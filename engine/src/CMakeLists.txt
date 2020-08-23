# Add current binary directory to include configured headers
target_include_directories(
    ${EngineTargetName}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

add_subdirectory( lazye )