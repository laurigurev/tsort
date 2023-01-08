#include <array>
// #include <bitset>
#include <cstdio>
#include <vector>
#include "bitset2.hpp"

struct edge {
        int src;
        int dst;
};

int main()
{
        printf("Hello, world! This is a Topological Sort, aka. tsort\n");

        std::vector<edge> edges = {
            {8,  9 },
            {3,  8 },
            {11, 10},
            {3,  10},
            {7,  11},
            {11, 2 },
            {7,  8 },
            {11, 9 },
            {5,  11}
        };

        std::vector<int> nodes = {2, 3, 5, 7, 8, 9, 10, 11};

        // construct bitmaps that signifies relationship inside a graph
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

        // for (auto a : output) printf("%llu\n", a.data[0]);

        for (auto n = nodes.begin(); n != nodes.end();) {
                if (input[*n].any()) {
                        nodes.erase(n);
                        continue;
                }
                n++;
        }

        std::vector<int> sorted;
        sorted.reserve(16);
        // container that saves all the nodes on the same level;
        bitset2<16> level;
        for (int i = 0; i < nodes.size();) {
                int n = nodes[i];
                
                if (level.test(n)) {
                        level ^= level;
                        sorted.push_back(-1);
                }
                
                sorted.push_back(n);
                nodes.erase(nodes.begin());
                
                if (!output[n].any()) continue;

                int len = output[n].count();
                while (len--) {
                        int m = static_cast<int>(output[n].find_first());

                        // printf("n %i, m %i, input %llu\n", n, m, input[m].data[0]);
                        // printf("input[%i]  ", m); input[m].reset(n);
                        // printf("output[%i] ", n); output[n].reset(m);
                        // printf("n %i, m %i, output %llu\n", n, m, output[n].data[0]);
                        // printf("n %i, m %i, input.none() %i\n", n, m, input[m].none());
                        input[m].reset(n);
                        output[n].reset(m);
                        if (input[m].none()) {
                                nodes.push_back(m);
                                level.set(m);
                                // printf("nodes.push_back(%i)\n", m);
                        }
                }
        }

        for (int s : sorted) {
                if (s == -1) printf("\n");
                else printf("%i ", s);
        }

        return 0;
}
