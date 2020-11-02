#pragma once

#include <tuple>
#include <limits>

#include <string>
#include <utility>
#include <vector>

#include <algorithm>

namespace impl
{
class node;

class edge
{
public:
    using Cost_t = int;
    constexpr static Cost_t INF_COST = std::numeric_limits<Cost_t>::max();

public:
    edge(node* from, node* to, Cost_t cost)
        : m_from{from}
        , m_to{to}
        , m_cost{cost}
    { }

    ~edge() = default;

    inline void set_from(node* from) noexcept { m_from = from; }
    inline void set_to(node* to) noexcept { m_to = to; }

    [[nodiscard]] inline const node* get_from() const noexcept { return m_from; }
    [[nodiscard]] inline node* get_from() noexcept { return m_from; }
    [[nodiscard]] inline const node* get_to() const noexcept { return m_to; }
    [[nodiscard]] inline node* get_to() noexcept { return m_to; }

    [[nodiscard]] inline size_t get_from_idx() const noexcept;
    [[nodiscard]] inline size_t get_to_idx() const noexcept;

    inline void set_cost(Cost_t cost) noexcept { m_cost = cost; }
    [[nodiscard]] inline Cost_t get_cost() const noexcept { return m_cost; }

    [[nodiscard]] bool compare(const edge* rhs) const noexcept;

private:
    node* m_from;
    node* m_to;
    Cost_t m_cost;

};

/**
 * @class node
 * @brief node object of the graph data structure.
 * @note Supports multigraph
 */
class node
{
public:
    using size_type = std::size_t;
    using edge_iterator = std::vector<edge*>::iterator;
    using const_edge_iterator = std::vector<edge*>::const_iterator;

public:
    node(size_type id);
    /**
     * @brief Construct a new node object with the given id and name.
     */
    node(size_type id, std::string  name);

    /**
     * @brief Destroy the node object.
     */
    ~node();

    size_type degree() const { return m_edges.size(); }

    /**
     * @brief Get the id of the node.
     */
    [[nodiscard]] inline size_type get_id() const { return m_id; };

    /**
     * @brief Update the id of the node.
     */
    void set_id(size_type id) { m_id = id; }

    /**
     * @brief Get the name of the node.
     */
    [[nodiscard]] inline const std::string& get_name() const { return m_name; }

    /**
     * @brief Update the name of the node.
     */
    inline void set_name(std::string name) {  m_name = std::move(name); }

    [[nodiscard]] inline edge* get_edge(size_type idx) { return m_edges[idx]; }
    [[nodiscard]] inline const edge* get_edge(size_type idx) const { return m_edges[idx]; }

    /**
     * @brief Add edge to the destinaion node with the given cost.
     * 
     * @return pointer to edge if it was added successfully, otherwise nullptr.
     */
    [[nodiscard]] edge* add_edge(node* to, edge::Cost_t cost = 1);

    /**
     * @brief Checks weather the edge exists from the current node to the given.
     */
    [[nodiscard]] inline bool has_edge(node* to) const;

    /**
     * @brief Removes the edge if exists.
     * @return true if the edge was removed, false if does not exist.
     */
    [[nodiscard]] inline bool remove_edge(node* to);

    [[nodiscard]] bool compare(const node* rhs) const;

    /**
     * @brief Dumps the node object to ostream.
     */
    void dump(std::ostream &os) const;

    std::vector<edge*>::iterator begin_edges() { return m_edges.begin(); }
    std::vector<edge*>::iterator end_edges() { return m_edges.end(); }

    const size_type get_num_of_edges() const { return m_edges.size(); }
    const std::vector<edge*>& get_edges() const { return m_edges; }

public:
    /**
     * @brief Iterator class of all the neighboring nodes.
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

    /**
     * @brief Const iterator class of all the neighboring nodes.
     */
    class const_node_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = node;
        using difference_type = size_t;
        using pointer = node*;
        using const_pointer = const node*;
        using reference = node&;
        using const_reference = const node&;
    public:
        const_node_iterator(std::vector<edge*>::const_iterator iter);

        ~const_node_iterator() = default;

        const_node_iterator& operator++();
        const_node_iterator operator++(int);

        //! NOTE: if iter_types are the same, and if nodes they point to
        //        are the same, they are equal
        bool operator==(const const_node_iterator& other) const;
        bool operator!=(const const_node_iterator& other) const;
        const_pointer operator*() const;

    private:
        std::vector<edge*>::const_iterator m_iter;
    };

    node_iterator begin_nodes() { return node_iterator(m_edges.begin()); }
    node_iterator end_nodes() { return node_iterator(m_edges.end()); }

    const_node_iterator begin_nodes() const { return const_node_iterator(m_edges.cbegin()); }
    const_node_iterator end_nodes() const { return const_node_iterator(m_edges.cend()); }

    const_node_iterator cbegin_nodes() const { return begin_nodes(); }
    const_node_iterator cend_nodes() const { return end_nodes(); }

private:
    size_type m_id;
    std::string m_name;
    std::vector<edge*> m_edges;

};


}

std::ostream& operator<<(std::ostream& os, const impl::node* node);

////////////////////////////////////////////////////////////////////////////////
////  Includes  ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include "_node_iterator.hpp"
#include "_widgets_impl.hpp"
