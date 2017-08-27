//
// Created by simon on 8/27/17.
//

#ifndef ALG_STACKS_H
#define ALG_STACKS_H

#include "main.h"

struct stacks_s {
    avl_node_t       *node;
    stacks_t         *next;
};

stacks_t* stacks_avl_init();

void stacks_avl_push(stacks_t *stack, avl_node_t *node);

avl_node_t* stacks_avl_top(stacks_t *stacks);

void stacks_avl_pop(stacks_t *stack);

#endif //ALG_STACKS_H
