target_sources( ${EngineTargetName}
    PUBLIC
    $<INSTALL_INTERFACE:include/lazye/graphics/graphicsfactory.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/graphics/graphicsfactory.h>

    $<INSTALL_INTERFACE:include/lazye/graphics/window.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/graphics/window.h>

    $<INSTALL_INTERFACE:include/lazye/graphics/irenderable.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/graphics/irenderable.h>

    $<INSTALL_INTERFACE:include/lazye/graphics/renderingcontext.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/graphics/renderingcontext.h>

    $<INSTALL_INTERFACE:include/lazye/graphics/renderingcomponent.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/graphics/renderingcomponent.h>

    $<INSTALL_INTERFACE:include/lazye/graphics/spritecomponent.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/graphics/spritecomponent.h>

    $<INSTALL_INTERFACE:include/lazye/graphics/sprite.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/graphics/sprite.h>

    PRIVATE
    graphicsfactory.cpp

    renderingcontext.cpp
    renderingcomponent.cpp
    spritecomponent.cpp
)