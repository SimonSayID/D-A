//
// Created by simon on 17-9-9.
//

#include "list.h"

list_t* list_init() {
    list_t *list = (list_t *) malloc(sizeof(list_t));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void list_insert(list_t* list, int data) {
    list_node_t *node = (list_node_t *)malloc(sizeof(list_node_t));
    node->data = data;
    node->next = NULL;
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
}

void list_delete(list_t* list, int data) {
    list_node_t *head = list->head;
    list_node_t *save = NULL;
    while (head != NULL && head->data != data) {
        save = head;
        head = head->next;
    }
    if (head != NULL) {
        if (save == NULL) {
            list->head = list->head->next;
            if (list->head == NULL) {
                list->tail = NULL;
            }
        } else {
            save->next = head->next;
            if (head->next == NULL) {
                list->tail = save;
            }
        }
        free(head);
    }
}

list_node_t *list_find(list_t* list, int data) {
    list_node_t *head = list->head;
    while (head != NULL) {
        if (head->data == data) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}
