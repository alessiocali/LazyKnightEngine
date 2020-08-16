set(BUILD_SHARED_LIBS FALSE CACHE BOOL "Build external dependencies statically" FORCE)

include(FetchContent)

function(FetchContent_AutoPopulate)
    foreach (ContentName IN LISTS ARGN)
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
    endforeach()
endfunction()

FetchContent_Declare(
    SDL
    HG_REPOSITORY  http://hg.libsdl.org/SDL
    HG_TAG         release-2.0.12
)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY  https://github.com/SFML/SFML.git
    GIT_TAG         2.5.1
)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
    GIT_TAG         v2.13.0
)

FetchContent_AutoPopulate(
    SDL
    SFML
    Catch2
)