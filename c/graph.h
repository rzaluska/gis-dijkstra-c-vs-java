#pragma once

struct Neighbor {
    int vertex_index;
    int weight;
    struct Neighbor * next;
};

struct Vertex {
    struct Neighbor* neighbors;
};

struct Graph {
    struct Vertex * vertex_array;
    int num_verticles;
};

struct Graph * new_graph(int num_verticles);
void graph_add_edge(struct Graph * g, int from, int to, int weight);
struct Neighbor * graph_get_neighbor(struct Graph * g, int from);
void graph_free(struct Graph * g);
