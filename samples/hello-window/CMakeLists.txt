add_executable ( HelloWindow main.cpp )

target_link_libraries( 
    HelloWindow
    PRIVATE
    ${EngineTargetName}
)

set_sample_properties( HelloWindow )