//
// Created by Simon on 2017/10/14.
//

#include "graph_d_w.h"

graph_d_w_t* graph_d_w_init(int vn) {
    graph_d_w_t *graph_d_w = (graph_d_w_t *)malloc(sizeof(graph_d_w_t));
    int len = vn + 1;
    graph_d_w->array = (vertex_d_w_t **)malloc(len * sizeof(vertex_d_w_t *));
    for (int i = 0; i < len; ++i) {
        graph_d_w->array[i] = (vertex_d_w_t *)malloc(sizeof(vertex_d_w_t));
        graph_d_w->array[i]->head = NULL;
        graph_d_w->array[i]->tail = NULL;
    }
    graph_d_w->vn = vn;
    graph_d_w->en = 0;
    return graph_d_w;
}

void graph_d_w_add_edge(graph_d_w_t *graph_d_w, int v, int w, int weight) {
    edge_d_w_t *edge = (edge_d_w_t *)malloc(sizeof(edge_d_w_t));
    edge->data = w;
    edge->next = NULL;
    edge->weight = weight;

    if (graph_d_w->array[v]->head == NULL) {
        graph_d_w->array[v]->head = edge;
        graph_d_w->array[v]->tail = edge;
    } else {
        graph_d_w->array[v]->tail->next = edge;
        graph_d_w->array[v]->tail = edge;
    }
}

void graph_d_w_destroy(graph_d_w_t *graph_d_w) {
    int len = graph_d_w->vn + 1;
    for (int i = 0; i < len; ++i) {
        edge_d_w_t *adj = graph_d_w->array[i]->head;
        while (adj != NULL) {
            edge_d_w_t *temp = adj;
            adj = adj->next;
            free(temp);
        }
        free(graph_d_w->array[i]);
    }
    free(graph_d_w->array);
    free(graph_d_w);
}