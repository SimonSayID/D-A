//
// Created by Simon on 2017/10/9.
//

#include "graph_ud_w.h"



graph_ud_w_t* graph_ud_w_init(int vn) {
    graph_ud_w_t *graph_ud_w = (graph_ud_w_t *)malloc(sizeof(graph_ud_w_t));
    int len = vn + 1;
    graph_ud_w->array = (vertex_ud_w_t **)malloc(len * sizeof(vertex_ud_w_t *));
    for (int i = 0; i < len; ++i) {
        graph_ud_w->array[i] = (vertex_ud_w_t *)malloc(sizeof(vertex_ud_w_t));
        graph_ud_w->array[i]->head = NULL;
        graph_ud_w->array[i]->tail = NULL;
    }
    graph_ud_w->vn = vn;
    graph_ud_w->en = 0;
    return graph_ud_w;
}

void graph_ud_w_add_edge(graph_ud_w_t *graph_ud_w, int v, int w, int weight) {
    edge_ud_w_t *a = (edge_ud_w_t *)malloc(sizeof(edge_ud_w_t));
    a->data = w;
    a->next = NULL;
    a->weight = weight;
    if (graph_ud_w->array[v]->head == NULL) {
        graph_ud_w->array[v]->head = a;
        graph_ud_w->array[v]->tail = a;
    } else {
        graph_ud_w->array[v]->tail->next = a;
        graph_ud_w->array[v]->tail = a;
    }

    edge_ud_w_t *b = (edge_ud_w_t *)malloc(sizeof(edge_ud_w_t));
    b->data = v;
    b->next = NULL;
    b->weight = weight;
    if (graph_ud_w->array[w]->head == NULL) {
        graph_ud_w->array[w]->head = b;
        graph_ud_w->array[w]->tail = b;
    } else {
        graph_ud_w->array[w]->tail->next = b;
        graph_ud_w->array[w]->tail = b;
    }

    graph_ud_w->en += 1;
}

int** graph_ud_w_single_source_shortest_path(graph_ud_w_t *graph_ud_w, int start) {

}

void graph_ud_w_destroy(graph_ud_w_t *graph_ud_w) {
    int len = graph_ud_w->vn + 1;
    for (int i = 0; i < len; ++i) {
        edge_ud_w_t *adj = graph_ud_w->array[i]->head;
        while (adj != NULL) {
            edge_ud_w_t *temp = adj;
            adj = adj->next;
            free(temp);
        }
        free(graph_ud_w->array[i]);
    }
    free(graph_ud_w->array);
    free(graph_ud_w);
}