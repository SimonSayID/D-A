//
// Created by Simon on 2017/10/7.
//

#include "graph_u.h"

graph_u_t* graph_u_init(int v_num) {
    graph_u_t *graph_u = (graph_u_t *)malloc(sizeof(graph_u_t));
    graph_u->array = (vertex_u_t *)malloc(v_num  * sizeof(vertex_u_t));
    for (int i = 0; i <= v_num; ++i) {
        graph_u->array[i].head = (edge_u_t *)malloc(sizeof(edge_u_t));
        graph_u->array[i].tail = NULL;
    }
    graph_u->vn = v_num;
    graph_u->en = 0;
    return graph_u;
}

void graph_u_add_edge(graph_u_t *graph_u, int v, int w) {
    if (graph_u != NULL) {
        if (graph_u->array[v].tail == NULL) {
            graph_u->array[v].head->data = w;
            graph_u->array[v].head->next = NULL;
            graph_u->array[v].tail = graph_u->array[v].head;
        } else {
            edge_u_t *a = (edge_u_t *)malloc(sizeof(edge_u_t));
            a->data = w;
            a->next = NULL;
            graph_u->array[v].tail->next = a;
            graph_u->array[v].tail = a;
        }

        if (graph_u->array[w].tail == NULL) {
            graph_u->array[w].head->data = v;
            graph_u->array[w].head->next = NULL;
            graph_u->array[w].tail = graph_u->array[w].head;
        } else {
            edge_u_t *b = (edge_u_t *)malloc(sizeof(edge_u_t));
            b->data = v;
            b->next = NULL;
            graph_u->array[w].tail->next = b;
            graph_u->array[w].tail = b;
        }

        graph_u->en += 1;
    }
}

int* depth_first_search(graph_u_t *graph_u, int start, int *result) {
    stack_t *stack = stack_init();
    int len = graph_u->vn + 1;
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
            edge_u_t *adj = graph_u->array[current].head;
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

    return result;
}

int* breadth_first_search(graph_u_t *graph_u, int start, int *result) {
    queue_t *queue = queue_init();
    int len = graph_u->vn + 1;
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
        edge_u_t *adj = graph_u->array[v].head;
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
