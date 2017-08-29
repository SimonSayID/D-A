//
// Created by simon on 8/27/17.
//

#include <assert.h>
#include "../main.h"

stack_avl_t* stacks_avl_init(){
    stack_avl_t *stacks = (stack_avl_t *)malloc(sizeof(stack_avl_t));
    stacks->node = NULL;
    stacks->next = NULL;
    return stacks;
}

void stacks_avl_push(stack_avl_t *stack, avl_node_t *node){
    stack_avl_t *new = (stack_avl_t *)malloc(sizeof(stack_avl_t));
    if (new != NULL) {
        new->node = node;
        new->next = stack->next;
        stack->next = new;
    }
}

avl_node_t* stacks_avl_top(stack_avl_t *stacks){
    if (stacks->next != NULL) {
        return stacks->next->node;
    }
    return NULL;
}

void stacks_avl_pop(stack_avl_t *stack){
    if (stack->next != NULL) {
        stack_avl_t *first = stack->next;
        stack->next = stack->next->next;
        free(first);
    }
}

void stacks_avl_clean(stack_avl_t *stacks){
    if (stacks != NULL) {
        while (stacks->next != NULL) {
            stacks_avl_pop(stacks);
        }
    } else {
        return;
    }
}