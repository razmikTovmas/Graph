#pragma once

#include <algorithm>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>

#include <cassert>

#include "node.hpp"

namespace impl
{

/**
 * @class graph
 * @brief Class representing a graph data structure.
 * 
 * @todo Add API to take iterators.
 */
class graph
{
public:
    //using value_type                = ;
    using size_type                 = std::size_t;

private:
    constexpr static size_type INVALID_ID = std::numeric_limits<size_type>::max();

public:
    using node_iterator = std::vector<node*>::iterator;
    using const_node_iterator = std::vector<node*>::const_iterator;
    using neighbor_node_iterator = node::node_iterator;
    using const_neighbor_node_iterator = node::const_node_iterator;

public:
    /**
     * @brief Construct a new empty graph object that doesn't have any nodes or edges.
     */
    graph();

    /**
     * @brief Destroy the graph object
     */
    ~graph();

    /**
     * @brief Return number of nodes in the graph.
     */
    [[nodiscard]] inline size_type size() const noexcept;

    /**
     * @brief Returns true if the graph is empty, false otherwise.
     */
    [[nodiscard]] inline bool empty() const noexcept;

    /**
     * @brief Return true if the name already maps to a node, false otherwise.
     */
    [[nodiscard]] inline bool contains(const std::string& name) const;

    /**
     * @brief Create a new node and add it to the graph.
     * @details Name must be a hashable type.
     * 
     * @return value indicates if a node was actually added, true means a new
     *  node was created and added, false means that a node with that name already
     *  exists in this graph, and it was not overwritten.
     */
    bool add_node(const std::string& name);

    /**
     * @brief Removes the node with the given name
     * 
     * @return value indicates if the node was actually removed, true means name
     *         maped to a node, and the node was removed, false otherwise.
     */
    bool remove_node(const std::string& name);

    /**
     * @brief Return true if a connection or path exists between from and to nodes.
     */
    [[nodiscard]] inline bool has_edge(const std::string& from, const std::string& to);

    /**
     * @brief Create an edge between from and to with the provided weight.
     * @details If either of the names is not already a member of the graph,
     *          create that node and add it to the graph first.
     * 
     * @return true if the edge was added successfully, false if the edge already
     *          exists (nothing happens in this case).
     */
    bool add_edge(const std::string& from, const std::string& to, edge::Cost_t cost = 1);

    /**
     * @brief Removes the edge between from and to nodes.
     * 
     * @return true if the edge existed and was removed successfully, false if
     *         either nodes or the edge was not found.
     */
    bool remove_edge(const std::string& from, const std::string& to);

    neighbor_node_iterator begin_neighbors(node* start) { return start->begin_nodes(); };
    neighbor_node_iterator begin_neighbors(const std::string& name) { return begin_neighbors(get_node(name)); };
    neighbor_node_iterator end_neighbors(node* start) { return start->end_nodes(); };
    neighbor_node_iterator end_neighbors(const std::string& name) { return end_neighbors(get_node(name)); };
    const_neighbor_node_iterator begin_neighbors(const node* start) const { return start->cbegin_nodes(); };
    const_neighbor_node_iterator begin_neighbors(const std::string& name) const { return begin_neighbors(get_node(name)); };
    const_neighbor_node_iterator end_neighbors(const node* start) const { return start->cend_nodes(); };
    const_neighbor_node_iterator end_neighbors(const std::string& name) const { return end_neighbors(get_node(name)); };
    const_neighbor_node_iterator cbegin_neighbors(const std::string& name) const { return begin_neighbors(name); };
    const_neighbor_node_iterator cend_neighbors(const std::string& name) const { return end_neighbors(name); };

    /**
     * @brief Return an iterator that yields the node names (in no particular order).
     */
    node_iterator begin_nodes() { return m_adjList.begin(); }
    node_iterator end_nodes() { return m_adjList.end(); }
    const_node_iterator begin_nodes() const { return m_adjList.cbegin(); }
    const_node_iterator end_nodes() const { return m_adjList.cend(); }
    const_node_iterator cbegin_nodes() const { return begin_nodes(); }
    const_node_iterator cend_nodes() const { return end_nodes(); }

    /**
     * @brief Return all the edges as an iterator of Edges (named tuples) with values
     *        (from, to, weight). Edges are yielded in no particular order.
     */
    //edge_iterator edges() const;

    /**
     * @brief Dumps the graph object to ostream.
     */
    void dump(std::ostream& os = std::cout) const;

public:
    ///@{ @name Algorithms
    /// @brief Algorithms to work with the graph.
    /**
     * @brief What is a Mother Vertex?
     * @details A mother vertex in a graph G = (V,E) is a vertex v such that all
     *          other vertices in G can be reached by a path from v.
     * 
     * @return const pointer to mother node if found, otherwise nullptr.
     */
    const node* mother_node() const;
    /**
     * @brief Count the total number of ways or paths that exist between two vertices in a directed graph.
     * @details These paths don’t contain a cycle, the simple enough reason is
     *          that a cycle contains an infinite number of paths and hence they create a problem.
     */
    size_type num_of_paths(const node* from, const node* to) const;
    ///@}

    /**
     * @class iterator
     * @brief Iterator class to provide DFS and BFS traversal functionality.
     */
    class iterator
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
        enum class iter_type
        {
            DFS,
            BFS
        };

    public:
        explicit iterator(const graph& g, node* n, iter_type type);
        ~iterator() = default;

        iterator& operator++();
        iterator operator++(int);

        //! NOTE: if iter_types are the same, and if nodes they point to
        //        are the same, they are equal
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
        reference operator*() const;

        [[nodiscard]] inline bool is_BFS() const noexcept { return iter_type::BFS == m_type; }
        [[nodiscard]] inline bool is_DFS() const noexcept { return iter_type::DFS == m_type; }

    private:
        void collect_nodes();

    private:
        iter_type m_type;
        node* m_node; // nullptr means the end of the graph
        std::vector<bool> m_visited;
        std::deque<node*> m_deque;
    };

    class const_iterator
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
        enum class iter_type
        {
            DFS,
            BFS
        };

    public:
        explicit const_iterator(const graph& g, const node* n, iter_type type);
        ~const_iterator() = default;

        const_iterator& operator++();
        const_iterator operator++(int);

        //! NOTE: if iter_types are the same, and if nodes they point to
        //        are the same, they are equal
        bool operator==(const const_iterator& other) const;
        bool operator!=(const const_iterator& other) const;
        const_reference operator*() const;

        [[nodiscard]] inline bool is_BFS() const noexcept { return iter_type::BFS == m_type; }
        [[nodiscard]] inline bool is_DFS() const noexcept { return iter_type::DFS == m_type; }

    private:
        void collect_nodes();

    private:
        iter_type m_type;
        const node* m_node; // nullptr means the end of the graph
        std::vector<bool> m_visited;
        std::deque<const node*> m_deque;
    };

    [[nodiscard]] iterator begin_BFS(size_type start) { return iterator(*this, get_node(start), iterator::iter_type::BFS); }
    [[nodiscard]] iterator begin_BFS(const std::string& name) { return iterator(*this, get_node(name), iterator::iter_type::BFS); }
    [[nodiscard]] iterator end_BFS() { return iterator(*this, nullptr, iterator::iter_type::BFS); }
    [[nodiscard]] iterator begin_DFS(size_type start) { return iterator(*this, get_node(start), iterator::iter_type::DFS); }
    [[nodiscard]] iterator begin_DFS(const std::string& name) { return iterator(*this, get_node(name), iterator::iter_type::DFS); }
    [[nodiscard]] iterator end_DFS() { return iterator(*this, nullptr, iterator::iter_type::DFS); }

    [[nodiscard]] const_iterator begin_BFS(size_type start) const { return const_iterator(*this, get_node(start), const_iterator::iter_type::BFS); }
    [[nodiscard]] const_iterator begin_BFS(const std::string& name) const { return const_iterator(*this, get_node(name), const_iterator::iter_type::BFS); }
    [[nodiscard]] const_iterator end_BFS() const { return const_iterator(*this, nullptr, const_iterator::iter_type::BFS); }
    [[nodiscard]] const_iterator begin_DFS(size_type start) const { return const_iterator(*this, get_node(start), const_iterator::iter_type::DFS); }
    [[nodiscard]] const_iterator begin_DFS(const std::string& name) const { return const_iterator(*this, get_node(name), const_iterator::iter_type::DFS); }
    [[nodiscard]] const_iterator end_DFS() const { return const_iterator(*this, nullptr, const_iterator::iter_type::DFS); }

    [[nodiscard]] const_iterator cbegin_BFS(size_type start) const { return begin_BFS(start); }
    [[nodiscard]] const_iterator cbegin_BFS(const std::string& name) const { return begin_BFS(name); }
    [[nodiscard]] const_iterator cend_BFS() const { return end_BFS(); }
    [[nodiscard]] const_iterator cbegin_DFS(size_type start) const { return begin_DFS(start); }
    [[nodiscard]] const_iterator cbegin_DFS(const std::string& name) const { return begin_DFS(name); }
    [[nodiscard]] const_iterator cend_DFS() const { return end_DFS(); }

    [[nodiscard]] inline node* get_node(const std::string& name);
    [[nodiscard]] inline const node* get_node(const std::string& name) const;

private:
    [[nodiscard]] inline size_type get_node_id(const std::string& name) const;
    [[nodiscard]] inline node* get_node(size_type start);
    [[nodiscard]] inline const node* get_node(size_type start) const;
    [[nodiscard]] inline node* get_or_create_node(const std::string& name);

private:
    std::vector<node*> m_adjList;
    std::map<std::string, node*> m_nameToId;

};

}

////////////////////////////////////////////////////////////////////////////////
////  Includes  ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include "_graph_iterator.hpp"
#include "_graph_impl.hpp"
#include "_mother_node.hpp"
#include "_num_of_paths.hpp"
