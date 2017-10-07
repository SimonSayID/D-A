//
// Created by Simon on 2017/9/14.
//

#include "stack.h"

void stack_test() {
    stack_t *stack = stack_init();
    stack_push(stack, 0);
    stack_push(stack, 1);
    assert(stack->top->data == 1);
    assert(stack->top->next->data == 0);
    stack_push(stack, 2);
    assert(stack->top->data == 2);
    assert(stack->top->next->data == 1);
    assert(stack->top->next->next->data == 0);
    stack_pop(stack);
    assert(stack->top->data == 1);
    stack_pop(stack);
    stack_push(stack, 3);
    stack_push(stack, 5);
    int value = stack_top(stack);
    assert(value == 5);
    stack_pop(stack);
    stack_pop(stack);
    stack_pop(stack);
    assert(stack->top == NULL);
    free(stack);
}
