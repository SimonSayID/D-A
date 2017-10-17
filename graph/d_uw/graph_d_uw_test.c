//
// Created by Simon on 2017/10/14.
//

#include "../d_uw/graph_d_uw.h"

void graph_d_uw_test() {
    graph_d_uw_t *graph_d_uw = graph_d_uw_init(9);
    graph_d_uw_add_edge(graph_d_uw, 0, 1);
    graph_d_uw_add_edge(graph_d_uw, 0, 3);
    graph_d_uw_add_edge(graph_d_uw, 0, 4);
    graph_d_uw_add_edge(graph_d_uw, 1, 5);
    graph_d_uw_add_edge(graph_d_uw, 1, 6);
    graph_d_uw_add_edge(graph_d_uw, 2, 4);
    graph_d_uw_add_edge(graph_d_uw, 2, 5);
    graph_d_uw_add_edge(graph_d_uw, 4, 7);
    graph_d_uw_add_edge(graph_d_uw, 5, 6);
    graph_d_uw_add_edge(graph_d_uw, 8, 9);
    graph_d_uw_destroy(graph_d_uw);
}