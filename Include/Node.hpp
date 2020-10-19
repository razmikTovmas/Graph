#pragma once

#include <string>
#include <vector>

#include <algorithm>

#include "Edge.hpp"

/**
 * @class Node
 * @brief Node object of the graph data structure.
 * @note Supports multigraph
 */
class Node
{
public:
    /**
     * @brief Construct a new Node object with the given id and name.
     */
    Node(size_t id, const std::string& name);

    /**
     * @brief Destroy the Node object.
     */
    ~Node() = default;

    /**
     * @brief Get the id of the node.
     */
    [[nodiscard]] size_t GetId() const { return m_id; };

    /**
     * @brief Update the id of the node.
     */
    void SetId(size_t id) { m_id = id; }

    /**
     * @brief Get the name of the node.
     */
    [[nodiscard]] const std::string& GetName() const { return m_name; }

    /**
     * @brief Add edge to the destinaion node with the given cost.
     * 
     * @return true if the edge was added successfully, otherwise false.
     */
    [[nodiscard]] bool AddEdge(Node* to, Edge::Cost_t cost = 1);

    /**
     * @brief Checks weather the edge exists from the current node to the given.
     */
    [[nodiscard]] inline bool HasEdge(Node* to) const;

    /**
     * @brief Removes the edge if exists.
     * @return true if the edge was removed, false if does not exist.
     */
    [[nodiscard]] inline bool RemoveEdge(Node* to);

    /**
     * @brief Dumps the node object to ostream.
     */
    void Dump(std::ostream &os) const;

private:
    size_t m_id;
    const std::string m_name;
    std::vector<Edge*> m_edges;

};

Node::Node(size_t id, const std::string& name)
    : m_id(id)
    , m_name(name)
{ }

inline bool Node::HasEdge(Node* to) const
{
    for (auto& edge : m_edges) {
        if (to == edge->GetTo()) {
            return true;
        }
    }
    return false;
}

bool Node::AddEdge(Node* to, Edge::Cost_t cost)
{
    // if (std::find(m_edges.begin(), m_edges.end(), edge) != m_edges.end()) {
    //     return false;
    // }
    // (from, to) can repeat - supports multigraph (not sure if I need this)
    Edge* edge = new Edge(this, to, cost);
    m_edges.push_back(edge);
    return true;
}

bool Node::RemoveEdge(Node* to)
{
    for (auto it = m_edges.begin(); it != m_edges.end(); ++it) {
        if (to == (*it)->GetTo()) {
            m_edges.erase(it);
            return true;
        }
    }
    return false;
}

void Node::Dump(std::ostream &os) const
{
    os << m_name << ":" << std::endl;
    for (auto& edge : m_edges) {
        os << "  to: " << edge->GetTo()->GetName()
           << ", cost: " << edge->GetCost() << std::endl;
    }
}
