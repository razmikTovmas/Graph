#pragma once

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
