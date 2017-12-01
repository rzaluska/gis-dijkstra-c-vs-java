#pragma once

#include "graph.h"

struct DijkstraResult {
    unsigned int * distance_table;
    unsigned int * prev_table;
};

struct DijkstraResult dijkstra(struct Graph *g, int start);
