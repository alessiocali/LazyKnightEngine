add_executable( LazyE-Tests 
    catch_main.cpp
    test_vectors.cpp
    test_quaternions.cpp
)

target_link_libraries( LazyE-Tests
    PRIVATE
    Catch2::Catch2
    LazyE
)
