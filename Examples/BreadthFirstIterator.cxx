#include <iostream>
#include <vector>

#include "Graph.hpp"

int main()
{
    std::cout << "BreadthFirstIterator!" << std::endl;

    Graph g;
    std::cout << "Empty: " << g.IsEmpty() << std::endl;

    g.AddNode("A");
    g.AddNode("B");
    g.AddNode("C");

    std::cout << "Size: " << g.Size() << std::endl;

    g.AddEdge("A", "B");
    g.AddEdge("A", "C");
    g.AddEdge("B", "D");
    g.AddEdge("D", "E");
    g.AddEdge("C", "E");
    g.AddEdge("E", "C");
    g.AddEdge("C", "A");

    Graph::BreadthFirstIterator iter(g, 2);

    while (iter.Next()) {
        std::cout << iter.Get()->GetName() << ' ';
    }
    std::cout << std::endl;

    return 0;
}