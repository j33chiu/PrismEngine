set(_INCL "${PROJECT_SOURCE_DIR}/include/core/math")


target_sources(prism PRIVATE
    ${_INCL}/prismTypeDef.h
    ${_INCL}/vec1.h
    ${_INCL}/vec2.h
    ${_INCL}/vec3.h
    ${_INCL}/vec4.h
    ${_INCL}/mat.h
    ${_INCL}/mat2.h
    ${_INCL}/mat3.h
    ${_INCL}/mat4.h
    ${_INCL}/pml.h
    ${_INCL}/vecAngle.h
    ${_INCL}/vecFunc.h
    ${_INCL}/vecRotate.h
    ${_INCL}/matFunc.h
    ${_INCL}/matTransform.h
    ${_INCL}/floatCompare.h
    ${_INCL}/expFunc.h
    ${_INCL}/trigFunc.h
    ${_INCL}/pmlFunctor.h
    ${_INCL}/dataPointer.h
)