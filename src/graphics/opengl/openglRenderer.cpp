#include "graphics/opengl/openglRenderer.h"

#include <unordered_map>

#include "core/PrismRoot.h"
#include "graphics/win32/Win32OpenglWindow.h"
#include "graphics/opengl/openglMesh.h"
#include "graphics/opengl/OpenGLVAO.h"
#include "graphics/RenderObject.h"
#include "graphics/SingleRenderObject.h"
#include "graphics/InstancedRenderObject.h"
#include "graphics/Material.h"
#include "graphics/opengl/openglMaterial.h"

namespace {

// helper function to get the transformation matrix of renderobjects
prism::pml::mat4 getTransformation(prism::pml::vec3 pos, prism::pml::FLOAT scale, prism::pml::FLOAT rotateDeg) {
    prism::pml::mat4 m;
    m[3] = prism::pml::vec4(pos);

    return m;
}

// helper function to draw renderobject
void drawObject(const prism::RenderObject* obj) {
    // note that vao binds can be optimized (todo)
    // bind obj vao
    const prism::OpenGLMesh* glMesh = static_cast<const prism::OpenGLMesh*>(obj->getMesh());
    glMesh->getVAO()->bind();

    GLenum primitiveType = GL_TRIANGLES;
    switch(obj->getPrimitiveType()) {
        default:
        case prism::PrimitiveType::TRIANGE:
            primitiveType = GL_TRIANGLES;
            break;
        case prism::PrimitiveType::LINE:
            primitiveType = GL_LINES;
            break;
        case prism::PrimitiveType::QUAD:
            primitiveType = GL_QUADS;
            break;
    }

    GLuint instances = (obj->getType() == prism::RenderObjectType::INSTANCED) ? 
        static_cast<GLuint>(static_cast<const prism::InstancedRenderObject*>(obj)->getInstancesCount()) : 1u;

    // bind vbo and ebo
    glBindVertexBuffer(0u, glMesh->getVBOId(), 0, glMesh->getVAO()->getVertexAttr().vertexStride);
    prism::checkGLError("unable to bind object vbo");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glMesh->getEBOId());
    prism::checkGLError("unable to bind object ebo");
    

    glDrawElementsInstanced(
        primitiveType, 
        static_cast<GLsizei>(glMesh->getIndices().size()), 
        GL_UNSIGNED_INT, 
        0, 
        static_cast<GLsizei>(instances));
    prism::checkGLError("unable to draw object");

    // unbind obj vao
    glMesh->getVAO()->unbind();
    prism::checkGLError("unable to unbind object vao");
}

}

namespace prism {

OpenGLRenderer::OpenGLRenderer(std::uint32_t width, std::uint32_t height) 
    : Renderer()
    , width(width)
    , height(height)
    , cameraData()
    , singleObjectData()
    , instancedObjectData()
    , vaos()
    , vaoObjectMap()
{
    glClearColor(0.85f, 0.85f, 0.90f, 1.0f);
    checkGLError("unable to set clear colour");
    glEnable(GL_DEPTH_TEST);
    checkGLError("unable to enable GL_DEPTH_TEST");
    glDepthFunc(GL_LESS);
    checkGLError("unable to set GL depth function");

/*
    glEnable(GL_CULL_FACE);
    checkGLError("unable to enable face culling");
	glCullFace(GL_FRONT); // almost always want front face
    checkGLError("unable to set cull face to front");
	glFrontFace(GL_CCW); // usually order of triangle indices is ccw
    checkGLError("unabe to set ccw to front face");*/
}

void OpenGLRenderer::setRenderPipeline(std::unique_ptr<RenderPipeline> pipeline) {
    this->pipeline = std::move(pipeline);
    this->pipeline->buildQueue();
    renderQueue = this->pipeline->getRenderQueue();

    // do any processing using built renderqueue that has to be done before starting to render

    // for all objects, create ssbo for transformation data and ensure VAOs created
    for (const RenderStep& step : renderQueue) {
        if (step.getType() == RenderStepType::DRAW) {
            const RenderObject* object = step.getObject();
            if (object->getType() == RenderObjectType::INSTANCED) {
                const InstancedRenderObject* instancedObject = static_cast<const InstancedRenderObject *>(object);
                instancedObjectData[object] = std::make_unique<SSBO>(sizeof(pml::mat4) * instancedObject->getInstancesCount(), 2u);
                instancedObjectData[object]->writeVector(instancedObject->getData());
            } else if (object->getType() == RenderObjectType::SINGLE) {
                const SingleRenderObject* singleObject = static_cast<const SingleRenderObject *>(object);
                singleObjectData[object] = std::make_unique<SSBO>(sizeof(pml::mat4), 2u);
                singleObjectData[object]->write(singleObject->getData());
            }
            const Mesh* objectMesh = object->getMesh();
            const OpenGLMesh* objectGLMesh = static_cast<const OpenGLMesh*>(objectMesh);
            // check VAOs
            assert(objectGLMesh->getVAO() != nullptr); // fatal, VAOs should be generated and attached to object meshes at their creation
            if (vaoObjectMap.find(objectGLMesh->getVAO()) == vaoObjectMap.end()) {
                vaoObjectMap[objectGLMesh->getVAO()] = std::vector<const RenderObject*>();
            }
            vaoObjectMap[objectGLMesh->getVAO()].push_back(object);
        }
    }

    // setup cameradata UBOs
    cameraData = std::make_unique<UBO>(sizeof(pml::mat4), 1u);

}

void OpenGLRenderer::startPass(RenderStep& step) {
    // once framebuffer is implemented, use here
    bool hasTarget = false;

    const Camera* camera = step.getCamera();
    if (!hasTarget) {
        std::uint32_t scale = PrismRoot::windowManager().getCurrentWindow()->getScreenScale();
        glViewport(0, 0, width * scale, height * scale);
        checkGLError("could not set viewport");

        glBindFramebuffer(GL_FRAMEBUFFER, 0); // default frame buffer
        checkGLError("could not bind default framebuffer");
    }

    // clear target if specified in the step (todo)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // update camera data 
    assert(cameraData);
    assert(camera);
    cameraData.get()->write(camera->getCamMatrix());

}

void OpenGLRenderer::draw(RenderStep& step) {
    const RenderObject* renderObject = step.getObject();

    // once framebuffer is implemented, use here
    bool hasTarget = false;

    if (!hasTarget) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // default frame buffer
        checkGLError("could not bind default framebuffer");
    }

    // bind material (shader program) if needed
    static const Material* previousMaterial = nullptr;
    const OpenglMaterial* material = static_cast<const OpenglMaterial*>(step.getMaterial());
    if (material != previousMaterial) {
        previousMaterial = material;
        material->bind();
    }

    // show wireframe if specified
    if(renderObject->showsWireframe()) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    // bind ubo and ssbo buffers for the object
    glBindBufferBase(GL_UNIFORM_BUFFER, 1u, cameraData->getID());
    checkGLError("could not bind cameraData UBO");

    if (renderObject->getType() == RenderObjectType::SINGLE) {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2u, singleObjectData[renderObject]->getID());
        checkGLError("could not bind model data SSBO");
    } else {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2u, instancedObjectData[renderObject]->getID());
        checkGLError("could not bind model data SSBO");
    }
    
    // debug
    const Camera* camera = step.getCamera();

    GLint debugCamUniLoc = glGetUniformLocation(material->getID(), "debugCam");
    GLint debugTransfUniLoc = glGetUniformLocation(material->getID(), "debugTransf");

    glUniformMatrix4fv(debugCamUniLoc, 1, GL_FALSE, pml::dataPtr(camera->getCamMatrix()));
    checkGLError("unable to set camera uniform data (debug)");
    const SingleRenderObject* singleObject = static_cast<const SingleRenderObject *>(renderObject);
    glUniformMatrix4fv(debugTransfUniLoc, 1, GL_FALSE, pml::dataPtr(singleObject->getData()));
    checkGLError("unable to set object transform uniform data (debug)");


    drawObject(renderObject);
}

void OpenGLRenderer::frame(RenderStep& step) {

#   if defined(PRISM_PLATFORM_WIN32)
    const Win32OpenglWindow* window = static_cast<const Win32OpenglWindow*>(PrismRoot::windowManager().getCurrentWindow());
    SwapBuffers(window->getDeviceContext());

#   endif
}

}