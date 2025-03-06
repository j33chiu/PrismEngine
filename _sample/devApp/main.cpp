#include <iostream>
#include <memory>

#include "core/PrismRoot.h"
#include "core/PrismInit.h"
#include "logger/Logger.h"
#include "util/files/FileManager.h"

#include "core/math/pml.h"
#include "graphics/Scene.h"
#include "graphics/RenderPipeline.h"
#include "graphics/Vertex.h"
#include "graphics/opengl/openglMesh.h"
#include "graphics/opengl/openglVAO.h"
#include "graphics/opengl/openglVAOFactory.h"
#include "core/Camera.h"

void app(int, char**) {
	// main app loop defined here, windows created etc

	// eg: layout files from resources attached to created windows
	// eg: objects loaded from files and added to created scenes
	// eg: object behaviours defined
	// eg: user interactions defined (keypresses, mouse actions)
	// eg: 

	auto window1 = prism::PrismRoot::windowManager().createWindow(1900, 600);
	//auto window2 = prism::PrismRoot::windowManager().createWindow(1000, 900);

	// set filemanager location (for stuff like loading shaders, textures etc)
	prism::FileManager fileManager = prism::FileManager::getInstance();
	fileManager.cd("textures");
	fileManager.listFiles();

	// texture loading
	prism::TextureSampler* defaultSampler = prism::PrismRoot::textureManager().getDefaultSampler();
	prism::Texture* brickTexture = prism::PrismRoot::textureManager().loadTexture("brick.png", prism::TextureUse::IMAGE, defaultSampler);

	// debug/testing scene
	std::unique_ptr<prism::RenderPipeline> win1Pipeline = std::make_unique<prism::RenderPipeline>(1900, 600);
	prism::Scene* win1Scene = win1Pipeline->createNewScene();

	// create camera and add to pipeline
	prism::Camera* win1Cam = win1Pipeline->createNewCamera();
	prism::pml::vec3 camPos(0.0f, 0.0f, 1.0f);
	prism::pml::vec3 camUp(0.0f, 1.0f, 0.0f);
	prism::pml::vec3 camOrientation(0.0f, 0.0f, -1.0f);
	win1Cam->setPosition(camPos);
	win1Cam->setUp(camUp);
	win1Cam->setOrientation(camOrientation);
	win1Cam->updateCamMatrix();

	// create second camera for debug purposes
	// prism::Camera* win1Cam2 = win1Pipeline->createNewCamera();
	// prism::pml::vec3 camPos2(0.0f, 0.5f, 1.0f);
	// prism::pml::vec3 camUp2(0.0f, 1.0f, 0.0f);
	// prism::pml::vec3 camOrientation2(0.0f, 0.0f, -1.0f);
	// win1Cam2->setPosition(camPos2);
	// win1Cam2->setUp(camUp2);
	// win1Cam2->setOrientation(camOrientation2);
	// win1Cam2->updateCamMatrix();

	// texture vertex
	prism::VertexDescriptor texturedVertexDescription;
	texturedVertexDescription.addVertexComponent(3, prism::VertexAttributeType::FLOAT);	// position
	texturedVertexDescription.addVertexComponent(4, prism::VertexAttributeType::FLOAT);	// colour
	texturedVertexDescription.addVertexComponent(2, prism::VertexAttributeType::FLOAT);	// texture uv

	std::unique_ptr<prism::VertexContainer> textureVertexContainer = std::make_unique<prism::VertexContainer>(texturedVertexDescription);
	textureVertexContainer->addRawData(prism::pml::vec3(-0.5f,  0.5f, -3.0f));
	textureVertexContainer->addRawData(prism::pml::vec4(0.1f, 0.6f, 0.3f, 1.0f));
	textureVertexContainer->addRawData(prism::pml::vec2(1.0f, 0.0f));

	textureVertexContainer->addRawData(prism::pml::vec3( 0.5f,  0.5f, -3.0f));
	textureVertexContainer->addRawData(prism::pml::vec4(0.3f, 0.2f, 0.5f, 1.0f));
	textureVertexContainer->addRawData(prism::pml::vec2(1.0f, 1.0f));

	textureVertexContainer->addRawData(prism::pml::vec3( 0.5f, -0.5f, -3.0f));
	textureVertexContainer->addRawData(prism::pml::vec4(0.5f, 0.9f, 0.7f, 1.0f));
	textureVertexContainer->addRawData(prism::pml::vec2(0.0f, 1.0f));

	textureVertexContainer->addRawData(prism::pml::vec3(-0.5f, -0.5f, -3.0f));
	textureVertexContainer->addRawData(prism::pml::vec4(0.7f, 0.15f, 0.9f, 1.0f));
	textureVertexContainer->addRawData(prism::pml::vec2(0.0f, 0.0f));

	textureVertexContainer->addRawData(prism::pml::vec3(-0.5f,  0.5f, -4.0f));
	textureVertexContainer->addRawData(prism::pml::vec4(0.1f, 0.6f, 0.3f, 1.0f));
	textureVertexContainer->addRawData(prism::pml::vec2(1.0f, 0.0f));

	textureVertexContainer->addRawData(prism::pml::vec3( 0.5f,  0.5f, -4.0f));
	textureVertexContainer->addRawData(prism::pml::vec4(0.3f, 0.2f, 0.5f, 1.0f));
	textureVertexContainer->addRawData(prism::pml::vec2(1.0f, 1.0f));

	textureVertexContainer->addRawData(prism::pml::vec3( 0.5f, -0.5f, -4.0f));
	textureVertexContainer->addRawData(prism::pml::vec4(0.5f, 0.9f, 0.7f, 1.0f));
	textureVertexContainer->addRawData(prism::pml::vec2(0.0f, 1.0f));

	textureVertexContainer->addRawData(prism::pml::vec3(-0.5f, -0.5f, -4.0f));
	textureVertexContainer->addRawData(prism::pml::vec4(0.7f, 0.15f, 0.9f, 1.0f));
	textureVertexContainer->addRawData(prism::pml::vec2(0.0f, 0.0f));

	// custom vertex description
	prism::VertexDescriptor vertexDescription;
	vertexDescription.addVertexComponent(3, prism::VertexAttributeType::FLOAT);		// position
	vertexDescription.addVertexComponent(4, prism::VertexAttributeType::FLOAT);		// colour
	vertexDescription.addVertexComponent(2, prism::VertexAttributeType::FLOAT);		// texture uv

	std::unique_ptr<prism::VertexContainer> vertexContainer = std::make_unique<prism::VertexContainer>(vertexDescription);
	vertexContainer->addRawData(prism::pml::vec3(-0.5f,  0.5f, -3.0f));
	vertexContainer->addRawData(prism::pml::vec4(0.1f, 0.6f, 0.3f, 1.0f));
	vertexContainer->addRawData(prism::pml::vec2(1.0f, 0.0f));

	vertexContainer->addRawData(prism::pml::vec3( 0.5f,  0.5f, -3.0f));
	vertexContainer->addRawData(prism::pml::vec4(0.3f, 0.2f, 0.5f, 1.0f));
	vertexContainer->addRawData(prism::pml::vec2(1.0f, 1.0f));

	vertexContainer->addRawData(prism::pml::vec3( 0.5f, -0.5f, -3.0f));
	vertexContainer->addRawData(prism::pml::vec4(0.5f, 0.9f, 0.7f, 1.0f));
	vertexContainer->addRawData(prism::pml::vec2(0.0f, 1.0f));

	vertexContainer->addRawData(prism::pml::vec3(-0.5f, -0.5f, -3.0f));
	vertexContainer->addRawData(prism::pml::vec4(0.7f, 0.15f, 0.9f, 1.0f));
	vertexContainer->addRawData(prism::pml::vec2(0.0f, 0.0f));

	vertexContainer->addRawData(prism::pml::vec3(-0.5f,  0.5f, -4.0f));
	vertexContainer->addRawData(prism::pml::vec4(0.1f, 0.6f, 0.3f, 1.0f));
	vertexContainer->addRawData(prism::pml::vec2(1.0f, 0.0f));

	vertexContainer->addRawData(prism::pml::vec3( 0.5f,  0.5f, -4.0f));
	vertexContainer->addRawData(prism::pml::vec4(0.3f, 0.2f, 0.5f, 1.0f));
	vertexContainer->addRawData(prism::pml::vec2(1.0f, 1.0f));

	vertexContainer->addRawData(prism::pml::vec3( 0.5f, -0.5f, -4.0f));
	vertexContainer->addRawData(prism::pml::vec4(0.5f, 0.9f, 0.7f, 1.0f));
	vertexContainer->addRawData(prism::pml::vec2(0.0f, 1.0f));

	vertexContainer->addRawData(prism::pml::vec3(-0.5f, -0.5f, -4.0f));
	vertexContainer->addRawData(prism::pml::vec4(0.7f, 0.15f, 0.9f, 1.0f));
	vertexContainer->addRawData(prism::pml::vec2(0.0f, 0.0f));

	std::vector<std::uint32_t> win1Indices;
	win1Indices.insert(win1Indices.end(), {0, 1, 2, // front face
										   0, 2, 3, 
										   4, 0, 3, // left face
										   4, 3, 7,
										   4, 5, 1,	// top face
										   4, 1, 0,
										   1, 5, 6,	// right face
										   1, 6, 2,
										   3, 2, 6,	// bottom face
										   3, 6, 7,
										   5, 4, 7,	// back face
										   5, 7, 6});

	// shader program
	const char* vertexShaderSource = R"(#version 450 core
	layout (location = 0) in vec3 pos;
	layout (location = 1) in vec4 col;
	layout (location = 2) in vec2 uv;

	// ubo
	layout(binding = 0) uniform cameraMatrix 
	{
		mat4 camMatrix;
	};

	// ssbo
	layout(binding = 1) buffer objectTransform 
	{
		mat4 transform[];
	};

	out vec4 colour;
	out vec2 texUV;
	out int i;
	void main()
	{
		// prism engine gives transformation matrices in row-major format, while opengl expects them in column-major
		gl_Position = camMatrix * transpose(transform[gl_InstanceID]) * vec4(pos, 1.0f);
		colour = col;
		texUV = uv;
		i = gl_InstanceID;
	})";
	const char* fragmentShaderSource = R"(#version 450 core
	out vec4 FragColor;
	in vec4 colour;
	in vec2 texUV;
	in int i;
	uniform sampler2D textureSampler;
	void main()
	{
		FragColor = colour;
	})";

	prism::Material* win1Material = prism::PrismRoot::materialManager().createMaterial(vertexShaderSource, fragmentShaderSource);

	// mesh generation using vertices and indices above
	const prism::Mesh* win1Mesh = prism::PrismRoot::meshManager().createMesh(std::move(vertexContainer), win1Indices);
	
	// create object using created mesh. define location and primitive draw type
	std::unique_ptr<prism::RenderObject> win1Obj = std::make_unique<prism::RenderObject>(win1Mesh, prism::PrimitiveType::TRIANGLE);
	win1Obj->addInstance({0.0f, 0.0f, -3.0f});
	win1Obj->addInstance({2.5f, 2.5f, -3.0f});
	win1Obj->addInstance({3.5f, 2.5f, -3.0f});	// TODO: be able to modify number of instances after adding object to scene
	// for (int x = 5; x < 55; x++) {
	// 	for (int y = 5; y < 55; y++) {
	// 		for (int z = 5; z < 55; z++) {
	// 			win1Obj->addInstance({x, y, z});
	// 		}
	// 	}
	// }

	std::unique_ptr<prism::RenderObject> win1Obj2 = std::make_unique<prism::RenderObject>(win1Mesh, prism::PrimitiveType::TRIANGLE);
	win1Obj2->addInstance({-1.0f, -1.0f, -3.0f});
	win1Obj2->addInstance({-2.5f, -2.5f, -3.0f});

	prism::PrismId object1Id = win1Obj->getId();
	prism::PrismId object2Id = win1Obj2->getId();

	// can add to scene with scene->addObject(), but using the pipeline is recommended
	// note that after the pipeline is set to the window, adding/removing objects MUST be done through the pipeline and CANNOT just be done via the scene
	win1Pipeline->triggerAddObject(win1Scene->getId(), win1Material, std::move(win1Obj));


	// separate pipeline for second window
	//std::unique_ptr<prism::RenderPipeline> win2Pipeline = std::make_unique<prism::RenderPipeline>(1000, 900);
	//prism::Scene* win2Scene = win2Pipeline->createNewScene();

	// add pipelines to window (which has a render object)
	window1->setRenderPipeline(std::move(win1Pipeline));
	prism::RenderPipeline* pipeline1 = window1->getRenderPipeline();
	//window2->setRenderPipeline(std::move(win2Pipeline));

	window1->startRenderThread();
	
	// TODO: create a class to register keypresses with functions
	while (prism::PrismRoot::windowManager().hasRunningWindows()) {
		// drain key and mouse events (up/down presses)
		while (window1->hasUiEvent()) {
			prism::Event uiEvent = window1->pollUiEvent();
			prism::EventType type = uiEvent.getEventType();
			if (type == prism::EventType::KEY) {
				if (uiEvent.getKeyEvent().has_value()) {
					prism::KeyId key = uiEvent.getKeyEvent().value().key;
					if (uiEvent.getKeyEvent().value().keyState == prism::EventState::DOWN) {
						// pressed key
						switch (key) {
							case prism::KeyId::ESC:
								win1Cam->setFPSMode(!win1Cam->isFPSCamera());
							 	break;
							case prism::KeyId::NUM1:
								pipeline1->triggerDeleteObject(pipeline1->getCurrentSceneId(), object1Id);
								break;
							case prism::KeyId::NUM2:
								pipeline1->triggerAddObject(pipeline1->getCurrentSceneId(), win1Material, std::move(win1Obj2));
								break;
							case prism::KeyId::NUM3:
								pipeline1->triggerDeleteObject(pipeline1->getCurrentSceneId(), object2Id);
								break;
							default:
								break;
						}
					} else {
						// unpressed key
					}
				}
			} else if (type == prism::EventType::MOUSE_MOVE) {
				if (win1Cam->isFPSCamera()) {
					// update camera orientation
					win1Cam->updateFPSOrientationDelta(uiEvent.getMouseMoveEvent().value().dX, uiEvent.getMouseMoveEvent().value().dY);
					// set cursor to center of screen
					window1->setCursorPosition(window1->getWidth() / 2, window1->getHeight() / 2);
				}
			}
		}

		// check state of keypresses 
		if (window1->isKeyPressed(prism::KeyId::W)) {
			win1Cam->moveForwardCardinal(0.0001f);
		}
		if (window1->isKeyPressed(prism::KeyId::S)) {
			win1Cam->moveBackwardCardinal(0.0001f);
		}
		if (window1->isKeyPressed(prism::KeyId::A)) {
			win1Cam->moveLeftCardinal(0.0001f);
		}
		if (window1->isKeyPressed(prism::KeyId::D)) {
			win1Cam->moveRightCardinal(0.0001f);
		}
		if (window1->isKeyPressed(prism::KeyId::SPACE)) {
			win1Cam->moveUpCardinal(0.0001f);
		} 
		if (window1->isKeyPressed(prism::KeyId::L_SHIFT)) {
			win1Cam->moveDownCardinal(0.0001f);
		} 
		// win1Cam->setPosition(camPos);
		win1Cam->updateCamMatrix();
	}
	window1->stopRenderThread();
}

int main(int argc, char **argv) {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	{
		prism::initDebug(argc, argv, app, prism::Platform { prism::DevicePlatform::WINDOWS, prism::GraphicsApi::OPENGL });
	}

	//_CrtDumpMemoryLeaks(); // shows leaks, likely since helper threads have not actually completed destruction yet (window event thread for example)

	return 0;
}