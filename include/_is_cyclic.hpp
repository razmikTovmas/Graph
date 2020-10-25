#pragma once

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
