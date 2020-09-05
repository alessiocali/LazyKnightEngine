add_executable( ${EngineTargetTests}
    catch_main.cpp
    test_vectors.cpp
    test_matrix.cpp
    test_quaternions.cpp
)

find_package(Catch2 REQUIRED)

target_link_libraries( LazyE-Tests
    PRIVATE
    Catch2::Catch2
    LazyE
)
