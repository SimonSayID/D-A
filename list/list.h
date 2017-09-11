//
// Created by simon on 17-9-9.
//

#ifndef D_A_LIST_H
#define D_A_LIST_H

#include "../main.h"

struct list_s {
    int data;
    list_t *next;
};

list_t *list_init(int data);

void list_insert(list_t *list, int data);

list_t *list_delete(list_t *list, int data);

list_t *list_find(list_t *list, int data);

void list_test();

#endif //D_A_LIST_H
