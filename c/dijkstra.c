#include "dijkstra.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "timer.h"

struct  DijkstraResult dijkstra(struct Graph *g, int start) {
    struct Timer timer;
    timer_start(&timer);

    struct DijkstraResult result;
    result.distance_table = (unsigned int*)calloc(g->num_verticles, sizeof(unsigned int));
    result.prev_table = (unsigned int*)calloc(g->num_verticles, sizeof(unsigned int));
    struct PriorityQueue *q = new_priority_queue(g->num_verticles);

    struct Timer init;
    timer_start(&init);

    result.distance_table[start] = 0;
    for (int i = 0; i < g->num_verticles; i++) {
        if (i != start) {
            result.distance_table[i] = UINT_MAX;
            result.prev_table[i] = -1;
        }
        priority_queue_add_with_priority(q, i, result.distance_table[i]);
    }
    timer_stop(&init);
    timer_print(&init, "# dijkstra init");

    struct Timer loop;
    timer_start(&loop);
    while (!priority_queue_is_empty(q)) {
        int min_verticle = priority_queue_extract_min(q);
        struct Neighbor * neighbor = graph_get_neighbor(g, min_verticle);
        while (neighbor != NULL) {
            unsigned int alternative = result.distance_table[min_verticle] + neighbor->weight;
            if (alternative < result.distance_table[neighbor->vertex_index]) {
                result.distance_table[neighbor->vertex_index] = alternative;
                result.prev_table[neighbor->vertex_index] = min_verticle;
                priority_queue_decrease_priority(q, neighbor->vertex_index, alternative);
            }
            neighbor = neighbor->next;
        }
    }
    timer_stop(&loop);
    timer_print(&loop, "# dijkstra loop");

    priority_queue_free(q);
    timer_stop(&timer);
    timer_print(&timer, "# dijkstra took");
    return result;
}
