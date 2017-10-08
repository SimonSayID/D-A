//
// Created by Simon on 2017/10/7.
//

#include "graph_u.h"

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

    result = depth_first_search(graph_u, 0, result);
    assert(result[0] == 0);
    assert(result[1] == 1);
    assert(result[2] == 5);
    assert(result[3] == 2);
    assert(result[4] == 4);
    assert(result[5] == 7);
    assert(result[6] == 6);
    assert(result[7] == 3);

    result = breadth_first_search(graph_u, 0, result);
    assert(result[0] == 0);
    assert(result[1] == 1);
    assert(result[2] == 3);
    assert(result[3] == 4);
    assert(result[4] == 5);
    assert(result[5] == 6);
    assert(result[6] == 2);
    assert(result[7] == 7);
}