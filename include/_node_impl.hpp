#pragma once


namespace impl
{

node::node(size_t id, std::string name)
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
