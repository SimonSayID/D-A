//
// Created by Simon on 2017/10/7.
//

#ifndef D_A_GRAPH_H
#define D_A_GRAPH_H

#include "../main.h"
#include "../stack/stack.h"
#include "../queue/queue.h"

typedef struct edge_u_s edge_u_t;
typedef struct vertex_u_s vertex_u_t;
typedef struct graph_u_s graph_u_t;

struct edge_u_s {
    edge_u_t *next;
    int data;
};

struct vertex_u_s {
    edge_u_t *head;
    edge_u_t *tail;
};

struct graph_u_s {
    vertex_u_t *array;
    int vn;
    int en;
};

graph_u_t* graph_u_init(int v_num);

void graph_u_add_edge(graph_u_t *graph_u, int v, int w);

int* depth_first_search(graph_u_t *graph_u, int start, int *result);

int* breadth_first_search(graph_u_t *graph_u, int start, int *result);


#endif //D_A_GRAPH_H
