//
// Created by simon on 8/27/17.
//

#include "stacks.h"
#include "../main.h"

stack_t* stack_init(int data){
    stack_t *stacks = (stack_t *)malloc(sizeof(stack_t));
    stacks->data = data;
    stacks->next = NULL;
    return stacks;
}

stack_t* stacks_push(stack_t *stack, int data){
    stack_t *new = (stack_t *)malloc(sizeof(stack_t));
    if (new != NULL) {
        new->data = data;
        new->next = stack;
        stack = new;
        return stack;
    }
    return NULL;
}

void stack_top(stack_t *stacks, int *value){
    if (stacks != NULL) {
        *value = stacks->data;
    }
}

stack_t* stack_pop(stack_t *stack){
    if (stack != NULL) {
        stack_t *first = stack;
        stack = stack->next;
        free(first);
    }
    return stack;
}