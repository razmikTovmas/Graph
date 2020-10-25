#pragma once

namespace impl
{

void graph::serialize(const std::string& fileName) const
{
    std::ofstream os{fileName};
    os << size() << " \n";
    for (const node* n : m_adjList) {
        os << n->get_name() << ' ' << n->get_num_of_edges() << '\n';
        for (const edge* e : n->get_edges()) {
            os << e->get_to()->get_id() << ' ' << e->get_cost() << ' ';
        }
        os << '\n';
    }
}

}
