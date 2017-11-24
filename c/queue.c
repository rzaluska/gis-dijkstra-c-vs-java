#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "queue.h"

struct PriorityQueue * new_priority_queue(int max_elements) {
    struct PriorityQueue * pq = (struct PriorityQueue *)malloc(sizeof(struct PriorityQueue));
    pq->elements = (struct PQElem*)calloc(max_elements, sizeof (struct PQElem));
    pq->first = -1;
    pq->next_free = 0;
    pq->size = 0;
    return pq;
}

int priority_queue_is_empty(struct PriorityQueue * q) {
    return q->size == 0;
}

void find_place_for_element(struct PriorityQueue * q, int new_index) {
    if (q->size == 1) {
        q->first = 0;
        return;
    }

    struct PQElem * new_elem = &(q->elements[new_index]);
    struct PQElem * curr = &(q->elements[q->first]);
    struct PQElem * prev = NULL;

    while (1) {
        if (curr->priority > new_elem->priority) {
            if (curr->index == q->first) {
                q->first = new_elem->index;
            } else {
                prev->next = new_elem->index;
            }
            new_elem->next = curr->index;
            return;
        }
        prev = curr;
        if (curr->next == -1) {
            break;
        }
        curr = &(q->elements[curr->next]);
    }
    //Add to end
    prev->next = new_elem->index;
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
    find_place_for_element(q, new_elem->index);
}

void priority_queue_decrease_priority(struct PriorityQueue * q, unsigned int val, unsigned int new_priority) {
    struct PQElem * curr = &(q->elements[q->first]);
    struct PQElem * prev = NULL;
    while (1) {
        if (curr->val == val) {
            curr->priority = new_priority;
            if (curr->index != q->first) {
                prev->next = curr->next;
                find_place_for_element(q, curr->index);
            }
            return;
        }
        if (curr->next == -1) {
            break;
        }
        prev = curr;
        curr = &(q->elements[curr->next]);
    }
}

unsigned int priority_queue_extract_min(struct PriorityQueue * q) {
    struct PQElem * min_elem = &(q->elements[q->first]);
    int to_return = min_elem->val;
    q->size--;
    if (q->size > 0) {
        q->first = q->elements[min_elem->next].index;
    }
    else if (q->size == 0) {
        q->first = -1;
    }
    return to_return;
}

void priority_queue_free(struct PriorityQueue * q) {
    struct PQElem * elements = q->elements;
    free(elements);
    free(q);
}
