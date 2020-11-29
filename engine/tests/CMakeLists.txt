set( EngineTargetTests ${EngineTargetName}_Tests )

option(ENABLE_CATCH2_BENCHMARKS "Compile and run Catch2 Benchmarks. Compiles in Release config only." ON)

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

if (ENABLE_CATCH2_BENCHMARKS)
    target_compile_definitions(${EngineTargetTests} PUBLIC $<$<CONFIG:Release>:CATCH_CONFIG_ENABLE_BENCHMARKING>)
endif()

add_copy_shared_libs_command( ${EngineTargetTests} )