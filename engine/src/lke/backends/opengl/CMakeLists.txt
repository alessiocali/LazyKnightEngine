# Add source files
target_sources(
    ${EngineTargetName}
    PRIVATE
        opengltypetraits.h

        opengluniformhelper.h

        openglapi.h
        openglapi.cpp

        openglshader.h
        openglshader.cpp

        openglvertexshader.h
        openglfragmentshader.h

        openglprogram.h
        openglprogram.cpp

        openglbufferobject.h

        openglvertexattribute.h
        openglvertexattribute.cpp

        openglvertexarrayobject.h
        openglvertexarrayobject.cpp

        opengltexture.h
        opengltexture.cpp

        openglmesh.h
        openglmesh.cpp
)

add_subdirectory(builtin_shaders)