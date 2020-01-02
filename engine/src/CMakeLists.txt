target_sources( ${EngineTargetName}
    PUBLIC
    $<INSTALL_INTERFACE:include/lazye/logger.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/logger.h>

    $<INSTALL_INTERFACE:include/lazye/macros.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lazye/macros.h>

    PRIVATE
    logger.cpp
)

add_subdirectory( core )
add_subdirectory( math )
add_subdirectory( graphics )