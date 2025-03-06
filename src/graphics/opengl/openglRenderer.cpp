#include "graphics/opengl/openglRenderer.h"

#include <unordered_map>

#include "core/PrismRoot.h"
#include "graphics/win32/Win32OpenglWindow.h"
#include "graphics/opengl/openglMesh.h"
#include "graphics/opengl/OpenGLVAO.h"
#include "graphics/RenderObject.h"
#include "graphics/Material.h"
#include "graphics/opengl/openglMaterial.h"

namespace {

// helper function to draw renderobject
void drawObject(const prism::RenderObject* obj) {
    // note that vao binds can be optimized with the vao map (TODO)
    // bind obj vao
    const prism::OpenGLMesh* glMesh = static_cast<const prism::OpenGLMesh*>(obj->getMesh());
    glMesh->getVAO()->bind();

    GLenum primitiveType = GL_TRIANGLES;
    switch(obj->getPrimitiveType()) {
        default:
        case prism::PrimitiveType::TRIANGLE:
            primitiveType = GL_TRIANGLES;
            break;
        case prism::PrimitiveType::LINE:
            primitiveType = GL_LINES;
            break;
        case prism::PrimitiveType::QUAD:
            primitiveType = GL_QUADS;
            break;
    }

    GLuint instances = obj->getNumInstances();

    // bind vbo and ebo
    glBindVertexBuffer(0u, glMesh->getVBOId(), 0, glMesh->getVAO()->getVertexDescription().getVertexSizeBytes());
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

OpenGLRenderer::OpenGLRenderer(const uint32_t width, const uint32_t height) 
    : Renderer(width, height)
    , cameraData()
    , objectData()
    , vaos()
    , vaoObjectMap()
{
    glClearColor(0.85f, 0.85f, 0.90f, 1.0f);
    checkGLError("unable to set clear colour");
    glEnable(GL_DEPTH_TEST);
    checkGLError("unable to enable GL_DEPTH_TEST");
    glDepthFunc(GL_LESS);
    checkGLError("unable to set GL depth function");


    glEnable(GL_CULL_FACE);
    checkGLError("unable to enable face culling");
	glCullFace(GL_FRONT); // almost always want front face
    checkGLError("unable to set cull face to front");
	glFrontFace(GL_CCW); // usually order of triangle indices is ccw
    checkGLError("unable to set ccw to front face");
}

void OpenGLRenderer::setRenderPipeline(std::unique_ptr<RenderPipeline> pipeline) {
    this->pipeline = std::move(pipeline);
    this->pipeline->buildQueue();

    RenderStep* currentStep = this->pipeline->getRenderQueueStart();
    // for all objects, create ssbo for transformation data and ensure VAOs created
    while (currentStep) {
        if (currentStep->getType() == RenderStepType::DRAW) {
            const RenderObject* object = currentStep->getObject();
            RenderObjectType objectType = object->getType();
            if (objectType != RenderObjectType::NONE) {
                auto it = objectData.find(object);
                if (it == objectData.end()) {
                    // need to create buffer
                    std::unique_ptr<SSBO> ssbo = std::make_unique<SSBO>(sizeof(pml::mat4) * object->getNumInstances(), OBJECT_TRANSFORM_SSBO_BINDING_INDEX);
                    ssbo->writeVector(object->getInstanceData());
                    objectData[object] = std::move(ssbo);
                } else {
                    // buffer exists already, update it
                    it->second->overwriteVector(object->getInstanceData());
                }
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
        currentStep = currentStep->getNextStep();
    }

    // setup cameradata UBOs
    // camera ubo set as binding index 0 for inside shader
    cameraData = std::make_unique<UBO>(sizeof(pml::mat4), CAMERA_UBO_BINDING_INDEX);
}

void OpenGLRenderer::startPass(RenderStep* step) {
    // once framebuffer is implemented, use here
    bool hasTarget = false;

    const Camera* camera = step->getCamera();
    if (!hasTarget) {
        std::uint32_t scale = PrismRoot::windowManager().getCurrentWindow()->getScreenScale();
        glViewport(0, 0, width * scale, height * scale);
        checkGLError("could not set viewport");

        glBindFramebuffer(GL_FRAMEBUFFER, 0); // default frame buffer
        checkGLError("could not bind default framebuffer");
    }

    // clear target if specified in the step (TODO)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    checkGLError("unable to clear");

    // update camera data 
    assert(cameraData);
    assert(camera);
    cameraData.get()->overwrite(camera->getCamMatrix());

}

void OpenGLRenderer::draw(RenderStep* step) {
    const RenderObject* renderObject = step->getObject();

    // once framebuffer is implemented, use here
    bool hasTarget = false;

    if (!hasTarget) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // default frame buffer
        checkGLError("could not bind default framebuffer");
    }

    // bind material (shader program) if needed
    static const Material* previousMaterial = nullptr;
    const OpenglMaterial* material = static_cast<const OpenglMaterial*>(step->getMaterial());
    if (material != previousMaterial) {
        previousMaterial = material;
        material->bind();
    }

    // show wireframe if specified
    if(renderObject->showsWireframe()) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        checkGLError("could not enable wireframe");
    }

    // update relevant ssbo and ubos

    // debug UBO/SSBO
    /*
    UBO debugUBO = UBO(sizeof(pml::mat4), 1u);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1u, debugUBO.getID());
    debugUBO.overwrite(pml::mat4(0.1f, 0.2f, 0.3f, 1.0f,
                                0.1f, 0.2f, 0.3f, 1.0f,
                                0.1f, 0.2f, 0.3f, 1.0f,
                                1.0f, 0.2f, 0.3f, 1.0f));

    GLint debugTransfUniLoc = glGetUniformLocation(material->getID(), "debugTransf");
    const SingleRenderObject* singleObject = static_cast<const SingleRenderObject *>(renderObject);
    glUniformMatrix4fv(debugTransfUniLoc, 1, GL_FALSE, pml::dataPtr(singleObject->getData()));
    checkGLError("unable to set object transform uniform data (debug)");
    */

    // end debug

    // bind ubo and ssbo buffers for the object
    glBindBufferBase(GL_UNIFORM_BUFFER, CAMERA_UBO_BINDING_INDEX, cameraData->getID());
    checkGLError("could not bind cameraData UBO");

    prism::RenderObjectType objectType = renderObject->getType();
    if (objectType == RenderObjectType::NONE) return;

    auto it = objectData.find(renderObject);
    if (it == objectData.end()) {
        // buffer for object does not exist yet, need to create
        std::unique_ptr<SSBO> ssbo = std::make_unique<SSBO>(sizeof(pml::mat4) * renderObject->getNumInstances(), OBJECT_TRANSFORM_SSBO_BINDING_INDEX);
        ssbo->writeVector(renderObject->getInstanceData());
        objectData[renderObject] = std::move(ssbo);
    } else {
        // buffer exists already, overwrite it with updated data
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, OBJECT_TRANSFORM_SSBO_BINDING_INDEX, it->second->getID());
        checkGLError("could not bind model data SSBO");
        it->second->overwriteVector(renderObject->getInstanceData());
    }

    drawObject(renderObject);
}

void OpenGLRenderer::frame(RenderStep* step) {

#   if defined(PRISM_PLATFORM_WIN32)
    const Win32OpenglWindow* window = static_cast<const Win32OpenglWindow*>(PrismRoot::windowManager().getCurrentWindow());
    checkGLError("uncaught error before frame");
    SwapBuffers(window->getDeviceContext());
    checkGLError("unable to swap buffers");
#   endif
}

}