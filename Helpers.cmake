function(set_common_properties TargetName)

    GetFullTargetOutputName(${TargetName} TargetOutputName)

    set_target_properties(
        ${TargetName}
        PROPERTIES
        OUTPUT_NAME "${TargetOutputName}"

        ARCHIVE_OUTPUT_DIRECTORY $<1:${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}>
        COMPILE_PDB_OUTPUT_DIRECTORY $<1:${CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY}>
        LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_LIBRARY_OUTPUT_DIRECTORY}>
        PDB_OUTPUT_DIRECTORY $<1:${CMAKE_PDB_OUTPUT_DIRECTORY}>
        RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}>
    )

endfunction()