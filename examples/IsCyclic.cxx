#include <iostream>

#include "core/graph.hpp"

int main()
{
    impl::graph g;

    g.add_edge("A", "B", 5);
    g.add_edge("A", "C", 2);
    g.add_edge("B", "D", 1);
    g.add_edge("D", "E", 3);
    g.add_edge("C", "E", 4);
    g.add_edge("E", "A", 1);

    std::cout << "Size: " << g.size() << std::endl;

    g.dump(std::cout);

    if (g.is_cyclic()) {
        std::cout << "Graph is cyclic" << std::endl;
    } else {
        std::cout << "Graph is not cyclic" << std::endl;
    }

    return 0;
}
