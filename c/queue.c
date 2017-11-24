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

void find_place_for_element(struct PriorityQueue * q, struct PQElem * new_elem) {
    if (q->size == 1) {
        q->first = 0;
        return;
    }

    struct PQElem * curr = &(q->elements[q->first]);
    struct PQElem * prev = NULL;

    while (curr != NULL) {
        if (curr->priority > new_elem->priority) {
            if (curr->index == q->first) {
                q->first = new_elem->index;
                new_elem->next = curr;
            } else {
                prev->next = new_elem;
                new_elem->next = curr;
            }
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    //Add to end
    prev->next = new_elem;
}

void priority_queue_add_with_priority(struct PriorityQueue * q, unsigned int elem, unsigned int priority) {
    int element_index = q->next_free;
    struct PQElem * new_elem = &(q->elements[element_index]);
    (q->next_free)++;
    (q->size)++;
    new_elem->val = elem;
    new_elem->index = element_index;
    new_elem->priority = priority;
    new_elem->next = NULL;
    find_place_for_element(q, new_elem);
}

void priority_queue_decrease_priority(struct PriorityQueue * q, unsigned int val, unsigned int new_priority) {
    struct PQElem * curr = &(q->elements[q->first]);
    struct PQElem * prev = NULL;
    while (curr != NULL) {
        if (curr->val == val) {
            curr->priority = new_priority;
            if (curr->index != q->first) {
                prev->next = curr->next;
                find_place_for_element(q, curr);
            }
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void priority_queue_print(struct PriorityQueue * q) {
    struct PQElem * curr = &(q->elements[q->first]);

    puts("Dumping queue...");
    while (curr != NULL) {
        printf("p: %u v: %u\n", curr->priority, curr->val);
        curr = curr->next;
    }
}

unsigned int priority_queue_extract_min(struct PriorityQueue * q) {
    struct PQElem * min_elem = &(q->elements[q->first]);
    int to_return = min_elem->val;
    q->size--;
    if (q->size > 0) {
        q->first = min_elem->next->index;
    }
    return to_return;
}

void priority_queue_free(struct PriorityQueue * q) {
    struct PQElem * elements = q->elements;
    free(elements);
    free(q);
}
