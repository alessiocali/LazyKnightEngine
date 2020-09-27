add_executable ( HelloLazyKnight main.cpp )

target_link_libraries(
    HelloLazyKnight
    PRIVATE
    ${EngineTargetName}
)

set_sample_properties( HelloLazyKnight )