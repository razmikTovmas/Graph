#pragma once

namespace impl
{
/**
 * @brief What is a Mother Vertex?
 * @details A mother vertex in a graph G = (V,E) is a vertex v such that all
 *          other vertices in G can be reached by a path from v.
 * 
 * @return const pointer to mother node if found, otherwise nullptr.
 */
const node* graph::mother_node()
{
    const graph::size_type numOfNodes = size();

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
