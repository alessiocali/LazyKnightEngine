macro(set_practice_properties TargetName)
    set_target_properties(
        ${TargetName}
        PROPERTIES
        FOLDER ${PracticeFolder}
    )
endmacro()

set(PracticeFolder Practice)
add_subdirectory(hello-lazye)
add_subdirectory(hello-window)