target_sources( ${EngineTargetName}
    PUBLIC
    $<INSTALL_INTERFACE:include/lke/assets/modelloader.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/assets/modelloader.h>

    $<INSTALL_INTERFACE:include/lke/assets/textureloader.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/assets/textureloader.h>

    PRIVATE
    modelloader.cpp
    textureloader.cpp
)