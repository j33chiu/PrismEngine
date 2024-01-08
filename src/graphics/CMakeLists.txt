add_subdirectory("opengl")
add_subdirectory("win32")

set(_INCL "${PROJECT_SOURCE_DIR}/include/graphics")

target_sources(prism PRIVATE
	${_INCL}/Window.h
	${_INCL}/WindowManager.h

	#render stuff
	${_INCL}/PrimitiveType.h
	${_INCL}/Renderer.h
	${_INCL}/RenderPipeline.h
	${_INCL}/RenderStep.h
	${_INCL}/RenderTarget.h
	${_INCL}/RenderTargetManager.h
	${_INCL}/Texture.h
	${_INCL}/TextureManager.h
	${_INCL}/TextureSampler.h
	${_INCL}/Scene.h
	${_INCL}/RenderObject.h
	${_INCL}/SingleRenderObject.h
	${_INCL}/InstancedRenderObject.h
	${_INCL}/Material.h
	${_INCL}/MaterialManager.h
	${_INCL}/Mesh.h
	${_INCL}/MeshManager.h
	${_INCL}/Vertex.h
	${_INCL}/ShaderType.h
	Renderer.cpp
	RenderPipeline.cpp
	RenderStep.cpp
	RenderTarget.cpp
	RenderTargetManager.cpp
	Texture.cpp
	TextureManager.cpp
	TextureSampler.cpp
	Scene.cpp
	RenderObject.cpp
	SingleRenderObject.cpp
	InstancedRenderObject.cpp
	Mesh.cpp
	MeshManager.cpp
	Window.cpp
)