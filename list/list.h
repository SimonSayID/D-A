//
// Created by simon on 17-9-9.
//

#ifndef D_A_LIST_H
#define D_A_LIST_H

typedef struct list_s                   list_t;

struct list_s {
    list_t *next;
    int data;
};

list_t *list_init(int data);

void list_insert(list_t *list, int data);

list_t *list_delete(list_t *list, int data);

list_t *list_find(list_t *list, int data);

#endif //D_A_LIST_H
