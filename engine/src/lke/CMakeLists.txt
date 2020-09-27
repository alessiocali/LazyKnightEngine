target_sources( ${EngineTargetName}
    PUBLIC
    $<INSTALL_INTERFACE:include/lke/lke.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/lke.h>

    $<INSTALL_INTERFACE:include/lke/asserts.h>
    $<BUILD_INTERFACE:${BuildRootDir}/include/lke/asserts.h>
)

add_subdirectory( assets )
add_subdirectory( backends )
add_subdirectory( core )
add_subdirectory( math )
add_subdirectory( graphics )