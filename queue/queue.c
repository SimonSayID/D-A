//
// Created by simon on 17-9-9.
//

#include "queue.h"

queue_t *queue_init() {
    queue_t *queue = (queue_t *) malloc(sizeof(queue_t));
    queue->head = queue->tail = NULL;
    return queue;
}

void queue_enqueue(queue_t *queue, int data) {
    if (queue != NULL) {
        list_node_t *new = (list_node_t *) malloc(sizeof(list_node_t));
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

int queue_dequeue(queue_t *queue) {
    if (queue->head != NULL) {
        list_node_t *temp = queue->head;
        queue->head = queue->head->next;
        if (queue->head == NULL) {
            queue->tail = NULL;
        }
        int num = temp->data;
        free(temp);
        return num;
    }
}

queue_t *destroy_queue(queue_t *queue) {
    while (queue->head != NULL) {
        queue_dequeue(queue);
    }
    free(queue);
    queue = NULL;
    return queue;
}

int queue_is_empty(queue_t *queue) {
    return queue->head == NULL && queue->tail == NULL;
}

