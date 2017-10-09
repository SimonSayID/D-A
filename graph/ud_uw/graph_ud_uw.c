//
// Created by Simon on 2017/10/7.
//

#include "graph_ud_uw.h"

graph_ud_uw_t* graph_ud_uw_init(int v_num) {
    graph_ud_uw_t *graph_ud_uw = (graph_ud_uw_t *)malloc(sizeof(graph_ud_uw_t));
    graph_ud_uw->array = (vertex_ud_uw_t *)malloc(v_num  * sizeof(vertex_ud_uw_t));
    for (int i = 0; i <= v_num; ++i) {
        graph_ud_uw->array[i].head = (edge_ud_uw_t *)malloc(sizeof(edge_ud_uw_t));
        graph_ud_uw->array[i].tail = NULL;
    }
    graph_ud_uw->vn = v_num;
    graph_ud_uw->en = 0;
    return graph_ud_uw;
}

void graph_ud_uw_add_edge(graph_ud_uw_t *graph_ud_uw, int v, int w) {
    if (graph_ud_uw != NULL) {
        if (graph_ud_uw->array[v].tail == NULL) {
            graph_ud_uw->array[v].head->data = w;
            graph_ud_uw->array[v].head->next = NULL;
            graph_ud_uw->array[v].tail = graph_ud_uw->array[v].head;
        } else {
            edge_ud_uw_t *a = (edge_ud_uw_t *)malloc(sizeof(edge_ud_uw_t));
            a->data = w;
            a->next = NULL;
            graph_ud_uw->array[v].tail->next = a;
            graph_ud_uw->array[v].tail = a;
        }

        if (graph_ud_uw->array[w].tail == NULL) {
            graph_ud_uw->array[w].head->data = v;
            graph_ud_uw->array[w].head->next = NULL;
            graph_ud_uw->array[w].tail = graph_ud_uw->array[w].head;
        } else {
            edge_ud_uw_t *b = (edge_ud_uw_t *)malloc(sizeof(edge_ud_uw_t));
            b->data = v;
            b->next = NULL;
            graph_ud_uw->array[w].tail->next = b;
            graph_ud_uw->array[w].tail = b;
        }

        graph_ud_uw->en += 1;
    }
}

int* graph_ud_uw_depth_first_search(graph_ud_uw_t *graph_ud_uw, int start, int *result) {
    stack_t *stack = stack_init();
    int len = graph_ud_uw->vn + 1;
    int marked[len];
    int r_pos = 0;

    for (int i = 0; i < len; ++i) {
        marked[i] = 0;
    }

    for (int j = start; j < len; ++j) {
        if (marked[j]) {
            continue;
        }
        stack_push(stack, j);
        marked[j] = 1;
        result[r_pos] = j;
        r_pos++;
        while (!stack_is_empty(stack)) {
            int current = stack_top(stack);
            edge_ud_uw_t *adj = graph_ud_uw->array[current].head;
            while (adj != NULL) {
                int v = adj->data;
                if (!marked[v]) {
                    stack_push(stack, v);
                    marked[v] = 1;
                    result[r_pos] = v;
                    r_pos++;
                    break;
                }
                adj = adj->next;
            }
            if (stack_top(stack) != current) {
                continue;
            }
            stack_pop(stack);
        }
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
        edge_ud_uw_t *adj = graph_ud_uw->array[v].head;
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