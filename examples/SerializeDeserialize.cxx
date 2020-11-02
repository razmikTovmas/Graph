#include <iostream>

#include "graph.hpp"

int main()
{
    impl::graph g;

    g.add_edge("A", "B", 5);
    g.add_edge("A", "C", 2);
    g.add_edge("B", "D", 1);
    g.add_edge("C", "E", 4);
    g.add_edge("D", "E", 3);
    g.add_edge("E", "A", 1);

    g.serialize("graph.txt");
    impl::graph g1;
    g1.deserialize("graph.txt");

    if (g.compare(&g1)) {
        std::cout << "Graphs are the same" << std::endl;
    } else {
        std::cout << "Graphs are not the same" << std::endl;
    }

    return 0;
}
