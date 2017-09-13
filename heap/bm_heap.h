//
// Created by simon on 17-9-12.
//

#ifndef D_A_HEAP_H
#define D_A_HEAP_H

#include "../main.h"

typedef struct bm_heap_node_s bm_heap_node_t;

struct bm_heap_node_s {
    int data;
    bm_heap_node_t *left;
    bm_heap_node_t *next_sibling;
};


#endif //D_A_HEAP_H
