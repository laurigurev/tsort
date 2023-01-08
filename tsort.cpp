#include "tsort.hpp"
#include "bitset2.hpp"
#include <array>

namespace tsort {

void tsort(const std::vector<edge>& edges, std::vector<size_t>& nodes, std::vector<size_t>& sorted)
{
        std::array<bitset2<16>, 16> input;
        std::array<bitset2<16>, 16> output;
        for (edge e : edges) {
                // for destination node set into map all the nodes
                // that input into it
                input[e.dst].set(e.src);
                // for source node set into map all the nodes that
                // source ouputs to
                output[e.src].set(e.dst);
        }

        for (auto n = nodes.begin(); n != nodes.end();) {
                if (input[*n].any()) {
                        nodes.erase(n);
                        continue;
                }
                n++;
        }

        sorted.reserve(16);
        // container that saves all the nodes on the same level;
        // bitset2<16> level;
        for (int i = 0; i < nodes.size();) {
                int n = nodes[i];

                /* if (level.test(n)) {
                        level ^= level;
                        sorted.push_back(-1);
                } */

                sorted.push_back(n);
                nodes.erase(nodes.begin());

                if (!output[n].any()) continue;

                int len = output[n].count();
                while (len--) {
                        int m = static_cast<int>(output[n].find_first());

                        input[m].reset(n);
                        output[n].reset(m);
                        if (input[m].none()) {
                                nodes.push_back(m);
                                // level.set(m);
                        }
                }
        }
}

} // namespace tsort
