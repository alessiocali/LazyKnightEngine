target_sources( ${EngineTargetName}
    PUBLIC
    $<INSTALL_INTERFACE:include/lazye/math/math.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/math/math.h>

    $<INSTALL_INTERFACE:include/lazye/math/physic_units.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/math/physic_units.h>

    $<INSTALL_INTERFACE:include/lazye/math/vectors.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/math/vectors.h>

    $<INSTALL_INTERFACE:include/lazye/math/matrix.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/math/matrix.h>

    $<INSTALL_INTERFACE:include/lazye/math/quaternions.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/math/quaternions.h>

    $<INSTALL_INTERFACE:include/lazye/math/transform.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/math/transform.h>

    PRIVATE
    quaternions.cpp
    transform.cpp
    math.cpp
)