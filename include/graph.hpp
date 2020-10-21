#pragma once

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <stack>

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
private:
    constexpr static size_t INVALID_ID = std::numeric_limits<size_t>::max();

public:
    using NodeIter = std::vector<std::string>;
    using EdgeIter = std::vector<std::tuple<std::string, std::string, int>>;

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
    [[nodiscard]] inline size_t size() const noexcept;

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

    /**
     * @brief Return an iterator that yields (name, weight) of all the neighboring nodes.
     */
    NodeIter neighbors(const std::string& from_name);

    /**
     * @brief Return an iterator that yields the node names (in no particular order).
     */
    NodeIter nodes();

    /**
     * @brief Return all the edges as an iterator of Edges (named tuples) with values
     *        (from, to, weight). Edges are yielded in no particular order.
     */
    EdgeIter edges();

    /**
     * @brief Dumps the graph object to ostream.
     */
    void dump(std::ostream& os = std::cout) const;

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
        using reference = node&;
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

        [[nodiscard]] inline bool is_BFS() noexcept { return iter_type::BFS == m_type; }
        [[nodiscard]] inline bool is_DFS() noexcept { return iter_type::DFS == m_type; }

    private:
        void collect_nodes();

    private:
        iter_type m_type;
        node* m_node; // nullptr means the end of the graph
        std::vector<bool> m_visited;
        std::deque<node*> m_deque;
    };

    [[nodiscard]] iterator begin_BFS(size_t start) { return iterator(*this, get_node(start), iterator::iter_type::BFS); }
    [[nodiscard]] iterator begin_BFS(const std::string& name) { return iterator(*this, get_node(name), iterator::iter_type::BFS); }
    [[nodiscard]] iterator end_BFS() { return iterator(*this, nullptr, iterator::iter_type::BFS); }
    [[nodiscard]] iterator begin_DFS(size_t start) { return iterator(*this, get_node(start), iterator::iter_type::DFS); }
    [[nodiscard]] iterator begin_DFS(const std::string& name) { return iterator(*this, get_node(name), iterator::iter_type::DFS); }
    [[nodiscard]] iterator end_DFS() { return iterator(*this, nullptr, iterator::iter_type::DFS); }

private:
    [[nodiscard]] inline size_t get_node_id(const std::string& name) const;
    [[nodiscard]] inline node* get_node(const std::string& name);
    [[nodiscard]] inline node* get_node(size_t start);
    [[nodiscard]] inline node* get_or_create_node(const std::string& name);

private:
    std::vector<node*> m_adjList;
    std::map<std::string, node*> m_nameToId;

};

////////////////////////////////////////////////////////////////////////////////
///// graph
////////////////////////////////////////////////////////////////////////////////
inline size_t graph::get_node_id(const std::string& name) const
{
    auto it = m_nameToId.find(name);
    if (it != m_nameToId.end()) {
        return it->second->get_id();
    }
    return INVALID_ID;
}

inline node* graph::get_node(const std::string& name)
{
    auto it = m_nameToId.find(name);
    if (it != m_nameToId.end()) {
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

inline node* graph::get_or_create_node(const std::string& name)
{
    node* n = get_node(name);
    if (nullptr != n) {
        return n;
    }
    const size_t id = m_adjList.size();
    n = new node(id, name);
    m_adjList.push_back(n);
    m_nameToId.insert({name, n});
    return n;
}

graph::graph()
    : m_adjList{}
    , m_nameToId{}
{ }

graph::~graph()
{
    std::destroy(m_adjList.begin(), m_adjList.end());
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
    return (m_nameToId.find(name) != m_nameToId.end());
}

bool graph::add_node(const std::string& name)
{
    if (contains(name)) {
        return false;
    }
    const size_t id = m_adjList.size();
    node* n = new node(id, name);
    m_adjList.push_back(n);
    m_nameToId.insert({name, n});
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
    std::cout << "New idx: " << std::distance(m_adjList.begin(), iter) << std::endl;
    std::cout << "Old idx: " << (*iter)->get_id() << std::endl;

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

    return fromNode->add_edge(toNode, cost);
}

bool graph::remove_edge(const std::string& from, const std::string& to)
{
    node* fromNode = get_node(from);
    node* toNode = get_node(to);

    return fromNode->remove_edge(toNode);
}

void graph::dump(std::ostream& os) const
{
    for (const auto* node : m_adjList) {
        node->dump(os);
    }
}

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
    for (auto it = m_node->begin_nods(); it != m_node->end_nods(); ++it) {
        node* to = *it;
        const size_t id = to->get_id();
        if (!m_visited[id]) {
            m_visited[id] = true;
            m_deque.push_back(to);
        }
    }
}

}
