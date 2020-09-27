target_sources( ${EngineTargetName} 
    PUBLIC
    $<INSTALL_INTERFACE:include/lke/core/entity.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/core/entity.h>

    $<INSTALL_INTERFACE:include/lke/core/component.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/core/component.h>

    $<INSTALL_INTERFACE:include/lke/core/world.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/core/world.h>

    PRIVATE
    entity.cpp
    component.cpp
    world.cpp
)