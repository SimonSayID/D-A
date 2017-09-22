//
// Created by Simon on 2017/9/14.
//

#include "stacks.h"

void stack_test() {
    stack_t *stack = stack_init(0);
    stack = stacks_push(stack, 1);
    assert(stack->data == 1);
    assert(stack->next->data == 0);
    stack = stacks_push(stack, 2);
    assert(stack->data == 2);
    assert(stack->next->data == 1);
    assert(stack->next->next->data == 0);
    stack = stack_pop(stack);
    assert(stack->data == 1);
    stack = stack_pop(stack);
    stack = stacks_push(stack, 3);
    stack = stacks_push(stack, 5);
    int *value = (int *)malloc(sizeof(int));
    stack_top(stack, value);
    assert(*value == 5);
    stack = stack_pop(stack);
    stack = stack_pop(stack);
    stack = stack_pop(stack);
    assert(stack == NULL);
    free(value);
}
