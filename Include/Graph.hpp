#pragma once

#include <string>

/**
 * @class Graph
 * @brief Class representing a graph data structure.
 */
class Graph
{
public:
    /**
     * @brief Construct a new empty Graph object that doesn't have any nodes or edges.
     */
    Graph();

    /**
     * @brief Return number of nodes in the graph.
     */
    size_t Size() const;

    /**
     * @brief Returns true if the graph is empty, false otherwise.
     */
    bool IsEmpty() const;

    /**
     * @brief Create a new node and add it to the graph.
     * @details Name must be a hashable type.
     * 
     * @return value indicates if a node was actually added, true means a new
     *  node was created and added, false means that a node with that name already
     *  exists in this graph, and it was not overwritten.
     */
    bool AddNode(const std::string& name);

    /**
     * @brief Removes the node with the given name
     * 
     * @return value indicates if the node was actually removed, true means name
     *         maped to a node, and the node was removed, false otherwise.
     */
    bool RemoveNode(const std::string& name);

    /**
     * @brief Create an edge between from and to with the provided weight.
     * @details If either of the names is not already a member of the graph,
     *          create that node and add it to the graph first.
     * 
     * @return true if the edge was added successfully, false if the edge already
     *          exists (nothing happens in this case).
     */
    bool AddEdge(const std::string from, const std::string to, int weight = 1);

    /**
     * @brief Removes the edge between from and to nodes.
     * 
     * @return true if the edge existed and was removed successfully, false if
     *         either nodes or the edge was not found.
     */
    bool RemoveEdge(const std::string& from, const std::string& to);

    /**
     * @brief Return an iterator that yields (name, weight) of all the neighboring nodes.
     */
    NodeIter Neighbors(const std::string& from_name);

    /**
     * @brief Return true if the name already maps to a node, false otherwise.
     */
    bool Contains(const std::string& name) const;

    /**
     * @brief Return true if a connection or path exists between from and to nodes.
     */
    bool HasEdge(const std::string& from, const std::string& to) const;

    /**
     * @brief Return an iterator that yields the node names (in no particular order).
     */
    NodeIter Nodes();

    /**
     * @brief Return all the edges as an iterator of Edges (named tuples) with values
     *        (from, to, weight). Edges are yielded in no particular order.
     */
    EdgeIter Edges();

private:


};
