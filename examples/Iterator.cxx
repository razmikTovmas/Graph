#include <iostream>
#include <vector>

#include "core/graph.hpp"

int main()
{
    std::cout << "DepthFirstIterator!" << std::endl;

    impl::graph g;
    std::cout << "Empty: " << g.empty() << std::endl;

    g.add_node("A");
    g.add_node("B");
    g.add_node("C");

    g.add_edge("A", "B");
    g.add_edge("A", "C");
    g.add_edge("B", "D");
    g.add_edge("D", "E");
    g.add_edge("C", "E");
    g.add_edge("E", "C");
    g.add_edge("C", "A");

    std::cout << "Size: " << g.size() << std::endl;

    g.dump(std::cout);

    std::cout << "BFS: ";
    for (auto it = g.begin_BFS(2); it != g.end_BFS(); ++it) {
        std::cout << (*it).get_name() << ' ';
    }
    std::cout << std::endl;
    std::cout << "DFS: ";
    for (auto it = g.begin_DFS(2); it != g.end_DFS(); ++it) {
        std::cout << (*it).get_name() << ' ';
    }
    std::cout << std::endl;

    return 0;
}
