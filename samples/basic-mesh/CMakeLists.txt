add_executable( BasicMesh 
    main.cpp
)

target_link_libraries(
    BasicMesh
    PRIVATE
        LazyE 
)

set_sample_properties( BasicMesh )

add_custom_command(
    TARGET BasicMesh POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_LIST_DIR}/Resources
    ${CMAKE_CURRENT_BINARY_DIR}/Resources
)