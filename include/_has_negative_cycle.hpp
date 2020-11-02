#pragma once

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
