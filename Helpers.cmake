function(set_common_properties TargetName)

    GetFullTargetOutputName(${TargetName} TargetOutputName)

    set_target_properties(
        ${TargetName}
        PROPERTIES
        OUTPUT_NAME "${TargetOutputName}"
    )

endfunction()