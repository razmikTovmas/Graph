#include <iostream>

#include "graph.hpp"

int main()
{
    impl::graph g;

    g.add_edge("A", "B", 5);
    g.add_edge("A", "C", 2);
    g.add_edge("B", "D", 1);
    g.add_edge("D", "E", 3);
    g.add_edge("C", "E", 4);

    std::cout << "Size: " << g.size() << std::endl;

    g.dump(std::cout);

    const impl::node* from = g.get_node("A");
    const impl::node* to = g.get_node("C");

    impl::graph::size_type numOfPaths = g.num_of_paths(from, to);
    std::cout << "The number of paths from " << from << " to " << to << " is : " << numOfPaths << std::endl;

    return 0;
}
