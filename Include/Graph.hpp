#pragma once

#include <string>
#include <vector>
#include <map>

#include <cassert>

#include "Node.hpp"

/**
 * @class Graph
 * @brief Class representing a graph data structure.
 */
class Graph
{
private:
    constexpr static size_t INVALID_ID = std::numeric_limits<size_t>::max();

public:
    using NodeIter = std::vector<std::string>;
    using EdgeIter = std::vector<std::tuple<std::string, std::string, int>>;

public:
    /**
     * @brief Construct a new empty Graph object that doesn't have any nodes or edges.
     */
    Graph();

    /**
     * @brief Destroy the Graph object
     */
    ~Graph();

    /**
     * @brief Return number of nodes in the graph.
     */
    [[nodiscard]] inline size_t Size() const noexcept;

    /**
     * @brief Returns true if the graph is empty, false otherwise.
     */
    [[nodiscard]] inline bool IsEmpty() const noexcept;

    /**
     * @brief Return true if the name already maps to a node, false otherwise.
     */
    [[nodiscard]] inline bool Contains(const std::string& name) const;

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
     * @brief Return true if a connection or path exists between from and to nodes.
     */
    [[nodiscard]] inline bool HasEdge(const std::string& from, const std::string& to);

    /**
     * @brief Create an edge between from and to with the provided weight.
     * @details If either of the names is not already a member of the graph,
     *          create that node and add it to the graph first.
     * 
     * @return true if the edge was added successfully, false if the edge already
     *          exists (nothing happens in this case).
     */
    bool AddEdge(const std::string& from, const std::string& to, Edge::Cost_t cost = 1);

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
     * @brief Return an iterator that yields the node names (in no particular order).
     */
    NodeIter Nodes();

    /**
     * @brief Return all the edges as an iterator of Edges (named tuples) with values
     *        (from, to, weight). Edges are yielded in no particular order.
     */
    EdgeIter Edges();

    /**
     * @brief Dumps the graph object to ostream.
     */
    void Dump(std::ostream& os = std::cout) const;

private:
    [[nodiscard]] inline size_t getNodeId(const std::string& name) const;
    [[nodiscard]] inline Node* getNode(const std::string& name);
    [[nodiscard]] inline Node* getOrCreateNode(const std::string& name);

private:
    std::vector<Node*> m_adjList;
    //! TODO: Replace id with actual pointer, othervise need to update id.
    //!       Currently this is a bug.
    std::map<std::string, size_t> m_nameToId;

};

inline size_t Graph::getNodeId(const std::string& name) const
{
    auto it = m_nameToId.find(name);
    if (it != m_nameToId.end()) {
        return it->second;
    }
    return INVALID_ID;
}

inline Node* Graph::getNode(const std::string& name)
{
    const size_t id = getNodeId(name);
    if (INVALID_ID == id) {
        return nullptr;
    }
    return m_adjList[id];
}

inline Node* Graph::getOrCreateNode(const std::string& name)
{
    Node* node = getNode(name);
    if (nullptr != node) {
        return node;
    }
    const size_t id = m_adjList.size();
    node = new Node(id, name);
    m_adjList.push_back(node);
    m_nameToId.insert({name, id});
    return node;
}

Graph::Graph()
    : m_adjList{}
    , m_nameToId{}
{ }

Graph::~Graph()
{
    std::destroy(m_adjList.begin(), m_adjList.end());
}

inline size_t Graph::Size() const noexcept
{
    return m_adjList.size();
}

inline bool Graph::IsEmpty() const noexcept
{
    return 0 == Size();
}

inline bool Graph::Contains(const std::string& name) const
{
    return (m_nameToId.find(name) != m_nameToId.end());
}

bool Graph::AddNode(const std::string& name)
{
    if (Contains(name)) {
        return false;
    }
    const size_t id = m_adjList.size();
    Node* node = new Node(id, name);
    m_adjList.push_back(node);
    m_nameToId.insert({name, id});
    return true;
}

bool Graph::RemoveNode(const std::string& name)
{
    // Not implemented yet
    Node* node = getNode(name);
    if (nullptr == node) {
        return false;
    }

    size_t id = node->GetId();

    std::vector<Node*>::iterator iter = m_adjList.erase(m_adjList.begin() + id);
    std::cout << "New idx: " << std::distance(m_adjList.begin(), iter) << std::endl;
    std::cout << "Old idx: " << (*iter)->GetId() << std::endl;

    for (; iter != m_adjList.end(); ++iter, ++id) {
        (*iter)->SetId(id);
        (void)(*iter)->RemoveEdge(node);
    }

    return true;
}

inline bool Graph::HasEdge(const std::string& from, const std::string& to)
{
    Node* fromNode = getNode(from);
    Node* toNode = getNode(to);

    if (nullptr == fromNode || nullptr == toNode) {
        return false;
    }

    return fromNode->HasEdge(toNode);
}

bool Graph::AddEdge(const std::string& from, const std::string& to, Edge::Cost_t cost)
{
    Node* fromNode = getOrCreateNode(from);
    Node* toNode = getOrCreateNode(to);

    return fromNode->AddEdge(toNode, cost);
}

bool Graph::RemoveEdge(const std::string& from, const std::string& to)
{
    Node* fromNode = getNode(from);
    Node* toNode = getNode(to);

    return fromNode->RemoveEdge(toNode);
}

void Graph::Dump(std::ostream& os) const
{
    for (const auto* node : m_adjList) {
        node->Dump(os);
    }
}
