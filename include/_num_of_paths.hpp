#pragma once

namespace impl
{

graph::size_type graph::num_of_paths(const node* from, const node* to) const
{
    if (nullptr == from || nullptr == to) {
        return 0;
    }

    size_type numOfPaths = 0;

    std::queue<const node*> queue;
    queue.push(from);

    while (!queue.empty()) {
        const node* current = queue.front();
        queue.pop();

        if (current == to) {
            ++numOfPaths;
            continue;
        }

        for (auto nodeIter = current->cbegin_nodes(); nodeIter != current->cend_nodes(); ++nodeIter) {
            queue.push(*nodeIter);
        }
    }

    return numOfPaths;
}

}
