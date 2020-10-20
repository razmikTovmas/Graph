#include <iostream>
#include <vector>

#include "Graph.hpp"

int main()
{
    std::cout << "DepthFirstIterator!" << std::endl;

    Graph g;
    std::cout << "Empty: " << g.IsEmpty() << std::endl;

    g.AddNode("A");
    g.AddNode("B");
    g.AddNode("C");

    g.AddEdge("A", "B");
    g.AddEdge("A", "C");
    g.AddEdge("B", "D");
    g.AddEdge("D", "E");
    g.AddEdge("C", "E");
    g.AddEdge("E", "C");
    g.AddEdge("C", "A");

    std::cout << "Size: " << g.Size() << std::endl;

    g.Dump();

    std::cout << "BFS: ";
    for (auto it = g.BeginBFS(2); it != g.EndBFS(); ++it) {
        std::cout << (*it).GetName() << ' ';
    }
    std::cout << std::endl;
    std::cout << "DFS: ";
    for (auto it = g.BeginDFS(2); it != g.EndDFS(); ++it) {
        std::cout << (*it).GetName() << ' ';
    }
    std::cout << std::endl;

    return 0;
}