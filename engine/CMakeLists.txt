project(Engine)

set ( EngineTargetExports ${EngineTargetName}-Target )
set ( EngineTargetConfig ${EngineTargetName}Config )

set ( BuildRootDir ${CMAKE_CURRENT_SOURCE_DIR} )

# Add all source files and includes
if (BUILD_LAZYE_SHARED)
    add_library( ${EngineTargetName} SHARED )
else()
    add_library( ${EngineTargetName} STATIC )
endif()

source_group( "Sources" REGULAR_EXPRESSION "/*" )
source_group( "Sources\\Core" REGULAR_EXPRESSION "core/*" )
source_group( "Sources\\Graphics" REGULAR_EXPRESSION "graphics/*" )
source_group( "Sources\\Math" REGULAR_EXPRESSION "math/*" )
source_group( "Backends" REGULAR_EXPRESSION "/backends/*" )
source_group( "Backends\\SDL" REGULAR_EXPRESSION "/backends/sdl/*" )

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
    target_compile_options(${EngineTargetName} PRIVATE /W4 /WX /wd4100)
else()
    target_compile_options(${EngineTargetName} PRIVATE -Wall -Wextra -pedantic -Werror -Wno-unused-parameter)
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

set_common_properties(${EngineTargetName})

set_target_properties( 
    ${EngineTargetName}
    PROPERTIES
    CXX_EXTENSIONS OFF
)

# Add additional module finders
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

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

# Add the actual sources
add_subdirectory( src )

# Include the Tests
add_subdirectory( tests )