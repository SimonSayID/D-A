//
// Created by Simon on 2017/10/14.
//

#include "graph_d_uw.h"

graph_d_uw_t* graph_d_uw_init(int vn) {
    graph_d_uw_t *graph_d_uw = (graph_d_uw_t *)malloc(sizeof(graph_d_uw));
    graph_d_uw->array = (vertex_d_uw_t **)malloc(sizeof(vertex_d_uw_t *));
    int len = vn + 1;
    for (int i = 0; i <= len; ++i) {
        graph_d_uw->array[i] = (vertex_d_uw_t *)malloc(sizeof(vertex_d_uw_t));
        graph_d_uw->array[i]->head = NULL;
        graph_d_uw->array[i]->tail = NULL;
    }
    graph_d_uw->vn = len;
    graph_d_uw->en = 0;
    return graph_d_uw;
}

void graph_d_uw_add_edge(graph_d_uw_t *graph_d_uw, int v, int w) {
    edge_d_uw_t *edge = (edge_d_uw_t *)malloc(sizeof(edge_d_uw_t));
    edge->data = w;

    if (graph_d_uw->array[v]->head == NULL) {
        graph_d_uw->array[v]->head = edge;
        graph_d_uw->array[v]->tail = edge;
    } else {
        graph_d_uw->array[v]->tail->next = edge;
        graph_d_uw->array[v]->tail = edge;
    }
}

void graph_d_uw_destroy(graph_d_uw_t *graph_d_uw) {
    int len = graph_d_uw->vn + 1;
    for (int i = 0; i < len; ++i) {
        edge_d_uw_t *adj = graph_d_uw->array[i]->head;
        while (adj != NULL) {
            edge_d_uw_t *temp = adj;
            adj = adj->next;
            free(temp);
        }
        free(graph_d_uw->array[i]);
    }
    free(graph_d_uw->array);
    free(graph_d_uw);
}

int* graph_d_uw_depth_first_search(graph_d_uw_t *graph_d_uw, int start, int *result) {

}

int* graph_d_uw_breadth_first_search(graph_d_uw_t *graph_d_uw, int start, int *result) {

}