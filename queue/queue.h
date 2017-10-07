//
// Created by simon on 17-9-9.
//

#ifndef D_A_QUEUE_H
#define D_A_QUEUE_H

#include "../list/list.h"
#include "../main.h"

typedef struct queue_s                  queue_t;

struct queue_s {
    list_node_t *head;
    list_node_t *tail;
};

queue_t *queue_init();

void queue_enqueue(queue_t *queue, int data);

int queue_dequeue(queue_t *queue);

queue_t *destroy_queue(queue_t *queue);

int queue_is_empty(queue_t *queue);

#endif //D_A_QUEUE_H
