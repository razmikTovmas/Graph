#pragma once

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
