//
// Created by simon on 17-9-12.
//

#ifndef D_A_HEAP_H
#define D_A_HEAP_H

#include "../../main.h"

typedef struct bm_heap_node_s bm_heap_node_t;
typedef struct bm_heap_s bm_heap_t;

struct bm_heap_data_s {
    int key;
    int data;
};

typedef struct bm_heap_data_s bm_heap_data_t;

struct bm_heap_node_s {
    bm_heap_node_t *parent;
    bm_heap_node_t *next;
    bm_heap_node_t *child;
    unsigned int degree;
    int key;
    int data;
};

struct bm_heap_s {
    bm_heap_node_t *head;
    int size;
};

bm_heap_t* bm_heap_init();

bm_heap_t* bm_heap_merge(bm_heap_t* bm_heap, bm_heap_t* add);

bm_heap_node_t* bm_heap_find_min(bm_heap_t* bm_heap);

void bm_heap_insert(bm_heap_t* bm_heap, bm_heap_data_t data);

int bm_heap_delete_min(bm_heap_t* bm_heap);

void bm_heap_destroy(bm_heap_t* bm_heap);

int bm_heap_is_empty(bm_heap_t* bm_heap);


#endif //D_A_HEAP_H
