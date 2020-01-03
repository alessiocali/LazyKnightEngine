macro(set_practice_properties TargetName)
    set_target_properties(
        ${TargetName}
        PROPERTIES
        FOLDER ${PracticeFolder}
    )

    add_custom_command(
        TARGET ${TargetName} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_BINARY_DIR}/engine/$<CONFIGURATION>
        $<TARGET_FILE_DIR:${TargetName}>
    )
endmacro()

set(PracticeFolder Practice)
add_subdirectory(hello-lazye)
add_subdirectory(hello-window)