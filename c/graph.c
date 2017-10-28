#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

struct Graph * new_graph(int num_verticles) {
    struct Graph * graph = (struct Graph*)malloc(sizeof (struct Graph));
    graph->vertex_array = (struct Vertex*)calloc(num_verticles, sizeof (struct Vertex));
    graph->num_verticles = num_verticles;
    return graph;
}

void graph_free(struct Graph * g) {
    for (int i =0; i < g->num_verticles; i++) {
#ifdef DEBUG
        printf("V[%d]:\n", i);
#endif
        struct Vertex curr = g->vertex_array[i];
        struct Neighbor * neighbor = curr.neighbors;
        while (neighbor != NULL) {
#ifdef DEBUG
            printf("\t[E] %d --%d--> %d\n", i, neighbor->weight, neighbor->vertex_index);
#endif
            struct Neighbor * to_free = neighbor;
            neighbor = neighbor->next;
            free(to_free);
        }
    }
    free(g->vertex_array);
    free(g);
}

void graph_add_single_edge(struct Graph * g, int from, int to, int weight) {
    struct Vertex *f = &(g->vertex_array[from-1]);
    struct Neighbor *nforward = (struct Neighbor *)malloc(sizeof(struct Neighbor));
    nforward->vertex_index = to-1;
    nforward->weight = weight;
    nforward->next = NULL;
    if (f->neighbors == NULL) {
        f->neighbors = nforward;
    } else {
        nforward->next = f->neighbors;
        f->neighbors = nforward;
    }
}

void graph_add_edge(struct Graph * g, int from, int to, int weight) {
#ifdef DEBUG
    printf("graph_add_edge(%d, %d, %d)\n", from, to, weight);
#endif
    graph_add_single_edge(g, from, to, weight);
    graph_add_single_edge(g, to, from, weight);

}


struct Neighbor * graph_get_neighbor(struct Graph * g, unsigned int from) {
    struct Vertex f = g->vertex_array[from];
    return f.neighbors;
}
