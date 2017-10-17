//
// Created by Simon on 2017/10/14.
//

#include "../d_w/graph_d_w.h"

void graph_d_w_test() {
    graph_d_w_t *graph_d_w = graph_d_w_init(7);
    graph_d_w_add_edge(graph_d_w, 0, 1, 1);
    graph_d_w_add_edge(graph_d_w, 0, 3, 3);
    graph_d_w_add_edge(graph_d_w, 0, 4, 2);
    graph_d_w_add_edge(graph_d_w, 1, 5, 1);
    graph_d_w_add_edge(graph_d_w, 1, 6, 4);
    graph_d_w_add_edge(graph_d_w, 2, 4, 5);
    graph_d_w_add_edge(graph_d_w, 2, 5, 8);
    graph_d_w_add_edge(graph_d_w, 4, 7, 3);
    graph_d_w_add_edge(graph_d_w, 5, 6, 7);
    graph_d_w_destroy(graph_d_w);
}