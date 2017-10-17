//
// Created by Simon on 2017/10/7.
//

#include "graph_ud_uw.h"

static void dfs(graph_ud_uw_t *graph_ud_uw, int start, int *marked, int *result, int *count);

graph_ud_uw_t* graph_ud_uw_init(int vn) {
    graph_ud_uw_t *graph_ud_uw = (graph_ud_uw_t *)malloc(sizeof(graph_ud_uw_t));
    int len = vn + 1;
    graph_ud_uw->array = (vertex_ud_uw_t **)malloc(len  * sizeof(vertex_ud_uw_t *));
    for (int i = 0; i < len; ++i) {
        graph_ud_uw->array[i] = (vertex_ud_uw_t *)malloc(sizeof(vertex_ud_uw_t));
        graph_ud_uw->array[i]->head = NULL;
        graph_ud_uw->array[i]->tail = NULL;
    }
    graph_ud_uw->vn = vn;
    graph_ud_uw->en = 0;
    return graph_ud_uw;
}

void graph_ud_uw_add_edge(graph_ud_uw_t *graph_ud_uw, int v, int w) {
    edge_ud_uw_t *a = (edge_ud_uw_t *)malloc(sizeof(edge_ud_uw_t));
    a->data = w;
    a->next = NULL;
    if (graph_ud_uw->array[v]->head == NULL) {
        graph_ud_uw->array[v]->head = a;
    } else {
        graph_ud_uw->array[v]->tail->next = a;
    }
    graph_ud_uw->array[v]->tail = a;

    edge_ud_uw_t *b = (edge_ud_uw_t *)malloc(sizeof(edge_ud_uw_t));
    b->data = v;
    b->next = NULL;
    if (graph_ud_uw->array[w]->head == NULL) {
        graph_ud_uw->array[w]->head = b;
    } else {
        graph_ud_uw->array[w]->tail->next = b;
    }
    graph_ud_uw->array[w]->tail = b;

    graph_ud_uw->en += 1;
}

int* graph_ud_uw_depth_first_search(graph_ud_uw_t *graph_ud_uw, int start, int *result) {
    stack_t *stack = stack_init();
    int len = graph_ud_uw->vn + 1;
    int marked[len];
    int r_pos = 0;

    for (int i = 0; i < len; ++i) {
        marked[i] = 0;
    }

    stack_push(stack, start);

    while (!stack_is_empty(stack)) {
        int n = stack_top(stack);
        if (!marked[n]) {
            marked[n] = 1;
            result[r_pos] = n;
            r_pos++;
        }
        edge_ud_uw_t *adj = graph_ud_uw->array[n]->head;
        while (adj != NULL) {
            int num = adj->data;
            if (marked[num]) {
                adj = adj->next;
            } else {
                marked[num] = 1;
                result[r_pos] = num;
                r_pos++;
                edge_ud_uw_t *e = adj->next;
                while (e != NULL) {
                    if (!marked[e->data]) {
                        stack_push(stack, e->data);
                    }
                    e = e->next;
                }
                adj = graph_ud_uw->array[num]->head;
            }
        }
        stack_pop(stack);
    }
    free(stack);

    return result;
}

int* graph_ud_uw_breadth_first_search(graph_ud_uw_t *graph_ud_uw, int start, int *result) {
    queue_t *queue = queue_init();
    int len = graph_ud_uw->vn + 1;
    int marked[len];
    int r_pos = 0;

    for (int i = 0; i < len; ++i) {
        marked[i] = 0;
    }

    queue_enqueue(queue, start);
    marked[start] = 1;
    result[r_pos] = start;
    r_pos++;

    while (!queue_is_empty(queue)) {
        int v = queue_dequeue(queue);
        edge_ud_uw_t *adj = graph_ud_uw->array[v]->head;
        while (adj != NULL) {
            int num = adj->data;
            if (!marked[num]) {
                marked[num] = 1;
                result[r_pos] = num;
                r_pos++;
                queue_enqueue(queue, num);
            }
            adj = adj->next;
        }
    }

    free(queue);

    return result;
}

int* graph_ud_uw_connected_components(graph_ud_uw_t *graph_ud_uw, int *result, int *count) {
    int len = graph_ud_uw->vn + 1;
    int *marked = (int *)malloc(len * sizeof(int));
    *count = 0;
    for (int i = 0; i < len; ++i) {
        marked[i] = 0;
        result[i] = 0;
    }
    for (int j = 0; j < len; ++j) {
        if (!marked[j]) {
            dfs(graph_ud_uw, j, marked, result, count);
            *count += 1;
        }
    }
    return result;
}

static void dfs(graph_ud_uw_t *graph_ud_uw, int start, int *marked, int *result, int *count) {
    stack_t *stack = stack_init();
    int len = graph_ud_uw->vn + 1;

    for (int i = 0; i < len; ++i) {
        marked[i] = 0;
    }

    stack_push(stack, start);

    while (!stack_is_empty(stack)) {
        int n = stack_top(stack);
        if (!marked[n]) {
            marked[n] = 1;
            result[n] = *count;
        }
        edge_ud_uw_t *adj = graph_ud_uw->array[n]->head;
        while (adj != NULL) {
            int num = adj->data;
            if (marked[num]) {
                adj = adj->next;
            } else {
                marked[num] = 1;
                result[num] = *count;
                edge_ud_uw_t *e = adj->next;
                while (e != NULL) {
                    if (!marked[e->data]) {
                        stack_push(stack, e->data);
                    }
                    e = e->next;
                }
                adj = graph_ud_uw->array[num]->head;
            }
        }
        stack_pop(stack);
    }
    free(stack);
}

void graph_ud_uw_destroy(graph_ud_uw_t *graph_ud_uw) {
    int len = graph_ud_uw->vn + 1;
    for (int i = 0; i < len; ++i) {
        edge_ud_uw_t *adj = graph_ud_uw->array[i]->head;
        while (adj != NULL) {
            edge_ud_uw_t *del = adj;
            adj = adj->next;
            free(del);
        }
        free(graph_ud_uw->array[i]);
    }
    free(graph_ud_uw->array);
    free(graph_ud_uw);
}