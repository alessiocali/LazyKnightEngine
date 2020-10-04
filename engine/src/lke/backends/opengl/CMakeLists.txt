# Find OpenGL and helper packages
add_lke_dependencies(glad)
find_package(glad CONFIG REQUIRED)

# Link dependencies
target_link_libraries( 
    ${EngineTargetName}
    PRIVATE
        glad::glad
)

# Add OpenGL includes
target_include_directories(
    ${EngineTargetName}
    PRIVATE
        ${GLAD_INCLUDE_DIRS}
)

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