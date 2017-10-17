//
// Created by Simon on 2017/10/14.
//

#ifndef D_A_GRAPH_D_UW_H
#define D_A_GRAPH_D_UW_H

#include "../../main.h"

typedef struct edge_d_uw_s edge_d_uw_t;
typedef struct vertex_d_uw_s vertex_d_uw_t;
typedef struct graph_d_uw_s graph_d_uw_t;

struct edge_d_uw_s {
    edge_d_uw_t *next;
    int data;
};

struct vertex_d_uw_s {
    edge_d_uw_t *head;
    edge_d_uw_t *tail;
};

struct graph_d_uw_s {
    vertex_d_uw_t **array;
    int vn;
    int en;
};

graph_d_uw_t* graph_d_uw_init(int vn);

void graph_d_uw_add_edge(graph_d_uw_t *graph_d_w, int v, int w);

void graph_d_uw_destroy(graph_d_uw_t *graph_d_w);

#endif //D_A_GRAPH_D_UW_H
