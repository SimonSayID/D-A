//
// Created by simon on 8/27/17.
//

#include "main.h"

stacks_t* stacks_avl_init(){
    stacks_t *stacks = (stacks_t *)malloc(sizeof(stacks_t));
    stacks->node = NULL;
    stacks->next = NULL;
    return stacks;
}

void stacks_avl_push(stacks_t *stack, avl_node_t *node){
    stacks_t *new = (stacks_t *)malloc(sizeof(stacks_t));
    if (new != NULL) {
        new->node = node;
        new->next = stack->next;
        stack->next = new;
    }
}

avl_node_t* stacks_avl_top(stacks_t *stacks){
    if (stacks->next != NULL) {
        return stacks->next->node;
    }
    return NULL;
}

void stacks_avl_pop(stacks_t *stack){
    if (stack->next != NULL) {
        stacks_t *first = stack->next;
        stack->next = stack->next->next;
        free(first);
    }
}
