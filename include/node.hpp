#pragma once

#include <string>
#include <utility>
#include <vector>

#include <algorithm>

#include "edge.hpp"

namespace impl
{

/**
 * @class node
 * @brief node object of the graph data structure.
 * @note Supports multigraph
 */
class node
{
public:
    /**
     * @brief Construct a new node object with the given id and name.
     */
    node(size_t id, std::string  name);

    /**
     * @brief Destroy the node object.
     */
    ~node();

    /**
     * @brief Get the id of the node.
     */
    [[nodiscard]] size_t get_id() const { return m_id; };

    /**
     * @brief Update the id of the node.
     */
    void set_id(size_t id) { m_id = id; }

    /**
     * @brief Get the name of the node.
     */
    [[nodiscard]] const std::string& get_name() const { return m_name; }

    /**
     * @brief Add edge to the destinaion node with the given cost.
     * 
     * @return true if the edge was added successfully, otherwise false.
     */
    [[nodiscard]] bool add_edge(node* to, edge::Cost_t cost = 1);

    /**
     * @brief Checks weather the edge exists from the current node to the given.
     */
    [[nodiscard]] inline bool has_edge(node* to) const;

    /**
     * @brief Removes the edge if exists.
     * @return true if the edge was removed, false if does not exist.
     */
    [[nodiscard]] inline bool remove_edge(node* to);

    std::vector<edge*>::iterator begin() { return m_edges.begin(); }
    std::vector<edge*>::iterator end() { return m_edges.end(); }

    const std::vector<edge*>& get_edges() { return m_edges; }


    /**
     * @brief Dumps the node object to ostream.
     */
    void dump(std::ostream &os) const;

    class node_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = node;
        using difference_type = size_t;
        using pointer = node*;
        using reference = node&;
    public:
        node_iterator(std::vector<edge*>::iterator iter)
            : m_iter(iter)
        { }

        ~node_iterator() = default;

        node_iterator& operator++()
        {
            ++m_iter;
            return *this;
        }
        node_iterator operator++(int)
        {
            node_iterator temp{*this};
            ++m_iter;
            return temp;
        }

        //! NOTE: if iter_types are the same, and if nodes they point to
        //        are the same, they are equal
        bool operator==(const node_iterator& other) const { return m_iter == other.m_iter; }
        bool operator!=(const node_iterator& other) const { return m_iter != other.m_iter; }
        pointer operator*() const { return (*m_iter)->get_to(); }

    private:
        std::vector<edge*>::iterator m_iter;
    };

    node_iterator begin_nods() { return node_iterator(m_edges.begin()); }
    node_iterator end_nods() { return node_iterator(m_edges.end()); }

private:
    size_t m_id;
    const std::string m_name;
    std::vector<edge*> m_edges;

};

node::node(size_t id, std::string  name)
    : m_id(id)
    , m_name(std::move(name))
{ }

node::~node()
{
    std::destroy(m_edges.begin(), m_edges.end());
}

inline bool node::has_edge(node* to) const
{
    for (auto& edge : m_edges) {
        if (to == edge->get_to()) {
            return true;
        }
    }
    return false;
}

bool node::add_edge(node* to, edge::Cost_t cost)
{
    // if (std::find(m_edges.begin(), m_edges.end(), edge) != m_edges.end()) {
    //     return false;
    // }
    // (from, to) can repeat - supports multigraph (not sure if I need this)
    edge* e = new edge(this, to, cost);
    m_edges.push_back(e);
    return true;
}

bool node::remove_edge(node* to)
{
    for (auto it = m_edges.begin(); it != m_edges.end(); ++it) {
        if (to == (*it)->get_to()) {
            m_edges.erase(it);
            return true;
        }
    }
    return false;
}

void node::dump(std::ostream &os) const
{
    os << m_name << ":" << std::endl;
    for (auto& edge : m_edges) {
        os << "  to: " << edge->get_to()->get_name()
           << ", cost: " << edge->get_cost() << std::endl;
    }
}
}
