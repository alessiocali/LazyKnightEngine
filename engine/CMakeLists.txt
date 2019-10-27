project(Engine)

# Add all source files and includes
add_library( 
    LazyE
    include/lazye/macros.h
    include/lazye/math.h
    src/math.cpp
    include/lazye/logger.h
    src/logger.cpp
    include/lazye/graphics.h
    src/graphics.cpp
)

target_compile_features( 
    LazyE 
    PUBLIC
        cxx_std_17 
)

# Set warnings as errors
if (MSVC)
    target_compile_options(LazyE PRIVATE /W4 /WX)
else()
    target_compile_options(LazyE PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Add Debug Postfix to differentiate artifacts
set_target_properties( 
    LazyE
    PROPERTIES
    DEBUG_POSTFIX "_d"
    CXX_EXTENSIONS OFF
)

# Link dependencies
target_link_libraries( 
    LazyE
    PRIVATE
        sfml-window 
        sfml-graphics
)

# Setup the include directories
target_include_directories( 
    LazyE
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        src
)

# Setup installation paths
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR cmake/LazyE)

# Install library DLL and export target
install(
    TARGETS LazyE 
    EXPORT  LazyE-Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install include directory
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install exported target
install(
    EXPORT      LazyE-Targets
    FILE        LazyETargets.cmake
    NAMESPACE   LazyE::
    DESTINATION ${INSTALL_CONFIGDIR}
)

# Create configured _Config.cmake file
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/LazyEConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/LazyEConfig.cmake
    INSTALL_DESTINATION     ${INSTALL_CONFIGDIR}
    PATH_VARS               INSTALL_CONFIGDIR
)

# Install the _Config.cmake file
install(
    FILES
    ${CMAKE_CURRENT_BINARY_DIR}/LazyEConfig.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)