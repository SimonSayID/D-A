//
// Created by simon on 8/27/17.
//

#include "stack.h"

stack_t* stack_init() {
    stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
    stack->top = NULL;
    return stack;
}

void stack_push(stack_t *stack, int data) {
    stack_frame_t *frame = (stack_frame_t *)malloc(sizeof(stack_frame_t));
    frame->data = data;
    frame->next = NULL;
    if (stack->top == NULL) {
        stack->top = frame;
    } else {
        frame->next = stack->top;
        stack->top = frame;
    }
}

void stack_pop(stack_t *stack) {
    stack_frame_t *temp = stack->top;
    stack->top = temp->next;
    free(temp);
}

int stack_top(stack_t *stacks) {
    return stacks->top->data;
}