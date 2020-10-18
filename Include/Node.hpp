#pragma once

#include <string>
#include <vector>

#include <algorithm>

class Node
{
public:
    /**
     * @brief Construct a new Node object with the given id and name.
     */
    Node(size_t id, const std::string& name);

    /**
     * @brief Destroy the Node object
     */
    ~Node() = default;

    /**
     * @brief Get the id of the node.
     */
    [[nodiscard]] size_t GetId() const;

    /**
     * @brief Get the name of the node.
     */
    [[nodiscard]] const std::string& GetName() const;

    [[nodiscard]] inline bool AddEdge(Node* to, int cost = 1);
    [[nodiscard]] inline bool HasEdge(Node* to);
    [[nodiscard]] inline bool HasEdge(const std::string& to);

    void Dump(std::ostream &os) const;

private:
    size_t m_id;
    std::string m_name;
    std::vector<std::pair<Node*, int>> m_nodes;
};

Node::Node(size_t id, const std::string& name)
    : m_id(id)
    , m_name(name)
{ }

bool Node::HasEdge(Node* to)
{
    return std::find_if(m_nodes.begin(), m_nodes.end(), [to](auto& pair) { return pair.first == to; }) != m_nodes.end();
}

bool Node::AddEdge(Node* to, int cost)
{
    if (HasEdge(to)) {
        return false;
    }
    m_nodes.push_back({to, cost});
    return true;
}

void Node::Dump(std::ostream &os) const
{
    os << m_name << ":" << std::endl;
    for (auto [node, cost] : m_nodes) {
        os << "  to: " << node->m_name << ", cost: " << cost << std::endl;
    }
}
