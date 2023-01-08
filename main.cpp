#include <cstdio>
#include <vector>

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
        std::vector<int> sorted;
        sorted.reserve(9);
        std::vector<int> levels;
        levels.reserve(9);
        std::vector<int> history;
        history.reserve(9);
        std::vector<int> marked;
        marked.reserve(9);

        while (!nodes.empty()) {
                for (int i = 0; i < nodes.size(); i++) {
                        marked.clear();
                        int tmp = nodes[i];
                        int counter = 0;
                        
                        printf("node %i, nodes.size() %llu, edges.size() %llu\n", tmp, nodes.size(), edges.size());
                        for (int k = 0; k < edges.size(); k++) {
                                printf("{%i, %i}, ", edges[k].src, edges[k].dst);
                        }
                        if (edges.size()) printf("\n");
                        
                        for (int ii = 0; ii < edges.size(); ii++) {
                                if (edges[ii].dst == tmp) counter++;
                                if (edges[ii].src == tmp) { 
                                        marked.push_back(ii);
                                        history.push_back(edges[ii].dst);
                                }
                        }
                        
                        if (counter) continue;
                        sorted.push_back(tmp);
                        nodes.erase(nodes.begin() + i);

                        for (int j = 0; j < history.size(); j++) {
                                if (tmp == history[j]) {
                                        levels.push_back(sorted.size() - 2);
                                        history.clear();
                                        break;
                                }
                        }
                        
                        if (marked.size() == 0) break;
                        for (int j = marked.size() - 1; j >= 0; j--) {
                                edges.erase(edges.begin() + marked[j]);
                        }
                        
                        break; // let's start at the beginning because vector dimensions have changed
                }
        }

        int li = 0;
        for (int i = 0; i < sorted.size(); i++) {
                printf("%i ", sorted[i]);
                // printf("(li %i, i %i) ", levels[li], i);
                if (levels[li] == i && levels.size()) {
                        printf("\n");
                        li++;
                }
        }

        return 0;
}
