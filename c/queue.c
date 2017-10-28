#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "queue.h"

struct PriorityQueue * new_priority_queue() {
    struct PriorityQueue * pq = (struct PriorityQueue*)malloc(sizeof (struct PriorityQueue));
    pq->first = NULL;
    return pq;
}

int priority_queue_is_empty(struct PriorityQueue * q) {
    return q->first == NULL;
}

void priority_queue_add_with_priority(struct PriorityQueue * q, unsigned int elem, unsigned int priority) {
    struct PQElem * new_elem = (struct PQElem*)malloc(sizeof (struct PQElem));
    new_elem->val = elem;
    new_elem->priority = priority;
    new_elem->next = NULL;

    if (q->first == NULL) {
        q->first = new_elem;
        return;
    }

    struct PQElem * curr = q->first;
    struct PQElem * prev = NULL;

    while (curr != NULL) {
        if (curr->priority > new_elem->priority) {
            if (curr == q->first) {
                q->first = new_elem;
                new_elem->next = curr;
                return;
            } else {
                prev->next = new_elem;
                new_elem->next = curr;
                return;
            }
        }
        prev = curr;
        curr = curr->next;
    }
    //Add to end
    prev->next = new_elem;
}

void priority_queue_decrease_priority(struct PriorityQueue * q, unsigned int val, unsigned int new_priority) {
    struct PQElem * curr = q->first;
    struct PQElem * prev = NULL;
    while (curr != NULL) {
        if (curr->val == val) {
            if (curr == q->first) {
                q->first = curr->next;
                free(curr);
            } else {
                prev->next = curr->next;
                free(curr);
            }
            priority_queue_add_with_priority(q, val, new_priority);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void priority_queue_print(struct PriorityQueue * q) {
    struct PQElem * curr = q->first;

    puts("Dumping queue...");
    while (curr != NULL) {
        printf("p: %u v: %u\n", curr->priority, curr->val);
        curr = curr->next;
    }
}

unsigned int priority_queue_extract_min(struct PriorityQueue * q) {
    struct PQElem * min_elem = q->first;
    assert(min_elem != NULL);
    int to_return = min_elem->val;
    q->first = min_elem->next;
    free(min_elem);
    return to_return;
}

void priority_queue_free(struct PriorityQueue * q) {
    struct PQElem * curr = q->first;

    while (curr != NULL) {
        struct PQElem * to_free = curr;
        curr = curr->next;
        free(to_free);
    }
    free(q);
}
