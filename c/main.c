#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "graph.h"
#include "dijkstra.h"
#include "timer.h"

int main() {
    // Read graph data from stdin
    // Write result to stdout
    struct Timer all;
    timer_start(&all);
    int num_test_cases = 0;
    scanf("%d\n", &num_test_cases);
    for (int i = 0; i < num_test_cases; i++) {
        struct Timer timer;
        int num_verticles = 0;
        int num_edges = 0;
        scanf("%d %d\n", &num_verticles, &num_edges);
        printf("### graph with: %d vertices and %d edges\n", num_verticles, num_edges);
        timer_start(&timer);
        struct Graph * g = new_graph(num_verticles);
        for (int j = 0; j < num_edges; j++) {
            int edge1 = 0;
            int edge2 = 0;
            int weight = 0;
            scanf("%d %d %d\n", &edge1, &edge2, &weight);
            graph_add_edge(g, edge1, edge2, weight);
        }
        timer_stop(&timer);
        timer_print(&timer, "# graph build took");
        int starting_verticle = 0;
        scanf("%d\n", &starting_verticle);
        timer_start(&timer);
        struct DijkstraResult result = dijkstra(g, starting_verticle - 1);
        timer_stop(&timer);
        timer_print(&timer, "# dijkstra took");
        timer_start(&timer);
        for (int j = 0; j < g->num_verticles; j++) {
            if (j != starting_verticle - 1) {
                if (j != g->num_verticles - 1) {
                    printf("%u ", result.distance_table[j]);
                } else {
                    printf("%u", result.distance_table[j]);
                }
            }
        }
        printf("\n");
        for (int j = 0; j < g->num_verticles; j++) {
            if (j != starting_verticle - 1) {
                if (j != g->num_verticles - 1) {
                    printf("%u ", result.prev_table[j]);
                } else {
                    printf("%u", result.prev_table[j]);
                }
            }
        }
        timer_stop(&timer);
        timer_print(&timer, "\n# print result took");
        free(result.distance_table);
        free(result.prev_table);
        graph_free(g);
    }
    timer_stop(&all);
    timer_print(&all, "# execution took");
}
