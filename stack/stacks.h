//
// Created by simon on 8/27/17.
//

#ifndef ALG_STACKS_H
#define ALG_STACKS_H

#include "../main.h"

struct stack_s {
    int             data;
    stack_t         *next;
};

stack_t* stack_init();

void stacks_push(stack_t *stack, int data);

void stack_top(stack_t *stacks, int *value);

void stack_pop(stack_t *stack);

void stack_clean(stack_t *stacks);

void stack_test();

#endif //ALG_STACKS_H
