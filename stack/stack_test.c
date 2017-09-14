//
// Created by Simon on 2017/9/14.
//

#include "../main.h"

void stack_test() {
    stack_t *stack = stack_init();
    stacks_push(stack, 1);
    assert(stack->next->data == 1);
    stacks_push(stack, 2);
    assert(stack->next->data == 2);
    assert(stack->next->next->data == 1);
    stack_pop(stack);
    assert(stack->next->data == 1);
    stacks_push(stack, 3);
    stacks_push(stack, 5);
    int *value = (int *)malloc(sizeof(int));
    stack_top(stack, value);
    assert(*value == 5);
    stack_pop(stack);
    stack_pop(stack);
    stack_pop(stack);
    assert(stack->next == NULL);
    stacks_push(stack, 5);
    stacks_push(stack, 1);
    stacks_push(stack, 3);
    stacks_push(stack, 2);
    stack_clean(stack);
    assert(stack->next == NULL);
    free(value);
}
