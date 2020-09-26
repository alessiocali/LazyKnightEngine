find_package(assimp CONFIG REQUIRED)

target_link_libraries(
    ${EngineTargetName}
    
    PRIVATE
    assimp::assimp
)

target_sources(
    ${EngineTargetName}

    PRIVATE
    assimpmodelloader.h
    assimpmodelloader.cpp
)