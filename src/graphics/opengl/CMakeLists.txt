set(_INCL "${PROJECT_SOURCE_DIR}/include/graphics/opengl")

target_sources(prism PRIVATE
	${_INCL}/opengl.h
	${_INCL}/openglShader.h
	${_INCL}/openglVAO.h
	${_INCL}/openglVAOFactory.h
	${_INCL}/openglBuffers.h
	${_INCL}/openglDef.h
	${_INCL}/openglRenderer.h
	${_INCL}/openglMesh.h
	${_INCL}/openglMeshManager.h
	${_INCL}/openglMaterial.h
	${_INCL}/openglMaterialManager.h
	opengl.cpp
	openglShader.cpp
	openglVAO.cpp
	openglVAOFactory.cpp
	openglRenderer.cpp
	openglMesh.cpp
	openglMeshManager.cpp
	openglMaterial.cpp
	openglMaterialManager.cpp
)