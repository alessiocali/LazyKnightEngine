# Find OpenGL and helper packages
find_package(OpenGL REQUIRED)
find_package(glad CONFIG REQUIRED)

# Link dependencies
target_link_libraries( 
    ${EngineTargetName}
    PRIVATE
        ${OPENGL_gl_LIBRARY}
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

        openglsprite.h
        openglsprite.cpp
)

add_subdirectory(builtin_shaders)