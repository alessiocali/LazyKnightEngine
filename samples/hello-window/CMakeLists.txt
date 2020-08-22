add_executable ( HelloWindow main.cpp )

target_link_libraries( 
    HelloWindow
    PRIVATE
        LazyE 
)

set_sample_properties( HelloWindow )