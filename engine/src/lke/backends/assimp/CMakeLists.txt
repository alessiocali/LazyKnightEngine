add_lke_dependencies(assimp)

if (WIN32)
    find_package(assimp CONFIG REQUIRED)
    target_link_libraries(${EngineTargetName} PRIVATE assimp::assimp)
else()
    # Workaround for a weird Unix issue where Assimp would sometimes not be located
    # See https://github.com/microsoft/vcpkg/pull/13264
    #
    # Waiting for next VCPKG release to test it out.
    # Can't currently checkout master/latest because it causes a dependency error on Windows/SDL2
    
    find_and_link(${EngineTargetName} assimp)
    find_and_link(${EngineTargetName} z)
    find_and_link(${EngineTargetName} IrrXML)
endif()

target_sources(
    ${EngineTargetName}

    PRIVATE
    assimpmodelloader.h
    assimpmodelloader.cpp
)