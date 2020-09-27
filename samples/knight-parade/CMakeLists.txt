add_executable( KnightParade 
    main.cpp
)

target_link_libraries(
    KnightParade
    PRIVATE
    ${EngineTargetName}
)

set_sample_properties( KnightParade )

add_custom_command(
    TARGET KnightParade POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_LIST_DIR}/Resources
    ${CMAKE_CURRENT_BINARY_DIR}/Resources
)