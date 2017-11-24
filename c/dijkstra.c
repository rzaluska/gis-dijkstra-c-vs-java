#include "dijkstra.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

unsigned int * dijkstra(struct Graph *g, int start) {
    unsigned int * distance_table = (unsigned int*)calloc(g->num_verticles, sizeof(unsigned int));
    struct PriorityQueue *q = new_priority_queue(g->num_verticles);

    distance_table[start] = 0;
    for (int i = 0; i < g->num_verticles; i++) {
        if (i != start) {
            distance_table[i] = UINT_MAX;
        }
        priority_queue_add_with_priority(q, i, distance_table[i]);
    }

    while (!priority_queue_is_empty(q)) {
        int min_verticle = priority_queue_extract_min(q);
        struct Neighbor * neighbors = graph_get_neighbor(g, min_verticle);
        while (neighbors != NULL) {
            unsigned int alternative = distance_table[min_verticle] + neighbors->weight;
            if (alternative < distance_table[neighbors->vertex_index]) {
                distance_table[neighbors->vertex_index] = alternative;
                priority_queue_decrease_priority(q, neighbors->vertex_index, alternative);
            }
            neighbors = neighbors->next;
        }
    }

    priority_queue_free(q);
    return distance_table;
}
