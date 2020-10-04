cmake_minimum_required(VERSION 3.16)

set(
    CMAKE_TOOLCHAIN_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
    CACHE STRING "Vcpkg toolchain file"
)

project( MyLazyKnightProject )

add_executable(Main main.cpp)
find_package(LazyKnight CONFIG REQUIRED COMPONENTS Engine)
target_link_libraries(Main PRIVATE LazyKnight::Engine)