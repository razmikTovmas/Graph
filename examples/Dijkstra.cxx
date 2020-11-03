#include <iostream>

#include "graph.hpp"

int main()
{
    impl::graph g;

    g.add_edge("A", "B", 5);
    g.add_edge("A", "C", 2);
    g.add_edge("B", "D", 1);
    g.add_edge("D", "E", 3);
    g.add_edge("C", "E", 3);
    g.add_edge("E", "A", 1);

    std::cout << "Size: " << g.size() << std::endl;

    g.dump(std::cout);
    for (auto cost : g.dijkstra(0)) {
        std::cout << "Cost: " << cost << std::endl;
    }

    return 0;
}
