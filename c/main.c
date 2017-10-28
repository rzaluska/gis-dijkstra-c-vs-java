#include <stdio.h>
#include "graph.h"

int main() {
    // Read graph data from stdin
    // Write result to stdout
    int num_test_cases = 0;
    scanf("%d\n", &num_test_cases);
    printf("%d\n", num_test_cases);
    for (int i = 0; i < num_test_cases; i++) {
        int num_verticles = 0;
        int num_edges = 0;
        scanf("%d %d\n", &num_verticles, &num_edges);
        struct Graph * g = new_graph(num_verticles);
        for (int j = 0; j < num_edges; j++) {
            int edge1 = 0;
            int edge2 = 0;
            int weight = 0;
            scanf("%d %d %d\n", &edge1, &edge2, &weight);
            graph_add_edge(g, edge1, edge2, weight);
        }
        int starting_verticle = 0;
        scanf("%d\n", &starting_verticle);
        printf("%d\n", starting_verticle);
        graph_free(g);
    }
}
