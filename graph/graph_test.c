//
// Created by Simon on 2017/10/7.
//

#include "graph.h"

void graph_test() {
    graph_u_t *graph_u = graph_u_init(7);
    graph_u_add_edge(graph_u, 0, 1);
    graph_u_add_edge(graph_u, 0, 3);
    graph_u_add_edge(graph_u, 0, 4);
    graph_u_add_edge(graph_u, 1, 5);
    graph_u_add_edge(graph_u, 1, 6);
    graph_u_add_edge(graph_u, 2, 4);
    graph_u_add_edge(graph_u, 2, 5);
    graph_u_add_edge(graph_u, 4, 7);
    graph_u_add_edge(graph_u, 5, 6);
    int num = graph_u->vn + 1;
    int *result = (int *)malloc(num * sizeof(int));
    result = breadth_first_search(graph_u, 0, result);
    for (int i = 0; i < num; ++i) {
        printf("%d\n",result[i]);
    }
}