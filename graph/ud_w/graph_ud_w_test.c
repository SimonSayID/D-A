//
// Created by Simon on 2017/10/9.
//

#include "graph_ud_w.h"

void graph_ud_w_test() {
    graph_ud_w_t *graph_ud_w = graph_ud_w_init(7);
    graph_ud_w_add_edge(graph_ud_w, 0, 1, 1);
    graph_ud_w_add_edge(graph_ud_w, 0, 3, 3);
    graph_ud_w_add_edge(graph_ud_w, 0, 4, 2);
    graph_ud_w_add_edge(graph_ud_w, 1, 5, 1);
    graph_ud_w_add_edge(graph_ud_w, 1, 6, 4);
    graph_ud_w_add_edge(graph_ud_w, 2, 4, 5);
    graph_ud_w_add_edge(graph_ud_w, 2, 5, 8);
    graph_ud_w_add_edge(graph_ud_w, 4, 7, 3);
    graph_ud_w_add_edge(graph_ud_w, 5, 6, 7);
    graph_ud_w_destroy(graph_ud_w);
}