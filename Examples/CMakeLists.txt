add_executable(Basic Basic.cxx)
target_link_libraries(Basic PRIVATE graph::graph)

add_executable(BreadthFirstIterator BreadthFirstIterator.cxx)
target_link_libraries(BreadthFirstIterator PRIVATE graph::graph)

add_executable(DepthFirstIterator DepthFirstIterator.cxx)
target_link_libraries(DepthFirstIterator PRIVATE graph::graph)
