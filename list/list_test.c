//
// Created by simon on 17-9-9.
//

#include "../main.h"

void list_test() {
    list_t *list = list_init(4);
    list_insert(list, 3);
    list_insert(list, 2);
    list_insert(list, 1);
    list_t *temp = list;
    for (int i = 4; i > 0; --i) {
        assert(temp->data == i);
        temp = temp->next;
    }
    list = list_delete(list, 2);
    assert(list->next->next->data == 1);
    list = list_delete(list, 4);
    assert(list->data == 3);
    list = list_delete(list, 3);
    assert(list->data == 1);
    list = list_delete(list, 1);
    assert(list == NULL);
}