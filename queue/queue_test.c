//
// Created by simon on 17-9-9.
//

#include "queue.h"

void queue_test() {
    int i;
    queue_t *queue = queue_init();
    queue_enqueue(queue, 1);
    queue_enqueue(queue, 2);
    assert(queue->head->data == 1);
    assert(queue->tail->data == 2);
    queue_dequeue(queue);
    queue_dequeue(queue);
    i = queue_is_empty(queue);
    assert(i == 1);
    queue_enqueue(queue, 3);
    queue_enqueue(queue, 4);
    queue_enqueue(queue, 5);
    assert(queue->head->data == 3);
    assert(queue->tail->data == 5);
    i = queue_dequeue(queue);
    assert(i == 3);
    i = queue_dequeue(queue);
    assert(i == 4);
    i = queue_is_empty(queue);
    assert(i == 0);
    queue_enqueue(queue, 1);
    queue_enqueue(queue, 2);
    assert(queue->head->data == 5);
    assert(queue->tail->data == 2);
    queue = destroy_queue(queue);
    assert(queue == NULL);
}