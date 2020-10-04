function(set_sample_properties TargetName)
    set_common_properties(${TargetName})

    set_target_properties(
        ${TargetName}
        PROPERTIES
        FOLDER ${SampleFolder}
    )

    add_copy_shared_libs_command(${TargetName})
endfunction()

set(SampleFolder Samples)
add_subdirectory(hello-window)
add_subdirectory(basic-scene)
add_subdirectory(basic-mesh)
add_subdirectory(transform-scene)
add_subdirectory(knight-parade)