project(Engine)

set ( EngineTargetName LazyE )
set ( EngineTargetExports ${EngineTargetName}-Target )
set ( EngineTargetConfig ${EngineTargetName}Config )

set ( BuildRootDir ${CMAKE_CURRENT_SOURCE_DIR} )

# Add all source files and includes
if (BUILD_LAZYE_SHARED)
    add_library( ${EngineTargetName} SHARED )
else()
    add_library( ${EngineTargetName} STATIC )
endif()
add_subdirectory( src )

source_group( "Sources" REGULAR_EXPRESSION "/*" )
source_group( "Sources\\Core" REGULAR_EXPRESSION "core/*" )
source_group( "Sources\\Graphics" REGULAR_EXPRESSION "graphics/*" )
source_group( "Sources\\Math" REGULAR_EXPRESSION "math/*" )

target_compile_features( 
    ${EngineTargetName}
    PUBLIC
        cxx_std_17 
)

target_precompile_headers(
    ${EngineTargetName}
    PRIVATE
    include/lazye/lazye.h
)

# Set warnings as errors
if (MSVC)
    target_compile_options(${EngineTargetName} PRIVATE /W4 /WX)
else()
    target_compile_options(${EngineTargetName} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Set compile flags for exports
set (PrivateCompileDefinitions "LAZYE_EXPORTS")
set (PublicCompileDefinitions "")
if (NOT BUILD_LAZYE_SHARED)
    set (PublicCompileDefinitions "${PublicCompileDefinitions} LAZYE_STATIC")
endif()

target_compile_definitions(
    ${EngineTargetName}
    PUBLIC
    ${PublicCompileDefinitions}
    PRIVATE
    ${PrivateCompileDefinitions}
)

# Add Debug Postfix to differentiate artifacts
set_target_properties( 
    ${EngineTargetName}
    PROPERTIES
    DEBUG_POSTFIX "_d"
    CXX_EXTENSIONS OFF
)

# Link dependencies
target_link_libraries( 
    ${EngineTargetName}
    PRIVATE
        sfml-window 
        sfml-graphics
)

# Setup the include directories
target_include_directories( 
    ${EngineTargetName}
    PUBLIC
        $<INSTALL_INTERFACE:include/>
        $<BUILD_INTERFACE:${BuildRootDir}/include/>
    PRIVATE
        src
)

# Setup installation paths
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR cmake/LazyE)

# Install library DLL and export target
install(
    TARGETS ${EngineTargetName} 
    EXPORT  ${EngineTargetExports}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install include directory
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install exported target
install(
    EXPORT      ${EngineTargetExports}
    FILE        ${EngineTargetExports}.cmake
    NAMESPACE   ${EngineTargetName}::
    DESTINATION ${INSTALL_CONFIGDIR}
)

# Create configured _Config.cmake file
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/${EngineTargetConfig}.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${EngineTargetConfig}.cmake
    INSTALL_DESTINATION     ${INSTALL_CONFIGDIR}
    PATH_VARS               INSTALL_CONFIGDIR
)

# Install the _Config.cmake file
install(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${EngineTargetConfig}.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

# Include the Tests
add_subdirectory( tests )