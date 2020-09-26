target_sources( ${EngineTargetName}
    PUBLIC
    $<INSTALL_INTERFACE:include/lazye/assets/assetloader.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/assets/assetloader.h>

    PRIVATE
    assetloader.cpp
)