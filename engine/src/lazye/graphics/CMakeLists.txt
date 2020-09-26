target_sources( ${EngineTargetName}
    PUBLIC
    $<INSTALL_INTERFACE:include/lazye/graphics/graphicsfactory.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/graphics/graphicsfactory.h>

    $<INSTALL_INTERFACE:include/lazye/graphics/window.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/graphics/window.h>

    $<INSTALL_INTERFACE:include/lazye/graphics/camera.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/graphics/camera.h>

    $<INSTALL_INTERFACE:include/lazye/graphics/irenderable.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/graphics/irenderable.h>

    $<INSTALL_INTERFACE:include/lazye/graphics/mesh.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/graphics/mesh.h>

    $<INSTALL_INTERFACE:include/lazye/graphics/model.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/graphics/model.h>

    $<INSTALL_INTERFACE:include/lazye/graphics/modelcomponent.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/graphics/modelcomponent.h>

    $<INSTALL_INTERFACE:include/lazye/graphics/renderingcontext.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/graphics/renderingcontext.h>

    $<INSTALL_INTERFACE:include/lazye/graphics/renderingcomponent.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/graphics/renderingcomponent.h>

    $<INSTALL_INTERFACE:include/lazye/graphics/spritecomponent.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/graphics/spritecomponent.h>

    $<INSTALL_INTERFACE:include/lazye/graphics/sprite.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/graphics/sprite.h>

    PRIVATE
    camera.cpp
    graphicsfactory.cpp

    model.cpp
    modelcomponent.cpp
    renderingcontext.cpp
    renderingcomponent.cpp
    spritecomponent.cpp
)