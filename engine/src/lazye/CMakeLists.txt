target_sources( ${EngineTargetName}
    PUBLIC
    $<INSTALL_INTERFACE:include/lazye/lazye.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/lazye.h>

    $<INSTALL_INTERFACE:include/lazye/logger.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/logger.h>

    $<INSTALL_INTERFACE:include/lazye/asserts.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/asserts.h>

    PRIVATE
    logger.cpp
)

add_subdirectory( backends )
add_subdirectory( core )
add_subdirectory( math )
add_subdirectory( graphics )