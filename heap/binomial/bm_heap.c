//
// Created by simon on 17-9-12.
//

#include "bm_heap.h"

static void bm_heap_merge_helper(bm_heap_node_t *root, bm_heap_node_t *child) {
    child->parent = root;
    child->next = root->child;
    root->child = child;
    root->degree++;
}

static bm_heap_node_t* bm_heap_merge_core(bm_heap_node_t *a, bm_heap_node_t *b) {

    bm_heap_node_t *head = NULL;
    bm_heap_node_t **chain = &head;

    while (a != NULL && b != NULL) {
        if (a->degree < b->degree) {
            *chain = a;
            a = a->next;
        } else {
            *chain = b;
            b = b->next;
        }
        chain = &(*chain)->next;
    }

    if (a != NULL) {
        *chain = a;
    } else {
        *chain = b;
    }

    return head;
}

static bm_heap_node_t* bm_heap_reverse(bm_heap_node_t *node) {

    bm_heap_node_t *tail = NULL;
    bm_heap_node_t *next = NULL;

    if (node == NULL) {
        return node;
    }

    node->parent = NULL;
    while (node->next != NULL) {
        next = node->next;
        node->next = tail;
        tail = node;
        node = next;
        node->parent = NULL;
    }
    node->next = tail;
    return node;
}

static void bm_heap_union(bm_heap_t* bm_heap, bm_heap_node_t* node) {
    bm_heap_node_t *head = bm_heap->head;;
    bm_heap_node_t *current, *prev, *next;

    if (node == NULL) {
        return;
    }
    if (head == NULL) {
        bm_heap->head = node;
        return;
    }

    head = bm_heap_merge_core(head, node);

    current = head;
    prev = NULL;
    next = current->next;

    while (next != NULL) {

        if (current->degree != next->degree ||
                (next->next != NULL && next->next->degree == current->degree)) {
            prev = current;
            current = next;
        } else if (current->key < next->key) {
            current->next = next->next;
            bm_heap_merge_helper(current, next);
        } else {
            if (prev != NULL) {
                prev->next = next;
            } else {
                head = next;
            }
            bm_heap_merge_helper(next, current);
            current = next;
        }

        next = current->next;
    }

    bm_heap->head = head;
}

bm_heap_t* bm_heap_init() {
    bm_heap_t *heap = (bm_heap_t *)malloc(sizeof(bm_heap_t));
    heap->head = NULL;
    heap->size = 0;
    return heap;
}

bm_heap_t* bm_heap_merge(bm_heap_t* bm_heap, bm_heap_t* add) {
    bm_heap_union(bm_heap, add->head);
    bm_heap->size += add->size;
    return bm_heap;
}

bm_heap_node_t* bm_heap_find_min(bm_heap_t* bm_heap) {
    bm_heap_node_t *temp = bm_heap->head;
    bm_heap_node_t *min = bm_heap->head;
    while (temp != NULL) {
        if (min->key > temp->key) {
            min = temp;
        }
        temp = temp->next;
    }
    return min;
}

void bm_heap_insert(bm_heap_t* bm_heap, bm_heap_data_t data) {
    if (bm_heap != NULL) {
        bm_heap_node_t *node = (bm_heap_node_t *)malloc(sizeof(bm_heap_node_t));
        node->data = data.data;
        node->key = data.key;
        node->degree = 0;
        node->parent = node->next = node->child = NULL;
        bm_heap_union(bm_heap, node);
        bm_heap->size += 1;
    }
}

void bm_heap_delete_min(bm_heap_t* bm_heap) {
    if (bm_heap != NULL) {
        bm_heap_node_t *current = bm_heap->head;
        bm_heap_node_t *next = current->next;
        bm_heap_node_t *prev = NULL;
        bm_heap_node_t *min = bm_heap->head;
        bm_heap_node_t *r = NULL;
        while (next != NULL) {
            if (current->key > next->key) {
                min = next;
                prev = current;
            }
            current = next;
            next = next->next;
        }
        if (prev != NULL) {
            prev->next = min->next;
        } else {
            bm_heap->head = min->next;
        }
        r = min->child;
        free(min);
        bm_heap->size -= 1;
        bm_heap_union(bm_heap, bm_heap_reverse(r));
    }
}

bm_heap_t* bm_heap_destroy(bm_heap_t* bm_heap) {
    while (bm_heap->head != NULL) {
        bm_heap_delete_min(bm_heap);
    }
    free(bm_heap);
    bm_heap = NULL;
    return bm_heap;
}