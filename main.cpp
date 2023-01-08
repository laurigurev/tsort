#include <cstdio>
#include <vector>
// #include <functional>
#include <algorithm>

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

        std::sort(edges.begin(), edges.end(), [](const edge e0, const edge e1) { return e0.dst < e1.dst; });

        printf("Sorted edges\n");
        for (edge e : edges) {
                printf("{%i, %i}\n", e.src, e.dst);
        }

        std::vector<int> empty = {3, 5, 7};
        std::vector<int> sorted;
        sorted.reserve(9);

        for (int i = 0; i < empty.size();) {
                int tmp = empty[i];
                empty.erase(empty.begin());
                sorted.push_back(tmp);

                for (int j = 0; j < edges.size();) {
                        if (edges[j].src == tmp) {
                                int m = edges[j].dst;
                                edges.erase(edges.begin() + j);
                                for (edge e : edges) {
                                        if (e.dst == m) {
                                                m = -1;
                                                break;
                                        }
                                }
                                if (m != -1) empty.push_back(m);
                        }
                        else j++;
                }
        }

        printf("\nSorted nodes\n");
        for (int s : sorted) {
                printf("%i ", s);
        }

        if (edges.size()) {
                printf("Some edges left!\n");
                return 1;
        }

        return 0;
}
