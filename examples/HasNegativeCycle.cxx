#include <iostream>

#include "core/graph.hpp"

int main()
{
    impl::graph g;

    g.add_edge("A", "B", -1);
    g.add_edge("A", "C", 4);
    g.add_edge("B", "C", 3);
    g.add_edge("B", "D", 2);
    g.add_edge("A", "E", 2);
    g.add_edge("D", "C", 5);
    g.add_edge("D", "B", 1);
    g.add_edge("E", "D", -3);

    std::cout << "Size: " << g.size() << std::endl;
    if (g.has_negative_cycle()) {
        std::cout << "Graph has negative cycle" << std::endl;
    } else {
        std::cout << "Graph doas not have negative cycle" << std::endl;
    }

    g.add_edge("D", "A", -1);
    if (g.has_negative_cycle()) {
        std::cout << "Graph has negative cycle" << std::endl;
    } else {
        std::cout << "Graph doas not have negative cycle" << std::endl;
    }

    return 0;
}
