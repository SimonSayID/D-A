//
// Created by simon on 8/27/17.
//

#include "../main.h"

stack_t* stack_init(){
    stack_t *stacks = (stack_t *)malloc(sizeof(stack_t));
    stacks->data = -1;
    stacks->next = NULL;
    return stacks;
}

void stacks_push(stack_t *stack, int data){
    stack_t *new = (stack_t *)malloc(sizeof(stack_t));
    if (new != NULL) {
        new->data = data;
        new->next = stack->next;
        stack->next = new;
    }
}

void stack_top(stack_t *stacks, int *value){
    if (stacks != NULL) {
        *value = stacks->next->data;
    }
}

void stack_pop(stack_t *stack){
    if (stack->next != NULL) {
        stack_t *first = stack->next;
        stack->next = stack->next->next;
        free(first);
    }
}

void stack_clean(stack_t *stacks){
    if (stacks != NULL) {
        while (stacks->next != NULL) {
            stack_pop(stacks);
        }
    } else {
        return;
    }
}