add_executable(Basic Basic.cxx)
target_link_libraries(Basic PRIVATE graph::graph)

add_executable(Iterator Iterator.cxx)
target_link_libraries(Iterator PRIVATE graph::graph)
