find_package(assimp CONFIG REQUIRED)

# Need to link ZLib and IrrXML due to a bug in Assimp to be solved (?) in v5.1
find_library(ASSIMP_ZLIB_LIBRARY z)
find_library(ASSIMP_IRRXML_LIBRARY IrrXML)

target_link_libraries(
    ${EngineTargetName}
    
    PRIVATE
    assimp::assimp
    ${ASSIMP_ZLIB_LIBRARY}
    ${ASSIMP_IRRXML_LIBRARY}
)

target_sources(
    ${EngineTargetName}

    PRIVATE
    assimpmodelloader.h
    assimpmodelloader.cpp
)