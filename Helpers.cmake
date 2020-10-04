function (find_and_link Target LibName)

    unset(LIBRARY CACHE)
    find_library(LIBRARY ${LibName})

    if (LIBRARY)
        message("-- Manual Linking ${LibName} from ${LIBRARY}")
        target_link_libraries(${Target} PRIVATE ${LIBRARY})
    endif()

endfunction()

function(set_common_properties TargetName ) # TargetBaseOutputName = TargetName
    if ( ${ARGC} GREATER 1 )
        set(TargetBaseOutputName ${ARGV1})
    else()
        set(TargetBaseOutputName ${TargetName})
    endif()

    GetFullTargetOutputName(${TargetName} ${TargetBaseOutputName} TargetOutputName )

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

function (fix_interface_libraries TargetName)

    set(FixedInterface "")

    get_target_property(InterfaceLinkLibraries ${EngineTargetName} INTERFACE_LINK_LIBRARIES)

    if (NOT InterfaceLinkLibraries)
        return()
    endif()

    foreach(Link ${InterfaceLinkLibraries})
        
        set(FixedLink ${Link})

        if (IS_ABSOLUTE ${Link})

            # Absolute paths should not be here. If they are, it's likely some workaround
            # like the one with Assimp. In this case they should be removed and handled separately
            # in the config file.
            set(FixedLink "")

        elseif(${Link} MATCHES ::@)

            # Due to reasons beyond my comprehension, Private imported targets on a static
            # library generate an interface like $<LINK_ONLY:MyImport::@(directory-id)>
            #
            # directory-id should theoretically be stripped; in practice, it's not, and this
            # breaks linkage when trying to link against this target externally. So yeah, let's
            # get rid of that, the library will be found anyway with find_dependency
            #
            # For more informations, here are the fruits of my hours spent pouring over Google
            #
            # https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_LIBRARIES.html
            # https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#creating-relocatable-packages
            # https://gitlab.kitware.com/cmake/cmake/-/issues/17943

            string(REGEX REPLACE ::@.*$ "" FixedLink ${Link})

            # We might have broken generator expressions, so let's take care of that
            fix_generator_expressions(${FixedLink} GeneratorOutput)
            set(FixedLink ${GeneratorOutput})

        endif()

        if (NOT FixedLink)
            message(STATUS "Deleting link ${Link}")
        elseif(NOT Link STREQUAL FixedLink)
            message(STATUS "Replacing link ${Link} with ${FixedLink}")
        endif()

        list(APPEND FixedInterface ${FixedLink})

    endforeach()

    set_target_properties(${TargetName} PROPERTIES INTERFACE_LINK_LIBRARIES "${FixedInterface}")

endfunction()

function (fix_generator_expressions Expression GeneratorOutput)

    set(FixedExpression ${Expression})

    string(REGEX MATCHALL < AllOpen ${Expression})
    string(REGEX MATCHALL > AllClose ${Expression})
    list(LENGTH AllOpen OpenCount)
    list(LENGTH AllClose CloseCount)

    if (${OpenCount} GREATER ${CloseCount})

        math(EXPR ToAddCount "${OpenCount} - ${CloseCount} - 1")

        foreach( i RANGE ${ToAddCount} )
            set(FixedExpression "${FixedExpression}>")
        endforeach()

    endif()

    set(${GeneratorOutput} ${FixedExpression} PARENT_SCOPE)

endfunction()