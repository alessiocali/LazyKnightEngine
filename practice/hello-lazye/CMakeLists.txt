add_executable ( HelloLazyE main.cpp )

target_link_libraries(
    HelloLazyE
    PRIVATE
        LazyE 
)

set_practice_properties( HelloLazyE )