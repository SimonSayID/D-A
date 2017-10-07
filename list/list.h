//
// Created by simon on 17-9-9.
//

#ifndef D_A_LIST_H
#define D_A_LIST_H

#include "../main.h"

typedef struct list_node_s list_node_t;
typedef struct list_s list_t;

struct list_node_s {
    list_node_t *next;
    int data;
};

struct list_s {
    list_node_t *head;
    list_node_t *tail;
};

list_t* list_init();

void list_insert(list_t* list, int data);

void list_delete(list_t* list, int data);

list_node_t* list_find(list_t* list, int data);

#endif //D_A_LIST_H
