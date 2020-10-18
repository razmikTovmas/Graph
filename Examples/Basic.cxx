#include <iostream>
#include <vector>

#include "Graph.hpp"

int main()
{
    std::cout << "Hello graph!" << std::endl;

    Graph g;
    std::cout << "Empty: " << g.IsEmpty() << std::endl;

    g.AddNode("A");
    g.AddNode("B");
    g.AddNode("C");

    std::cout << "Size: " << g.Size() << std::endl;

    g.AddEdge("A", "B", 3);
    g.AddEdge("A", "C", 1);
    g.AddEdge("A", "C", 2);
    g.AddEdge("B", "A", 1);
    g.AddEdge("C", "C", 5);

    g.Dump();

    return 0;
}