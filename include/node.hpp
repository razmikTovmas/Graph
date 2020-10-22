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
    [[nodiscard]] inline size_t get_id() const { return m_id; };

    /**
     * @brief Update the id of the node.
     */
    void set_id(size_t id) { m_id = id; }

    /**
     * @brief Get the name of the node.
     */
    [[nodiscard]] inline const std::string& get_name() const { return m_name; }

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

    /**
     * @brief Dumps the node object to ostream.
     */
    void dump(std::ostream &os) const;

private:
    const std::vector<edge*>& get_edges() { return m_edges; }

    std::vector<edge*>::iterator begin() { return m_edges.begin(); }
    std::vector<edge*>::iterator end() { return m_edges.end(); }

public:
    /**
     * @brief Return an iterator that yields (name, weight) of all the neighboring nodes.
     */
    class node_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = node;
        using difference_type = size_t;
        using pointer = node*;
        using reference = node&;
    public:
        node_iterator(std::vector<edge*>::iterator iter);

        ~node_iterator() = default;

        node_iterator& operator++();
        node_iterator operator++(int);

        //! NOTE: if iter_types are the same, and if nodes they point to
        //        are the same, they are equal
        bool operator==(const node_iterator& other) const;
        bool operator!=(const node_iterator& other) const;
        pointer operator*() const;

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

}

////////////////////////////////////////////////////////////////////////////////
////  Includes  ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include "_node_iterator.hpp"
#include "_node_impl.hpp"
