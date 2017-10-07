//
// Created by Simon on 2017/10/7.
//

#include "graph.h"

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

void dfs(graph_u_t *graph_u, int start, int *marked) {
    marked[start] = 1;
    printf("%d\n",start);
    edge_u_t *adj = graph_u->array[start].head;
    while (adj != NULL) {
        int num = adj->data;
        if (!marked[num]) {
            dfs(graph_u, num, marked);
        }
        adj = adj->next;
    }
}

int* depth_first_search(graph_u_t *graph_u, int start, int *result) {
//    stack_frame_t *stack = stack_init(start);
    int len = graph_u->vn + 1;
    int marked[len];
    int j = 0;
    for (int i = 0; i < len; ++i) {
        marked[i] = 0;
    }
    marked[start] = 1;
    result[j] = start;
    j++;

    edge_u_t *adj = graph_u->array[start].head;
    while (adj != NULL) {
        int num = adj->data;
        if (marked[num]) {
            adj = adj->next;
        } else {
            marked[num] = 1;
            result[j] = num;
            j++;
            adj = graph_u->array[num].head;
        }
    }

    return result;
}

int* breadth_first_search(graph_u_t *graph_u, int start, int *result) {
    queue_t *queue = queue_init();
    int len = graph_u->vn + 1;
    int marked[len];
    int j = 0;
    for (int i = 0; i < len; ++i) {
        marked[i] = 0;
    }
    queue_enqueue(queue, start);
    marked[start] = 1;
    result[j] = start;
    j++;
    while (!queue_is_empty(queue)) {
        int v = queue_dequeue(queue);
        edge_u_t *adj = graph_u->array[v].head;
        while (adj != NULL) {
            int num = adj->data;
            if (!marked[num]) {
                marked[num] = 1;
                result[j] = num;
                j++;
                queue_enqueue(queue, num);
            }
            adj = adj->next;
        }
    }
    free(queue);
    return result;
}
