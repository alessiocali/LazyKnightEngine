target_sources( ${EngineTargetName}
    PUBLIC
    $<INSTALL_INTERFACE:include/lke/math/math.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/math/math.h>

    $<INSTALL_INTERFACE:include/lke/math/physic_units.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/math/physic_units.h>

    $<INSTALL_INTERFACE:include/lke/math/vectors.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/math/vectors.h>

    $<INSTALL_INTERFACE:include/lke/math/matrix.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/math/matrix.h>

    $<INSTALL_INTERFACE:include/lke/math/quaternions.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/math/quaternions.h>

    $<INSTALL_INTERFACE:include/lke/math/transform.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/math/transform.h>

    PRIVATE
    quaternions.cpp
    transform.cpp
    math.cpp
)