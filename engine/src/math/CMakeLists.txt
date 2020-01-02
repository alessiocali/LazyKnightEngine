target_sources( ${EngineTargetName}
    PUBLIC
    $<INSTALL_INTERFACE:include/lazye/math/math.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/math/math.h>

    $<INSTALL_INTERFACE:include/lazye/math/vectors.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/math/vectors.h>
)