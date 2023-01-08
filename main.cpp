#include <array>
#include <bitset>
#include <cstdio>
#include <vector>
// #include <functional>
// #include <algorithm>

struct edge {
        int src;
        int dst;
};

// int tsort();

int main()
{
        printf("Hello, world! This is a Topological Sort, aka. tsort\n\n");

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
        std::array<std::bitset<16>, 16> input;
        std::array<std::bitset<16>, 16> output;
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

        std::vector<int> sorted;
        sorted.reserve(16);
        // constainer that saves all the nodes on the same level;
        std::bitset<16> level;
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
                        int m = 0;
                        while (m < output[n].size() && !output[n].test(m)) ++m;

                        input[m].reset(n);
                        output[n].reset(m);
                        
                        if (input[m].none()) {
                                nodes.push_back(m);
                                level.set(m);
                        }
                }
        }

        for (int s : sorted) {
                if (s == -1) printf("\n");
                else printf("%i ", s);
        }

        return 0;
}
