//
// Created by simon on 8/27/17.
//

#ifndef ALG_STACKS_H
#define ALG_STACKS_H

#include "../main.h"

typedef struct stack_frame_s stack_frame_t;
typedef struct stack_s stack_t;

struct stack_frame_s {
    stack_frame_t* next;
    int data;
};

struct stack_s {
    stack_frame_t* top;
};

stack_t* stack_init();

void stack_push(stack_t *stack, int data);

void stack_pop(stack_t *stack);

int stack_top(stack_t *stacks);

int stack_is_empty(stack_t *stack);

#endif //ALG_STACKS_H
