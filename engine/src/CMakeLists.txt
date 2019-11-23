target_sources( ${EngineTargetName}
    PUBLIC
    $<INSTALL_INTERFACE:include/lazye/logger.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/logger.h>

    $<INSTALL_INTERFACE:include/lazye/macros.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/macros.h>

    $<INSTALL_INTERFACE:include/lazye/math.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/math.h>
    # PUBLIC

    PRIVATE
    logger.cpp
    math.cpp
)

add_subdirectory( core )
add_subdirectory( graphics )