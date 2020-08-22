add_executable( BasicScene 
    main.cpp
)

target_link_libraries(
    BasicScene
    PRIVATE
        LazyE 
)

set_sample_properties( BasicScene )

add_custom_command(
    TARGET BasicScene POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_LIST_DIR}/Resources
    ${CMAKE_CURRENT_BINARY_DIR}/Resources
)