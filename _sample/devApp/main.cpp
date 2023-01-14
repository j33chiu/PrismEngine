#include <iostream>
#include <memory>

#include "core/PrismRoot.h"
#include "core/PrismInit.h"
#include "logger/Logger.h"

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


	// todo: eventually have a class that handles polling, framerate caps, gameticking etc
	// todo: spawn new threads per window

	auto window1 = prism::PrismRoot::windowManager().createWindow(800, 600);
	//auto window2 = prism::PrismRoot::windowManager().createWindow(1000, 900);

	bool running1 = true;
	//bool running2 = true;

	// debug/testing scene
	std::unique_ptr<prism::RenderPipeline> win1Pipeline = std::make_unique<prism::RenderPipeline>(800, 600);
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

	
	// create square (add object to scene in pipeline)
	prism::VertexDataDebug v1 {
		.pos = prism::pml::vec3(-0.5f,  0.5f, -3.0f),
		.colour = prism::pml::vec4(0.1f, 0.75f, 0.3f, 1.0f)
	};
	prism::VertexDataDebug v2 {
		.pos = prism::pml::vec3( 0.5f,  0.5f, -3.0f),
		.colour = prism::pml::vec4(0.1f, 0.75f, 0.3f, 1.0f)
	};
	prism::VertexDataDebug v3 {
		.pos = prism::pml::vec3( 0.5f, -0.5f, -3.0f),
		.colour = prism::pml::vec4(0.1f, 0.75f, 0.3f, 1.0f)
	};
	prism::VertexDataDebug v4 {
		.pos = prism::pml::vec3(-0.5f, -0.5f, -3.0f),
		.colour = prism::pml::vec4(0.1f, 0.75f, 0.3f, 1.0f)
	};

	std::vector<std::uint32_t> win1Indices;
	win1Indices.insert(win1Indices.end(), {0, 1, 2, 0, 2, 3});

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
	// vertexDataAttr can be modified for custom user-defined vertices. here, a default vertex layout is used (VertexDataDebug)
	prism::VertexDataAttributes vertexDataAttr = prism::getVertexDataAttributes(v1);
	std::unique_ptr<prism::VertexContainer> win1VerticesContainer = std::make_unique<prism::VertexContainer>(vertexDataAttr);
	win1VerticesContainer->addVertex(&v1);
	win1VerticesContainer->addVertex(&v2);
	win1VerticesContainer->addVertex(&v3);
	win1VerticesContainer->addVertex(&v4);
	const prism::Mesh* win1Mesh = prism::PrismRoot::meshManager().createMesh(std::move(win1VerticesContainer), win1Indices);
	
	// create object using created mesh. define location and primitive draw type
	std::unique_ptr<prism::SingleRenderObject> win1Obj = std::make_unique<prism::SingleRenderObject>(win1Mesh, prism::pml::vec3(0.0f, 0.0f, 0.0f), prism::PrimitiveType::TRIANGE);
	win1Scene->addObject(win1Material, std::move(win1Obj));


	// separate pipeline for second window
	//std::unique_ptr<prism::RenderPipeline> win2Pipeline = std::make_unique<prism::RenderPipeline>(1000, 900);
	//prism::Scene* win2Scene = win2Pipeline->createNewScene();

	// add pipelines to window (which has a render object)
	window1->setRenderPipeline(std::move(win1Pipeline));
	//window2->setRenderPipeline(std::move(win2Pipeline));

	// issue with polling and framerates:
	// lower framerates are limiting the polling. However, windows events are detected outside this thread
	// this results in a growing queue of events, so the application falls behind when polling
	// would have to poll the window in a separate thread and handle accordingly
	while (running1) { // || running2) {
		
		auto event1 = window1->pollWindow();
		//auto event2 = window2->pollWindow();

		if (event1.has_value()) {
			if (event1->isExitEvent()) running1 = false; 
			prism::Event e1 = event1.value();
			//if (e1.getEventType() != prism::EventType::MOUSE_MOVE)
				prism::Logger::debug("main", e1);
		}
		/*
		if (event2.has_value()) {
			if (event2->isExitEvent()) running2 = false; 
			prism::Event e2 = event2.value();
			if (e2.getEventType() != prism::EventType::MOUSE_MOVE)
				prism::Logger::debug("main", e2);
		}*/
		window1->render();
		//window2->render();
	}

}

int main(int argc, char **argv) {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	prism::initDebug(argc, argv, app, prism::Platform { prism::DevicePlatform::WINDOWS, prism::GraphicsApi::OPENGL });

	//_CrtDumpMemoryLeaks();

	return 0;
}