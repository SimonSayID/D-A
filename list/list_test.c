//
// Created by simon on 17-9-9.
//

#include "list.h"

void list_test() {
    list_t *list = list_init();
    list_insert(list, 0);
    list_insert(list, 1);
    list_insert(list, 2);
    list_insert(list, 3);
    list_node_t *temp = list_find(list, 2);
    assert(temp->data == 2);
    temp = list_find(list, 5);
    assert(temp == NULL);
    temp = list->head;
    for (int i = 0; i < 4; ++i) {
        assert(temp->data == i);
        temp = temp->next;
    }
    list_delete(list, 2);
    assert(list->head->next->data == 1);
    list_delete(list, 3);
    assert(list->head->next->next == NULL);
    list_delete(list, 1);
    assert(list->head->next == NULL);
    list_delete(list, 0);
    assert(list->head == NULL && list->tail == NULL);
    free(list);
}