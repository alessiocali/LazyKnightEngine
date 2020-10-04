set( EngineTargetTests ${EngineTargetName}_Tests )

add_executable( ${EngineTargetTests}
    catch_main.cpp
    test_vectors.cpp
    test_matrix.cpp
    test_quaternions.cpp
)

add_lke_dependencies(Catch2)
find_package(Catch2 REQUIRED)

target_link_libraries( ${EngineTargetTests}
    PRIVATE
    Catch2::Catch2
    ${EngineTargetName}
)

add_copy_shared_libs_command( ${EngineTargetTests} )