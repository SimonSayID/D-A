//
// Created by simon on 8/27/17.
//

#ifndef ALG_STACKS_H
#define ALG_STACKS_H

#include "../main.h"

struct stack_avl_s {
    avl_node_t       *node;
    stack_avl_t         *next;
};

stack_avl_t* stacks_avl_init();

void stacks_avl_push(stack_avl_t *stack, avl_node_t *node);

avl_node_t* stacks_avl_top(stack_avl_t *stacks);

void stacks_avl_pop(stack_avl_t *stack);

void stacks_avl_clean(stack_avl_t *stacks);

#endif //ALG_STACKS_H
