//
// Created by Simon on 2017/10/7.
//

#ifndef D_A_GRAPH_H
#define D_A_GRAPH_H

#include "../../main.h"
#include "../../stack/stack.h"
#include "../../queue/queue.h"

typedef struct edge_ud_uw_s edge_ud_uw_t;
typedef struct vertex_ud_uw_s vertex_ud_uw_t;
typedef struct graph_ud_uw_s graph_ud_uw_t;

struct edge_ud_uw_s {
    edge_ud_uw_t *next;
    int data;
};

struct vertex_ud_uw_s {
    edge_ud_uw_t *head;
    edge_ud_uw_t *tail;
};

struct graph_ud_uw_s {
    vertex_ud_uw_t *array;
    int vn;
    int en;
};

graph_ud_uw_t* graph_u_init(int v_num);

void graph_u_add_edge(graph_ud_uw_t *graph_u, int v, int w);

int* depth_first_search(graph_ud_uw_t *graph_u, int start, int *result);

int* breadth_first_search(graph_ud_uw_t *graph_u, int start, int *result);

#endif //D_A_GRAPH_H
