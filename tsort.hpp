#pragma once

#include <vector>

namespace tsort {

struct edge {
        size_t src;
        size_t dst;
};

void tsort(const std::vector<edge>& edges, std::vector<size_t>& nodes, std::vector<size_t>& sorted);

} // namespace tsort
