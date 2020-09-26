function(set_sample_properties TargetName)
    set_common_properties(${TargetName})

    set_target_properties(
        ${TargetName}
        PROPERTIES
        FOLDER ${SampleFolder}
    )

    if (WIN32 AND BUILD_LAZYE_SHARED)
        # Update all .dll artifacts post build

        GetFullTargetOutputName(${EngineTargetName} EngineTargetOutputName)

        add_custom_command(
            TARGET ${TargetName} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_BINARY_DIR}/engine/${EngineTargetOutputName}.dll
            $<TARGET_FILE_DIR:${TargetName}>
        )

    endif()

endfunction()

set(SampleFolder Samples)
add_subdirectory(hello-lazye)
add_subdirectory(hello-window)
add_subdirectory(basic-scene)
add_subdirectory(basic-mesh)
add_subdirectory(transform-scene)
add_subdirectory(knight-parade)