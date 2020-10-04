cmake_minimum_required(VERSION 3.16)

set(
    CMAKE_TOOLCHAIN_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
    CACHE STRING "Vcpkg toolchain file"
)

project( MyLazyKnightProject )

set(ExecutableName Main)

add_executable(${ExecutableName} main.cpp)
find_package(LazyKnight CONFIG REQUIRED COMPONENTS Engine)
target_link_libraries(Main PRIVATE LazyKnight::Engine)

if (WIN32 AND LazyKnightEngine_SHARED)

    add_custom_command(
        TARGET ${ExecutableName} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${LazyKnightEngine_BINDIR}
        $<TARGET_FILE_DIR:${ExecutableName}>
    )

endif()