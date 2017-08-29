//
// Created by simon on 8/27/17.
//

#include <assert.h>
#include "main.h"

stacks_t* stack_init(){
    stacks_t *stack = (stacks_t *) malloc(sizeof(stack));
    stack->data = NULL;
    stack->next = NULL;
    return stack;
}

void stack_push(stacks_t* stack, void *data){
    if (stack != NULL) {
        stacks_t *new = (stacks_t *) malloc(sizeof(stacks_t));
        new->data = data;
        new->next = NULL;
        stack->next = new;
    } else {
        return;
    }
}

stacks_t* stack_top(stacks_t* stack){
    if (stack != NULL) {
        stacks_t *res = stack->next;
        return res;
    }
    return NULL;
}

void stack_pop(stacks_t *stack){
    if (stack != NULL) {
        stacks_t *del = stack->next;
        stack->next = stack->next->next;
        free(del);
    }
}

void stack_clean(stacks_t *stack){
    if (stack != NULL) {
        while (stack->next != NULL) {
            stack_pop(stack);
        }
    } else {
        return;
    }
}

void stack_test(){
    /* data */
    int *a = (int *)malloc(sizeof(int));
    *a = 1;
    int *b = (int *)malloc(sizeof(int));
    *b = 2;
    int *c = (int *)malloc(sizeof(int));
    *c = 3;

    stacks_t *test = stack_init();
    stack_push(test, (void *)a);
    assert(test->next != NULL);
    stack_pop(test);
    assert(test->next == NULL);
    stack_push(test, (void *)b);
    stack_pop(test);
    stack_push(test, (void *)a);
    stack_push(test, (void *)b);
    stack_push(test, (void *)c);
    int *f = (int *)stack_top(test)->data;
    assert(*f == 3);
    stack_clean(test);
    assert(test->next == NULL);
    free(test);
    free(a);
    free(b);
    free(c);
}

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