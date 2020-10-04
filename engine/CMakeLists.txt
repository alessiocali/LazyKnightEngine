project( ${EngineTargetName} )

set ( EngineExports         ${ProjectName}Export    )
set ( EngineExportConfig    ${ProjectName}Config    )
set ( EngineExportTargets   ${ProjectName}Targets   )

set ( BuildRootDir ${CMAKE_CURRENT_SOURCE_DIR} )

# List variable holding all dependencies (to setup LazyKnightConfig.cmake)
set(LazyKnightDeps "" CACHE INTERNAL "List of dependencies to link against Lazy Knight Engine")

macro(add_lke_dependencies)

    foreach(Dependency ${ARGN})
        set(LazyKnightDeps ${LazyKnightDeps} ${Dependency} CACHE INTERNAL "")
    endforeach()

endmacro()

# Add all source files and includes
if (BUILD_LAZYKNIGHT_SHARED)
    add_library( ${EngineTargetName} SHARED )
else()
    add_library( ${EngineTargetName} STATIC )
endif()

source_group( "Sources" REGULAR_EXPRESSION "/*" )
source_group( "Sources\\Assets" REGULAR_EXPRESSION "assets/*" )
source_group( "Sources\\Core" REGULAR_EXPRESSION "core/*" )
source_group( "Sources\\Graphics" REGULAR_EXPRESSION "graphics/*" )
source_group( "Sources\\Math" REGULAR_EXPRESSION "math/*" )
source_group( "Backends" REGULAR_EXPRESSION "/backends/*" )
source_group( "Backends\\Assimp" REGULAR_EXPRESSION "backends/assimp/*" )
source_group( "Backends\\SDL" REGULAR_EXPRESSION "/backends/sdl/*" )
source_group( "Backends\\SDL\\Assets" REGULAR_EXPRESSION "backends/sdl/assets/*" )
source_group( "Backends\\SDL\\OpenGL" REGULAR_EXPRESSION "backends/sdl/opengl/*" )
source_group( "Backends\\OpenGL" REGULAR_EXPRESSION "/backends/opengl/*" )

target_compile_features( 
    ${EngineTargetName}
    PUBLIC
        cxx_std_17 
)

target_precompile_headers(
    ${EngineTargetName}
    PRIVATE
    include/lke/lke.h
)

# Set warnings as errors
if (MSVC)
    target_compile_options(${EngineTargetName} PRIVATE /W4 /WX /wd4100)
else()
    target_compile_options(${EngineTargetName} PRIVATE -Wall -Wextra -pedantic -Werror -Wno-unused-parameter)
endif()

# Set compile flags for exports
set (PrivateCompileDefinitions "LAZYKNIGHT_EXPORTS")
set (PublicCompileDefinitions "")
if (NOT BUILD_LAZYKNIGHT_SHARED)
    set (PublicCompileDefinitions "${PublicCompileDefinitions} LAZYKNIGHT_STATIC")
endif()

target_compile_definitions(
    ${EngineTargetName}
    PUBLIC
    ${PublicCompileDefinitions}
    PRIVATE
    ${PrivateCompileDefinitions}
)

set_common_properties(${EngineTargetName} ${ProjectName}_${EngineTargetName} )

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

# Add the actual sources
add_subdirectory( src )

# Include the Tests
if (BUILD_LAZYKNIGHT_TESTS)
    add_subdirectory( tests )
endif()

## INSTALLATION SETUP ##

# Setup installation paths
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR   ${CMAKE_INSTALL_LIBDIR}/cmake/${ProjectName})
set(INSTALL_LIBDIR      ${CMAKE_INSTALL_LIBDIR}/${ProjectName})

# Install library files and export target
install(
    TARGETS             ${EngineTargetName} 
    EXPORT              ${EngineExports}
    LIBRARY DESTINATION ${INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${INSTALL_LIBDIR}
)

# Install include directory
install(
    DIRECTORY       include/ 
    DESTINATION     ${CMAKE_INSTALL_INCLUDEDIR}
)

# Fix INTERFACE_LINK_LIBRARIES because woe is me
fix_interface_libraries(${EngineTargetName})

# Install exported target
install(
    EXPORT      ${EngineExports}
    FILE        ${EngineExportTargets}.cmake
    NAMESPACE   ${ProjectNameSpace}::
    DESTINATION ${INSTALL_CONFIGDIR}
)

message(STATUS "Setting up Config file with dependency list: ${LazyKnightDeps}")

# Create configured _Config.cmake file
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/${EngineExportConfig}.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${EngineExportConfig}.cmake
    INSTALL_DESTINATION     ${INSTALL_CONFIGDIR}
    PATH_VARS               INSTALL_CONFIGDIR
)

# Install the _Config.cmake file
install(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${EngineExportConfig}.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)