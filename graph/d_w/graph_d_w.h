//
// Created by Simon on 2017/10/14.
//

#ifndef D_A_GRAPH_D_W_H
#define D_A_GRAPH_D_W_H

#include "../../main.h"

typedef struct edge_d_w_s edge_d_w_t;
typedef struct vertex_d_w_s vertex_d_w_t;
typedef struct graph_d_w_s graph_d_w_t;

struct edge_d_w_s {
    edge_d_w_t *next;
    int data;
    int weight;
};

struct vertex_d_w_s {
    edge_d_w_t *head;
    edge_d_w_t *tail;
};

struct graph_d_w_s {
    vertex_d_w_t **array;
    int vn;
    int en;
};

graph_d_w_t* graph_d_w_init(int vn);

void graph_d_w_add_edge(graph_d_w_t *graph_d_w, int v, int w, int weight);

void graph_d_w_destroy(graph_d_w_t *graph_d_w);

#endif //D_A_GRAPH_D_W_H
