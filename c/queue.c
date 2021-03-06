#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include "queue.h"

struct PriorityQueue * new_priority_queue(int max_elements) {
    struct PriorityQueue * pq = (struct PriorityQueue *)malloc(sizeof(struct PriorityQueue));
    pq->elements = (struct PQElem*)calloc(max_elements, sizeof (struct PQElem));
    pq->lookup_index = (int*)calloc(max_elements, sizeof (int));
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
    new_elem->prev = -1;
    q->lookup_index[elem] = element_index;
    if (q->size == 1) {
        q->first = 0;
        return;
    }
    struct PQElem * prev_element = &(q->elements[element_index-1]);
    prev_element->next = element_index;
    new_elem->prev = prev_element->index;
}

void priority_queue_decrease_priority(struct PriorityQueue * q, unsigned int val, unsigned int new_priority) {
    int element_index = q->lookup_index[val];
    struct PQElem * curr = &(q->elements[element_index]);
    curr->priority = new_priority;
}

unsigned int priority_queue_extract_min(struct PriorityQueue * q) {
#ifdef DEBUG
    printf("START_EXTRACT_MIN\n");
#endif
    unsigned int min = UINT_MAX;
    int val = 0;
    int index = 0;

    for (int i = q->first; i != -1;) {
#ifdef DEBUG
        printf("q->elements[%d].priority = %u\n", i, q->elements[i].priority);
        printf("q->elements[%d].val = %d\n", i, q->elements[i].val);
#endif
        if (q->elements[i].priority <= min) {
            min = q->elements[i].priority;
            val = q->elements[i].val;
            index = i;
        }
        i = q->elements[i].next;
    }
    if (index == q->first) {
        q->first = q->elements[index].next;
    }
    if (q->elements[index].next != -1) {
        q->elements[q->elements[index].next].prev = q->elements[index].prev;
    }

    if (q->elements[index].prev != -1) {
        q->elements[q->elements[index].prev].next = q->elements[index].next;
    }
    q->size--;
#ifdef DEBUG
    printf("END_EXTRACT_MIN returning %d\n", val);
#endif
    return val;
}

void priority_queue_free(struct PriorityQueue * q) {
    struct PQElem * elements = q->elements;
    free(elements);
    free(q->lookup_index);
    free(q);
}
