function(set_common_properties TargetName)

    GetFullTargetOutputName(${TargetName} TargetOutputName)

    set_target_properties(
        ${TargetName}
        PROPERTIES
        OUTPUT_NAME "${TargetOutputName}"
    )

endfunction()

function (add_copy_shared_libs_command TargetName)
    if (WIN32 AND BUILD_LAZYKNIGHT_SHARED)

    # Update all .dll artifacts post build
    add_custom_command(
        TARGET ${TargetName} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:${EngineTargetName}>
        $<TARGET_FILE_DIR:${TargetName}>
    )

    endif()
endfunction()