#pragma once

#include <string>
#include <vector>

#include <algorithm>

/**
 * @class Node
 * @brief Node object of the graph data structure.
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
    [[nodiscard]] const std::string& GetName() const;

    /**
     * @brief Add edge to the destinaion node with the given cost.
     * 
     * @return true if the edge was added successfully, otherwise false.
     */
    [[nodiscard]] inline bool AddEdge(Node* to, int cost = 1);

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
    std::vector<std::pair<Node*, int>> m_neighbors;

};

Node::Node(size_t id, const std::string& name)
    : m_id(id)
    , m_name(name)
{ }

bool Node::HasEdge(Node* to) const
{
    return std::find_if(m_neighbors.begin(), m_neighbors.end(), [to](auto& pair) { return pair.first == to; }) != m_neighbors.end();
}

bool Node::AddEdge(Node* to, int cost)
{
    if (HasEdge(to)) {
        return false;
    }
    m_neighbors.push_back({to, cost});
    return true;
}

inline bool Node::RemoveEdge(Node* to)
{
    auto it = std::find_if(m_neighbors.begin(), m_neighbors.end(), [to](auto& pair) { return pair.first == to; });
    if (m_neighbors.end() != it) {
        m_neighbors.erase(it);
        return true;
    }
    return false;
}

void Node::Dump(std::ostream &os) const
{
    os << m_name << ":" << std::endl;
    for (auto [node, cost] : m_neighbors) {
        os << "  to: " << node->m_name << ", cost: " << cost << std::endl;
    }
}
