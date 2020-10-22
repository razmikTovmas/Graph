#pragma once

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
