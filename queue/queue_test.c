//
// Created by simon on 17-9-9.
//

#include "queue.h"

void queue_test() {
    int i;
    queue_t *queue = queue_init();
    enqueue(queue, 1);
    enqueue(queue, 2);
    assert(queue->head->data == 1);
    assert(queue->tail->data == 2);
    dequeue(queue);
    dequeue(queue);
    i = is_empty(queue);
    assert(i == 1);
    enqueue(queue, 3);
    enqueue(queue, 4);
    enqueue(queue, 5);
    assert(queue->head->data == 3);
    assert(queue->tail->data == 5);
    dequeue(queue);
    dequeue(queue);
    i = is_empty(queue);
    assert(i == 0);
    enqueue(queue, 1);
    enqueue(queue, 2);
    assert(queue->head->data == 5);
    assert(queue->tail->data == 2);
    queue = destroy_queue(queue);
    assert(queue == NULL);
}