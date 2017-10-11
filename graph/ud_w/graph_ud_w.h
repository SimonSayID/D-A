//
// Created by Simon on 2017/10/9.
//

#ifndef D_A_GRAPH_UD_W_H
#define D_A_GRAPH_UD_W_H

#include "../../main.h"

typedef struct edge_ud_w_s edge_ud_w_t;
typedef struct vertex_ud_w_s vertex_ud_w_t;
typedef struct graph_ud_w_s graph_ud_w_t;

struct edge_ud_w_s {
    edge_ud_w_t *next;
    int data;
    int weight;
};

struct vertex_ud_w_s {
    edge_ud_w_t *head;
    edge_ud_w_t *tail;
};

struct graph_ud_w_s {
    vertex_ud_w_t **array;
    int vn;
    int en;
};

graph_ud_w_t* graph_ud_w_init(int vn);

void graph_ud_w_add_edge(graph_ud_w_t *graph_ud_w, int v, int w, int weight);

int** graph_ud_w_single_source_shortest_path(graph_ud_w_t *graph_ud_w, int start);

void graph_ud_w_destroy(graph_ud_w_t *graph_ud_w);

#endif //D_A_GRAPH_UD_W_H
