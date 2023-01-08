#include <cstdio>
#include "tsort.hpp"

int main()
{
        printf("This is a Topological Sort, aka. tsort\n");

        std::vector<tsort::edge> edges = {
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

        std::vector<size_t> nodes = {2, 3, 5, 7, 8, 9, 10, 11};
        std::vector<size_t> sorted;
        sorted.reserve(16);

        tsort::tsort(edges, nodes, sorted);

        for (int s : sorted) {
                printf("%i ", s);
        }

        return 0;
}
