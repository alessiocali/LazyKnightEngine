find_package(assimp CONFIG REQUIRED)

target_link_libraries(
    ${EngineTargetName}
    
    PRIVATE
    assimp::assimp
)

target_sources(
    ${EngineTargetName}

    PRIVATE
    assimpassetloader.h
    assimpassetloader.cpp
)