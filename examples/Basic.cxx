#include <iostream>

#include "core/graph.hpp"

int main()
{
    std::cout << "Hello graph!" << std::endl;

    impl::graph g;
    std::cout << "Empty: " << g.empty() << std::endl;

    g.add_node("A");
    g.add_node("B");
    g.add_node("C");

    g.add_edge("A", "B", 5);
    g.add_edge("A", "C", 2);
    g.add_edge("B", "D", 1);
    g.add_edge("D", "E", 3);
    g.add_edge("C", "E", 4);
    g.add_edge("E", "C", 3);
    g.add_edge("C", "A", 2);

    std::cout << "Size: " << g.size() << std::endl;
    g.dump(std::cout);

    return 0;
}
