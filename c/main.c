#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "dijkstra.h"
#include "timer.h"

int main() {
    // Read graph data from stdin
    // Write result to stdout
    int num_test_cases = 0;
    struct Timer timer;
    scanf("%d\n", &num_test_cases);
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
        timer_start(&timer);
        unsigned int * distance_table = dijkstra(g, starting_verticle - 1);
        timer_stop(&timer);
        for (int j = 0; j < g->num_verticles; j++) {
            if (i != starting_verticle - 1) {
                if (i != g->num_verticles - 1) {
                    printf("%u ", distance_table[j]);
                } else {
                    printf("%u", distance_table[j]);
                }
            }
        }
        free(distance_table);
        graph_free(g);
        printf("dijkstra full took: %lu sec, %lu us\n", timer_get_sec_delta(&timer), timer_get_usec_delta(&timer));
    }
}
