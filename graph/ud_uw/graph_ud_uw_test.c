//
// Created by Simon on 2017/10/7.
//

#include "graph_ud_uw.h"

void graph_ud_uw_test() {
    graph_ud_uw_t *graph_ud_uw = graph_ud_uw_init(7);
    graph_ud_uw_add_edge(graph_ud_uw, 0, 1);
    graph_ud_uw_add_edge(graph_ud_uw, 0, 3);
    graph_ud_uw_add_edge(graph_ud_uw, 0, 4);
    graph_ud_uw_add_edge(graph_ud_uw, 1, 5);
    graph_ud_uw_add_edge(graph_ud_uw, 1, 6);
    graph_ud_uw_add_edge(graph_ud_uw, 2, 4);
    graph_ud_uw_add_edge(graph_ud_uw, 2, 5);
    graph_ud_uw_add_edge(graph_ud_uw, 4, 7);
    graph_ud_uw_add_edge(graph_ud_uw, 5, 6);

    int num = graph_ud_uw->vn + 1;
    int *result = (int *)malloc(num * sizeof(int));

    result = graph_ud_uw_depth_first_search(graph_ud_uw, 0, result);
    assert(result[0] == 0);
    assert(result[1] == 1);
    assert(result[2] == 5);
    assert(result[3] == 2);
    assert(result[4] == 4);
    assert(result[5] == 7);
    assert(result[6] == 6);
    assert(result[7] == 3);

    result = graph_ud_uw_breadth_first_search(graph_ud_uw, 0, result);
    assert(result[0] == 0);
    assert(result[1] == 1);
    assert(result[2] == 3);
    assert(result[3] == 4);
    assert(result[4] == 5);
    assert(result[5] == 6);
    assert(result[6] == 2);
    assert(result[7] == 7);

    graph_ud_uw_destroy(graph_ud_uw);
}