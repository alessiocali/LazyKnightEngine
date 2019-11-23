target_sources( ${EngineTargetName}
    PUBLIC
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

    PRIVATE
    window.cpp
    renderingcontext.cpp
    renderingcomponent.cpp
    spritecomponent.cpp
)