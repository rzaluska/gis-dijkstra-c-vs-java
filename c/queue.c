#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include "queue.h"

struct PriorityQueue * new_priority_queue(int max_elements) {
    struct PriorityQueue * pq = (struct PriorityQueue *)malloc(sizeof(struct PriorityQueue));
    pq->elements = (struct PQElem*)calloc(max_elements, sizeof (struct PQElem));
    pq->lookup_index = (int*)calloc(max_elements, sizeof (int));
    pq->present = (int*)calloc(max_elements, sizeof (int));
    pq->first = -1;
    pq->next_free = 0;
    pq->size = 0;
    return pq;
}

int priority_queue_is_empty(struct PriorityQueue * q) {
    return q->size == 0;
}

void priority_queue_add_with_priority(struct PriorityQueue * q, unsigned int elem, unsigned int priority) {
    int element_index = q->next_free;
    struct PQElem * new_elem = &(q->elements[element_index]);
    (q->next_free)++;
    (q->size)++;
    new_elem->val = elem;
    new_elem->index = element_index;
    new_elem->priority = priority;
    new_elem->next = -1;
    q->lookup_index[elem] = element_index;
    q->present[element_index] = 1;
}

void priority_queue_decrease_priority(struct PriorityQueue * q, unsigned int val, unsigned int new_priority) {
    int element_index = q->lookup_index[val];
    struct PQElem * curr = &(q->elements[element_index]);
    curr->priority = new_priority;
}

unsigned int priority_queue_extract_min(struct PriorityQueue * q) {
    unsigned int min = UINT_MAX;
    int val;
    int index;

    for (int i = 0; i < q->next_free; i++) {
        if (!q->present[i]) {
            continue;
        }
        if (q->elements[i].priority <= min) {
            min = q->elements[i].priority;
            val = q->elements[i].val;
            index = i;
        }
    }
    q->present[index] = 0;
    q->size--;
    return val;
}

void priority_queue_free(struct PriorityQueue * q) {
    struct PQElem * elements = q->elements;
    free(elements);
    free(q->lookup_index);
    free(q);
}
