target_sources( ${EngineTargetName}
    PUBLIC
    $<INSTALL_INTERFACE:include/lke/graphics/graphicsfactory.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/graphics/graphicsfactory.h>

    $<INSTALL_INTERFACE:include/lke/graphics/window.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/graphics/window.h>

    $<INSTALL_INTERFACE:include/lke/graphics/camera.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/graphics/camera.h>
    
    $<INSTALL_INTERFACE:include/lke/graphics/mesh.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/graphics/mesh.h>

    $<INSTALL_INTERFACE:include/lke/graphics/model.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/graphics/model.h>

    $<INSTALL_INTERFACE:include/lke/graphics/modelcomponent.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/graphics/modelcomponent.h>

    $<INSTALL_INTERFACE:include/lke/graphics/renderingcontext.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/graphics/renderingcontext.h>

    $<INSTALL_INTERFACE:include/lke/graphics/renderingcomponent.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/graphics/renderingcomponent.h>

    $<INSTALL_INTERFACE:include/lke/graphics/spritecomponent.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/graphics/spritecomponent.h>

    $<INSTALL_INTERFACE:include/lke/graphics/sprite.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/graphics/sprite.h>

    $<INSTALL_INTERFACE:include/lke/graphics/texture.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/graphics/texture.h>

    PRIVATE
    camera.cpp
    graphicsfactory.cpp

    model.cpp
    modelcomponent.cpp
    renderingcontext.cpp
    renderingcomponent.cpp
    sprite.cpp
    spritecomponent.cpp
)