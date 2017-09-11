//
// Created by simon on 17-9-9.
//

#include "../main.h"

list_t *list_init(int data) {
    list_t *list = (list_t *) malloc(sizeof(list_t));
    list->data = data;
    list->next = NULL;
    return list;
}

void list_insert(list_t *list, int data) {
    if (list != NULL) {
        list_t *node = (list_t *) malloc(sizeof(list_t));
        node->data = data;
        node->next = NULL;
        while (list->next != NULL) {
            list = list->next;
        }
        list->next = node;
    }
}

list_t *list_delete(list_t *list, int data) {
    list_t *save = list;
    list_t *head = list;
    while (list != NULL) {
        if (list->data == data) {
            list_t *temp = list;
            save->next = list->next;
            free(temp);
            if (list == head) {
                return save->next;
            } else {
                return head;
            }
        } else {
            save = list;
            list = list->next;
        }
    }
}

list_t *list_find(list_t *list, int data) {
    while (list != NULL) {
        if (list->data == data) {
            return list;
        }
        list = list->next;
    }
    return NULL;
}
