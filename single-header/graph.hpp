#pragma once

#include <algorithm>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <cassert>

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

namespace impl
{

node::node_iterator::node_iterator(std::vector<edge*>::iterator iter)
    : m_iter(iter)
{ }

node::node_iterator& node::node_iterator::operator++()
{
    ++m_iter;
    return *this;
}

node::node_iterator node::node_iterator::operator++(int)
{
    node_iterator temp{*this};
    ++m_iter;
    return temp;
}

//! NOTE: if iter_types are the same, and if nodes they point to
//        are the same, they are equal
bool node::node_iterator::operator==(const node_iterator& other) const
{
    return m_iter == other.m_iter;
}

bool node::node_iterator::operator!=(const node_iterator& other) const
{
    return m_iter != other.m_iter;
}

node::node_iterator::pointer node::node_iterator::operator*() const
{
    return (*m_iter)->get_to();
}

///////////////////////////////

node::const_node_iterator::const_node_iterator(std::vector<edge*>::const_iterator iter)
    : m_iter(iter)
{ }

node::const_node_iterator& node::const_node_iterator::operator++()
{
    ++m_iter;
    return *this;
}

node::const_node_iterator node::const_node_iterator::operator++(int)
{
    const_node_iterator temp{*this};
    ++m_iter;
    return temp;
}

//! NOTE: if iter_types are the same, and if nodes they point to
//        are the same, they are equal
bool node::const_node_iterator::operator==(const const_node_iterator& other) const
{
    return m_iter == other.m_iter;
}

bool node::const_node_iterator::operator!=(const const_node_iterator& other) const
{
    return m_iter != other.m_iter;
}

node::const_node_iterator::const_pointer node::const_node_iterator::operator*() const
{
    return (*m_iter)->get_to();
}

}

namespace impl
{

inline size_t edge::get_from_idx() const noexcept
{
    return m_from->get_id();
}

inline size_t edge::get_to_idx() const noexcept
{
    return m_to->get_id();
}

bool edge::compare(const edge* e) const noexcept
{
    assert(nullptr != e);
    return (m_from == e->m_from && m_to == e->m_to && m_cost == e->m_cost);
}

node::node(size_type id)
    : m_id(id)
{ }

node::node(size_type id, std::string name)
    : m_id(id)
    , m_name(std::move(name))
{ }

node::~node()
{
    std::destroy(m_edges.begin(), m_edges.end());
}

inline bool node::has_edge(node* to) const
{
    for (const edge* edge : m_edges) {
        if (to == edge->get_to()) {
            return true;
        }
    }
    return false;
}

edge* node::add_edge(node* to, edge::Cost_t cost)
{
    // if (std::find(m_edges.begin(), m_edges.end(), edge) != m_edges.end()) {
    //     return false;
    // }
    // (from, to) can repeat - supports multigraph (not sure if I need this)
    edge* e = new edge(this, to, cost);
    m_edges.push_back(e);
    return e;
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

bool node::compare(const node* n) const
{
    assert(nullptr != n);
    if (degree() != n->degree()) {
        return false;
    }
    for (size_type i = 0; i < degree(); ++i) {
        const edge* lhs = get_edge(i);
        const edge* rhs = n->get_edge(i);
        if (!lhs->compare(rhs)) {
            return false;
        }
    }
    return true;
}

void node::dump(std::ostream &os) const
{
    os << this << ":" << std::endl;
    for (auto& edge : m_edges) {
        os << "  to: " << edge->get_to()
           << ", cost: " << edge->get_cost() << std::endl;
    }
}

}

std::ostream& operator<<(std::ostream& os, const impl::node* node)
{
    if (nullptr == node) {
        os << "'nullptr'";
    } else {
        os << '\'' << node->get_name() << '\'';
    }
    return os;
}

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
    using edge_iterator = std::vector<const edge*>::iterator;
    using const_edge_iterator = std::vector<const edge*>::const_iterator;

public:
    /**
     * @brief Construct a new empty graph object that doesn't have any nodes or edges.
     */
    graph();

    graph(graph&& other);

    /**
     * @brief Destroy the graph object
     */
    ~graph();

    void clear();

    /**
     * @brief Return number of nodes in the graph.
     */
    [[nodiscard]] inline size_type size() const noexcept;

    /**
     * @brief Return number of edges in the graph.
     */
    [[nodiscard]] inline size_type num_of_edges() const noexcept { return m_edges.size(); }

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

    [[nodiscard]] bool compare(const graph* g) const;

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
    void dump(std::ostream& os) const;

    void serialize(const std::string& fileName) const;
    void deserialize(const std::string& fileName);

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
    [[nodiscard]] const node* mother_node() const;
    /**
     * @brief Count the total number of ways or paths that exist between two vertices in a directed graph.
     * @details These paths don’t contain a cycle, the simple enough reason is
     *          that a cycle contains an infinite number of paths and hence they create a problem.
     */
    [[nodiscard]] size_type num_of_paths(const node* from, const node* to) const;

    /**
     * @brief Given a directed graph, check whether the graph contains a cycle or not.
     */
    [[nodiscard]] bool is_cyclic() const;

    /**
     * @brief Given a graph and a source vertex in the graph, find shortest paths
     *        from source to all vertices in the given graph.
     * 
     * @return vector of costs from source to all nodes.
     */
    [[nodiscard]] std::vector<edge::Cost_t> dijkstra(size_type start) const;

    /**
     * @brief Given a directed graph, check whether the graph contains a negative cycle or not.
     */
    [[nodiscard]] bool has_negative_cycle() const;
    ///@}

private:
    ///@{ @name Algorithms Utils
    bool is_cyclic_util(size_type i, std::vector<bool>& visited, std::vector<bool>& stack) const;
    ///@}

public:
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

    [[nodiscard]] edge_iterator begin_edges() { return m_edges.begin(); }
    [[nodiscard]] edge_iterator end_edges() { return m_edges.end(); }
    [[nodiscard]] const_edge_iterator begin_edges() const { return m_edges.cbegin(); }
    [[nodiscard]] const_edge_iterator end_edges() const { return m_edges.cend(); }
    [[nodiscard]] const_edge_iterator cbegin_edges() const { return begin_edges(); }
    [[nodiscard]] const_edge_iterator cend_edges() const { return end_edges(); }

    [[nodiscard]] inline node* get_node(const std::string& name);
    [[nodiscard]] inline const node* get_node(const std::string& name) const;

private:
    [[nodiscard]] inline size_type get_node_id(const std::string& name) const;
    [[nodiscard]] inline node* get_node(size_type start);
    [[nodiscard]] inline const node* get_node(size_type start) const;
    [[nodiscard]] inline node* get_or_create_node(const std::string& name);
    [[nodiscard]] inline bool add_edge(node* fromNode, node* toNode, edge::Cost_t cost);
    inline void add_edge(edge* e);

private:
    std::vector<node*> m_adjList;
    std::vector<const edge*> m_edges;
    std::map<std::string, node*> m_nameToNode;

};

}

////////////////////////////////////////////////////////////////////////////////
////  Includes  ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace impl
{

////////////////////////////////////////////////////////////////////////////////
///// graph::iterator
////////////////////////////////////////////////////////////////////////////////
graph::iterator::iterator(const graph& g, node* n, iter_type type)
    : m_type(type)
    , m_node(n)
    , m_visited(g.size(), false)
    , m_deque()
{
    if (nullptr != m_node) {
        m_visited[m_node->get_id()] = true;
        collect_nodes();
    }
}

graph::iterator& graph::iterator::operator++()
{
    if (m_deque.empty()) {
        m_node = nullptr;
        return *this;
    }

    if (iter_type::BFS == m_type) {
        m_node = m_deque.front();
        m_deque.pop_front();
    } else {
        m_node = m_deque.back();
        m_deque.pop_back();
    }
    collect_nodes();

    return *this;
}

graph::iterator graph::iterator::operator++(int)
{
    iterator tmp = *this;
    ++*this;
    return tmp;
}

bool graph::iterator::operator==(const iterator& other) const
{
    return (m_type == other.m_type && m_node == other.m_node);
}

bool graph::iterator::operator!=(const iterator& other) const
{
    return !(other == *this);
}

graph::iterator::reference graph::iterator::operator*() const
{
    return *m_node;
}

void graph::iterator::collect_nodes()
{
    assert(nullptr != m_node);
    //for (auto* edge : m_node->get_edges()) {
    for (auto it = m_node->begin_nodes(); it != m_node->end_nodes(); ++it) {
        node* to = *it;
        const graph::size_type id = to->get_id();
        if (!m_visited[id]) {
            m_visited[id] = true;
            m_deque.push_back(to);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
graph::const_iterator::const_iterator(const graph& g, const node* n, iter_type type)
    : m_type(type)
    , m_node(n)
    , m_visited(g.size(), false)
    , m_deque()
{
    if (nullptr != m_node) {
        m_visited[m_node->get_id()] = true;
        collect_nodes();
    }
}

graph::const_iterator& graph::const_iterator::operator++()
{
    if (m_deque.empty()) {
        m_node = nullptr;
        return *this;
    }

    if (iter_type::BFS == m_type) {
        m_node = m_deque.front();
        m_deque.pop_front();
    } else {
        m_node = m_deque.back();
        m_deque.pop_back();
    }
    collect_nodes();

    return *this;
}

graph::const_iterator graph::const_iterator::operator++(int)
{
    const_iterator tmp = *this;
    ++*this;
    return tmp;
}

bool graph::const_iterator::operator==(const const_iterator& other) const
{
    return (m_type == other.m_type && m_node == other.m_node);
}

bool graph::const_iterator::operator!=(const const_iterator& other) const
{
    return !(other == *this);
}

graph::const_iterator::const_reference graph::const_iterator::operator*() const
{
    return *m_node;
}

void graph::const_iterator::collect_nodes()
{
    assert(nullptr != m_node);
    //for (auto* edge : m_node->get_edges()) {
    for (auto it = m_node->begin_nodes(); it != m_node->end_nodes(); ++it) {
        const node* to = *it;
        const graph::size_type id = to->get_id();
        if (!m_visited[id]) {
            m_visited[id] = true;
            m_deque.push_back(to);
        }
    }
}

}

namespace impl
{

////////////////////////////////////////////////////////////////////////////////
///// graph
////////////////////////////////////////////////////////////////////////////////
inline size_t graph::get_node_id(const std::string& name) const
{
    auto it = m_nameToNode.find(name);
    if (it != m_nameToNode.end()) {
        return it->second->get_id();
    }
    return INVALID_ID;
}

inline node* graph::get_node(const std::string& name)
{
    auto it = m_nameToNode.find(name);
    if (it != m_nameToNode.end()) {
        return it->second;
    }
    return nullptr;
}

inline const node* graph::get_node(const std::string& name) const
{
    auto it = m_nameToNode.find(name);
    if (it != m_nameToNode.end()) {
        return it->second;
    }
    return nullptr;
}

inline node* graph::get_node(size_t start)
{
    if (start >= size()) {
        return nullptr;
    }
    return m_adjList[start];
}

inline const node* graph::get_node(size_t start) const
{
    if (start >= size()) {
        return nullptr;
    }
    return m_adjList[start];
}

inline node* graph::get_or_create_node(const std::string& name)
{
    node* n = get_node(name);
    if (nullptr != n) {
        return n;
    }
    const size_t id = m_adjList.size();
    n = new node(id, name);
    m_adjList.push_back(n);
    m_nameToNode.insert({name, n});
    return n;
}

inline void graph::add_edge(edge* e)
{
    m_edges.push_back(e);
}

bool graph::add_edge(node* fromNode, node* toNode, edge::Cost_t cost)
{
    edge* e = fromNode->add_edge(toNode, cost);
    if (e == nullptr) {
        return false;
    }

    add_edge(e);
    return true;
}

graph::graph()
    : m_adjList{}
    , m_edges{}
    , m_nameToNode{}
{ }

graph::graph(graph&& other)
    : m_adjList(std::move(other.m_adjList))
    , m_nameToNode(std::move(other.m_nameToNode))
{
    other.m_adjList.clear();
    other.m_nameToNode.clear();
}

graph::~graph()
{
    clear();
}

void graph::clear()
{
    m_nameToNode.clear();
    std::destroy(m_adjList.begin(), m_adjList.end());
    m_adjList.clear();
}

inline size_t graph::size() const noexcept
{
    return m_adjList.size();
}

inline bool graph::empty() const noexcept
{
    return 0 == size();
}

inline bool graph::contains(const std::string& name) const
{
    return (m_nameToNode.find(name) != m_nameToNode.end());
}

bool graph::add_node(const std::string& name)
{
    if (contains(name)) {
        return false;
    }
    const size_t id = m_adjList.size();
    node* n = new node(id, name);
    m_adjList.push_back(n);
    m_nameToNode.insert({name, n});
    return true;
}

bool graph::remove_node(const std::string& name)
{
    // Not implemented yet
    node* node = get_node(name);
    if (nullptr == node) {
        return false;
    }

    size_t id = node->get_id();

    auto iter = m_adjList.erase(m_adjList.begin() + id);
    for (; iter != m_adjList.end(); ++iter, ++id) {
        (*iter)->set_id(id);
        (void)(*iter)->remove_edge(node);
    }

    return true;
}

inline bool graph::has_edge(const std::string& from, const std::string& to)
{
    node* fromNode = get_node(from);
    node* toNode = get_node(to);

    if (nullptr == fromNode || nullptr == toNode) {
        return false;
    }

    return fromNode->has_edge(toNode);
}

bool graph::add_edge(const std::string& from, const std::string& to, edge::Cost_t cost)
{
    node* fromNode = get_or_create_node(from);
    node* toNode = get_or_create_node(to);

    return add_edge(fromNode, toNode, cost);
}

bool graph::remove_edge(const std::string& from, const std::string& to)
{
    node* fromNode = get_node(from);
    node* toNode = get_node(to);

    return fromNode->remove_edge(toNode);
}

bool graph::compare(const graph* g) const
{
    if (size() != g->size()) {
        return false;
    }
    if (num_of_edges() != g->num_of_edges()) {
        return false;
    }
    for (size_type i = 0; i < size(); ++i) {
        const node* lhs = get_node(i);
        const node* rhs = get_node(i);
        if (!lhs->compare(rhs)) {
            return false;
        }
    }
    return true;
}

void graph::dump(std::ostream& os) const
{
    for (const auto* node : m_adjList) {
        node->dump(os);
    }
}

}

namespace impl
{

const node* graph::mother_node() const
{
    const size_type numOfNodes = size();

    std::vector<bool> visited(numOfNodes, false);
    auto util = [&visited](auto& node) { visited[node.get_id()] = true; };

    size_t motherNode = 0;
    for (size_t i = 0; i < numOfNodes; ++i) {
        if (!visited[i]) {
            std::for_each(this->begin_DFS(i), this->end_DFS(), util);
            motherNode = i;
        }
    }

    std::fill(visited.begin(), visited.end(), false);
    std::for_each(this->begin_DFS(motherNode), this->end_DFS(), util);

    for (size_t i = 0; i < numOfNodes; ++i) {
        if (!visited[i]) {
            return nullptr;
        }
    }

    return get_node(motherNode);
}

}

namespace impl
{

graph::size_type graph::num_of_paths(const node* from, const node* to) const
{
    if (nullptr == from || nullptr == to) {
        return 0;
    }

    size_type numOfPaths = 0;

    std::queue<const node*> queue;
    queue.push(from);

    while (!queue.empty()) {
        const node* current = queue.front();
        queue.pop();

        if (current == to) {
            ++numOfPaths;
            continue;
        }

        for (auto nodeIter = current->cbegin_nodes(); nodeIter != current->cend_nodes(); ++nodeIter) {
            queue.push(*nodeIter);
        }
    }

    return numOfPaths;
}

}

namespace impl
{
bool graph::is_cyclic_util(size_type i, std::vector<bool>& visited, std::vector<bool>& stack) const
{
    if (!visited[i]) {
        visited[i] = true;
        stack[i] = true;
        for(auto it = m_adjList[i]->begin_nodes(); it !=  m_adjList[i]->end_nodes(); ++it) {
            const size_type id = (*it)->get_id();
            if ( !visited[id] && is_cyclic_util(id, visited, stack)) {
                return true;
            } else if (stack[id]) {
                return true;
            }
        }
    }
    stack[i] = false;
    return false;
}

bool graph::is_cyclic() const
{
    std::vector<bool> visited(size(), false);
    std::vector<bool> stack(size(), false);

    for (size_type i = 0; i < size(); ++i) {
        if (is_cyclic_util(i, visited, stack)) {
            return true;
        }
    }

    return false;
}

}

namespace impl
{

std::vector<edge::Cost_t> graph::dijkstra(size_type start) const
{
    std::vector<edge::Cost_t> dist(size(), edge::INF_COST);
    dist[start] = 0;

    std::priority_queue<std::pair<edge::Cost_t, size_type>> queue;
    queue.push({0, start});

    while (!queue.empty()) {
        const auto [cost, id] = queue.top();
        queue.pop();

        for (const edge* edge : m_adjList[id]->get_edges()) {
            const size_type toId = edge->get_to()->get_id();
            const edge::Cost_t toCost = edge->get_cost();
            const edge::Cost_t totalCost = cost + toCost;
            if (totalCost < dist[toId]) {
                dist[toId] = totalCost;
                queue.push({totalCost, toId});
            }
        }
    }
    return dist;
}

}

namespace impl
{

bool graph::has_negative_cycle() const
{
    assert(!empty());
    std::vector<edge::Cost_t> dist(size(), edge::INF_COST);
    dist[0] = 0;
    for (size_type i = 1; i < size(); ++i) {
        for (auto it = cbegin_edges(); it != cend_edges(); ++it) {
            size_type fromIdx = (*it)->get_from_idx();
            size_type toIdx = (*it)->get_to_idx();
            edge::Cost_t cost = (*it)->get_cost();
            if (dist[fromIdx] != edge::INF_COST && dist[fromIdx] + cost < dist[toIdx]) {
                dist[toIdx] = dist[fromIdx] + cost;
            }
        }
    }

    for (auto it = cbegin_edges(); it != cend_edges(); ++it) {
        size_type fromIdx = (*it)->get_from_idx();
        size_type toIdx = (*it)->get_to_idx();
        edge::Cost_t cost = (*it)->get_cost();
        if (dist[fromIdx] != edge::INF_COST && dist[fromIdx] + cost < dist[toIdx]) {
            return true;
        }
    }

    return false;
}

}

namespace impl
{

void graph::serialize(const std::string& fileName) const
{
    std::ofstream os{fileName};
    os << size() << '\n';
    for (const node* n : m_adjList) {
        os << n->get_name() << ' ' << n->get_num_of_edges() << ' ';
        for (const edge* e : n->get_edges()) {
            os << e->get_to()->get_id() << ' ' << e->get_cost() << ' ';
        }
        os << '\n';
    }
}

}

namespace impl
{

void graph::deserialize(const std::string& fileName)
{
    clear();
    std::ifstream is{fileName};

    size_type size = 0;
    is >> size;

    m_adjList.resize(size);
    for (size_t i = 0; i < m_adjList.size(); ++i) {
        m_adjList[i] = new node(i);
    }

    for (size_t i = 0; i < m_adjList.size(); ++i) {
        std::string name;
        is >> name >> size;
        m_adjList[i]->set_name(std::move(name));
        for (size_t j = 0; j < size; ++j) {
            size_type to;
            edge::Cost_t cost;
            is >> to >> cost;
            assert(to >= 0 && to < m_adjList.size());
            (void)add_edge(m_adjList[i], m_adjList[to], cost);
        }
    }
    m_adjList.shrink_to_fit();
}

}
