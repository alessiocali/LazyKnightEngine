set(BUILD_SHARED_LIBS FALSE CACHE BOOL "Build external dependencies statically" FORCE)

include(FetchContent)

macro(FetchContent_AutoPopulate ContentName Repository Tag)
    
    FetchContent_Declare(
        ${ContentName}
        GIT_REPOSITORY ${Repository}
        GIT_TAG ${Tag}
    )

    FetchContent_GetProperties(${ContentName})

    # FetchContent sets the variable based on lowercased name, because reasons
    STRING(TOLOWER ${ContentName} LcContentName)
    
    SET(CONTENT_POPULATED "${${LcContentName}_POPULATED}")

    if ( NOT ${CONTENT_POPULATED} )

        FetchContent_Populate(${ContentName})

        SET(CONTENT_SOURCE_DIR "${${LcContentName}_SOURCE_DIR}")
        SET(CONTENT_BINARY_DIR "${${LcContentName}_BINARY_DIR}")

        add_subdirectory(
            ${CONTENT_SOURCE_DIR}
            ${CONTENT_BINARY_DIR}
            EXCLUDE_FROM_ALL
        )

    endif()

endmacro()

add_subdirectory(SFML)
add_subdirectory(Catch2)