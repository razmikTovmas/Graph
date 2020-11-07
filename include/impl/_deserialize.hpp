#pragma once

namespace impl
{

void graph::deserialize(const std::string& fileName)
{
    clear();
    std::ifstream is{fileName};

    size_type size = 0;
    is >> size;

    m_adjList.resize(size);
    for (size_t i = 0; i < m_adjList.size(); ++i) {
        m_adjList[i] = new node(i);
    }

    for (size_t i = 0; i < m_adjList.size(); ++i) {
        std::string name;
        is >> name >> size;
        m_adjList[i]->set_name(std::move(name));
        for (size_t j = 0; j < size; ++j) {
            size_type to;
            edge::Cost_t cost;
            is >> to >> cost;
            assert(to >= 0 && to < m_adjList.size());
            (void)add_edge(m_adjList[i], m_adjList[to], cost);
        }
    }
    m_adjList.shrink_to_fit();
}

}
