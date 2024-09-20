#include <iostream>
#include <memory>

#include "core/PrismRoot.h"
#include "core/PrismInit.h"
#include "logger/Logger.h"
#include "util/files/FileManager.h"

#include "core/math/pml.h"
#include "graphics/Scene.h"
#include "graphics/RenderPipeline.h"
#include "graphics/SingleRenderObject.h"
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


	// TODO: eventually have a class that handles polling, framerate caps, gameticking etc

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

	// custom vertex description
	prism::VertexDescriptor vertexDescription;
	vertexDescription.addVertexComponent(3, prism::VertexAttributeType::FLOAT);
	vertexDescription.addVertexComponent(4, prism::VertexAttributeType::FLOAT);

	std::unique_ptr<prism::VertexContainer> vertexContainer = std::make_unique<prism::VertexContainer>(vertexDescription);
	vertexContainer->addRawData(prism::pml::vec3(-0.5f,  0.5f, -3.0f));
	vertexContainer->addRawData(prism::pml::vec4(0.1f, 0.6f, 0.3f, 1.0f));

	vertexContainer->addRawData(prism::pml::vec3( 0.5f,  0.5f, -3.0f));
	vertexContainer->addRawData(prism::pml::vec4(0.3f, 0.2f, 0.5f, 1.0f));

	vertexContainer->addRawData(prism::pml::vec3( 0.5f, -0.5f, -3.0f));
	vertexContainer->addRawData(prism::pml::vec4(0.5f, 0.9f, 0.7f, 1.0f));

	vertexContainer->addRawData(prism::pml::vec3(-0.5f, -0.5f, -3.0f));
	vertexContainer->addRawData( prism::pml::vec4(0.7f, 0.15f, 0.9f, 1.0f));

	vertexContainer->addRawData(prism::pml::vec3(-0.5f,  0.5f, -4.0f));
	vertexContainer->addRawData(prism::pml::vec4(0.1f, 0.6f, 0.3f, 1.0f));

	vertexContainer->addRawData(prism::pml::vec3( 0.5f,  0.5f, -4.0f));
	vertexContainer->addRawData(prism::pml::vec4(0.3f, 0.2f, 0.5f, 1.0f));

	vertexContainer->addRawData(prism::pml::vec3( 0.5f, -0.5f, -4.0f));
	vertexContainer->addRawData(prism::pml::vec4(0.5f, 0.9f, 0.7f, 1.0f));

	vertexContainer->addRawData(prism::pml::vec3(-0.5f, -0.5f, -4.0f));
	vertexContainer->addRawData(prism::pml::vec4(0.7f, 0.15f, 0.9f, 1.0f));

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

	// ubo
	layout(binding = 0) uniform cameraMatrix 
	{
		mat4 camMatrix;
	};

	// ssbo
	layout(binding = 1) buffer objectTransform 
	{
		mat4 transform;
	};

	out vec4 colour;
	void main()
	{
		gl_Position = camMatrix * vec4(vec3(transform * vec4(pos, 1.0f)), 1.0f);
		colour = col;
	})";
	const char* fragmentShaderSource = R"(#version 450 core
	out vec4 FragColor;
	in vec4 colour;
	void main()
	{
		FragColor = colour;
	})";

	prism::Material* win1Material = prism::PrismRoot::materialManager().createMaterial(vertexShaderSource, fragmentShaderSource);

	// mesh generation using vertices and indices above
	const prism::Mesh* win1Mesh = prism::PrismRoot::meshManager().createMesh(std::move(vertexContainer), win1Indices);
	
	// create object using created mesh. define location and primitive draw type
	std::unique_ptr<prism::SingleRenderObject> win1Obj = std::make_unique<prism::SingleRenderObject>(win1Mesh, prism::pml::vec3(0.0f, 0.0f, 0.0f), prism::PrimitiveType::TRIANGE);
	win1Scene->addObject(win1Material, std::move(win1Obj));


	// separate pipeline for second window
	//std::unique_ptr<prism::RenderPipeline> win2Pipeline = std::make_unique<prism::RenderPipeline>(1000, 900);
	//prism::Scene* win2Scene = win2Pipeline->createNewScene();

	// add pipelines to window (which has a render object)
	window1->setRenderPipeline(std::move(win1Pipeline));
	//window2->setRenderPipeline(std::move(win2Pipeline));

	window1->startRenderThread();
	
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