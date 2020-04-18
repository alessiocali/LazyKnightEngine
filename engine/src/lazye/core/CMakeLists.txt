target_sources( ${EngineTargetName} 
    PUBLIC
    $<INSTALL_INTERFACE:include/lazye/core/entity.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/core/entity.h>

    $<INSTALL_INTERFACE:include/lazye/core/component.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/core/component.h>

    $<INSTALL_INTERFACE:include/lazye/core/world.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/core/world.h>

    PRIVATE
    entity.cpp
    component.cpp
    world.cpp
)