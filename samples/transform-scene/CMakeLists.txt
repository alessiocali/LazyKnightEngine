add_executable( TransformScene 
    main.cpp
)

target_link_libraries(
    TransformScene
    PRIVATE
    ${EngineTargetName}
)

set_sample_properties( TransformScene )

add_custom_command(
    TARGET TransformScene POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_LIST_DIR}/Resources
    ${CMAKE_CURRENT_BINARY_DIR}/Resources
)