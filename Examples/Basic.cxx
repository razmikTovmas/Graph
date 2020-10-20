#include <iostream>

#include "Graph.hpp"

int main()
{
    std::cout << "Hello graph!" << std::endl;

    Graph g;
    std::cout << "Empty: " << g.IsEmpty() << std::endl;

    g.AddNode("A");
    g.AddNode("B");
    g.AddNode("C");

    g.AddEdge("A", "B", 5);
    g.AddEdge("A", "C", 2);
    g.AddEdge("B", "D", 1);
    g.AddEdge("D", "E", 3);
    g.AddEdge("C", "E", 4);
    g.AddEdge("E", "C", 3);
    g.AddEdge("C", "A", 2);

    std::cout << "Size: " << g.Size() << std::endl;
    g.Dump();

    return 0;
}
