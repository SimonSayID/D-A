//
// Created by simon on 8/27/17.
//

#ifndef ALG_STACKS_H
#define ALG_STACKS_H

typedef struct stack_s                  stack_t;

struct stack_s {
    int             data;
    stack_t         *next;
};

stack_t* stack_init(int data);

stack_t* stacks_push(stack_t *stack, int data);

stack_t* stack_pop(stack_t *stack);

void stack_top(stack_t *stacks, int *value);

#endif //ALG_STACKS_H
