target_sources( ${EngineTargetName}
    PUBLIC
    $<INSTALL_INTERFACE:include/lazye/assets/modelloader.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/assets/modelloader.h>

    $<INSTALL_INTERFACE:include/lazye/assets/textureloader.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/assets/textureloader.h>

    PRIVATE
    modelloader.cpp
    textureloader.cpp
)