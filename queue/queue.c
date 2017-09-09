//
// Created by simon on 17-9-9.
//

#include "../main.h"

queue_t *queue_init() {
    queue_t *queue = (queue_t *) malloc(sizeof(queue_t));
    queue->head = queue->tail = NULL;
    return queue;
}

void enqueue(queue_t *queue, int data) {
    if (queue != NULL) {
        queue_n_t *new = malloc(sizeof(queue_n_t));
        new->data = data;
        new->next = NULL;
        if (queue->head == NULL) {
            queue->head = new;
        }
        if (queue->tail == NULL) {
            queue->tail = new;
        } else {
            queue->tail->next = new;
            queue->tail = new;
        }
    }
}

void dequeue(queue_t *queue) {
    if (queue->head != NULL) {
        queue_n_t *temp = queue->head;
        queue->head = queue->head->next;
        if (queue->head == NULL) {
            queue->tail = NULL;
        }
        free(temp);
    }
}

queue_t *destroy_queue(queue_t *queue) {
    while (queue->head != NULL) {
        dequeue(queue);
    }
    free(queue);
    queue = NULL;
    return queue;
}

int is_empty(queue_t *queue) {
    return queue->head == NULL && queue->tail == NULL;
}

