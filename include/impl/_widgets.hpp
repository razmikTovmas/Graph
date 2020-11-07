#pragma once

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
