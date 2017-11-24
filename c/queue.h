#pragma once

// Priority queue implementation

struct PQElem {
    unsigned int val;
    unsigned int priority;
    int next;
    int index;
};

struct PriorityQueue {
    struct PQElem *elements;
    int first;
    int next_free;
    int size;
};

struct PriorityQueue * new_priority_queue(int max_elements);
void priority_queue_add_with_priority(struct PriorityQueue * q, unsigned int elem, unsigned int priority);
int priority_queue_is_empty(struct PriorityQueue * q);
unsigned int priority_queue_extract_min(struct PriorityQueue * q);
void priority_queue_decrease_priority(struct PriorityQueue * q, unsigned int val, unsigned int new_priority);
void priority_queue_free(struct PriorityQueue * q);
