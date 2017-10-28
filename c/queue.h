#pragma once

// Priority queue implementation

struct PQElem {
    int val;
    int priority;
    struct PQElem *next;
};

struct PriorityQueue {
    struct PQElem *first;
};

struct PriorityQueue * new_priority_queue();
void priority_queue_add_with_priority(struct PriorityQueue * q, int elem, int priority);
int priority_queue_is_empty(struct PriorityQueue * q);
int priority_queue_extract_min(struct PriorityQueue * q);
void priority_queue_print(struct PriorityQueue * q);
void priority_queue_free(struct PriorityQueue * q);
