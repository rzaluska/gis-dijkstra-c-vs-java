#include "queue.h"
#include <assert.h>
#include <stdlib.h>

int main() {
    struct PriorityQueue *q = new_priority_queue();
    priority_queue_add_with_priority(q, 1, 10);
    priority_queue_add_with_priority(q, 2, 100);
    priority_queue_add_with_priority(q, 3, 1000);
    assert(priority_queue_is_empty(q) == 0);
    priority_queue_print(q);
    assert(priority_queue_extract_min(q) == 1);
    assert(priority_queue_extract_min(q) == 2);
    assert(priority_queue_extract_min(q) == 3);
    assert(priority_queue_is_empty(q) == 1);

    priority_queue_add_with_priority(q, 2, 100);
    assert(priority_queue_is_empty(q) == 0);
    priority_queue_add_with_priority(q, 1, 10);
    assert(priority_queue_is_empty(q) == 0);
    priority_queue_add_with_priority(q, 3, 1000);
    assert(priority_queue_is_empty(q) == 0);
    priority_queue_add_with_priority(q, 4, 1);
    assert(priority_queue_is_empty(q) == 0);
    priority_queue_add_with_priority(q, 5, 10000);
    assert(priority_queue_is_empty(q) == 0);
    assert(priority_queue_is_empty(q) == 0);
    priority_queue_print(q);

    assert(priority_queue_extract_min(q) == 4);
    assert(priority_queue_is_empty(q) == 0);
    assert(priority_queue_extract_min(q) == 1);
    assert(priority_queue_is_empty(q) == 0);
    assert(priority_queue_extract_min(q) == 2);
    assert(priority_queue_is_empty(q) == 0);
    assert(priority_queue_extract_min(q) == 3);
    assert(priority_queue_is_empty(q) == 0);
    assert(priority_queue_extract_min(q) == 5);

    assert(priority_queue_is_empty(q) == 1);

    priority_queue_free(q);
    free(q);
}
