find_package(assimp CONFIG REQUIRED)

target_link_libraries(
    ${EngineTargetName}
    
    PRIVATE
    assimp::assimp
)

find_library(ASSIMP_ZLINK_LIBRARY z)
find_library(ASSIMP_IRRXML_LIBRARY IrrXML)

# Need to link ZLib and IrrXML due to a bug in Assimp to be solved (?) in v5.1
if (ASSIMP_ZLINK_LIBRARY)
    target_link_libraries(${EngineTargetName} PRIVATE ${ASSIMP_ZLINK_LIBRARY})
endif()

if (ASSIMP_IRRXML_LIBRARY)
    target_link_libraries(${EngineTargetName} PRIVATE ${ASSIMP_IRRXML_LIBRARY})
endif()

target_sources(
    ${EngineTargetName}

    PRIVATE
    assimpmodelloader.h
    assimpmodelloader.cpp
)