//
// Created by Simon on 2017/10/7.
//

#include "graph_ud_uw.h"

void graph_ud_uw_test() {
    graph_ud_uw_t *graph_ud_uw = graph_ud_uw_init(9);
    graph_ud_uw_add_edge(graph_ud_uw, 0, 1);
    graph_ud_uw_add_edge(graph_ud_uw, 0, 3);
    graph_ud_uw_add_edge(graph_ud_uw, 0, 4);
    graph_ud_uw_add_edge(graph_ud_uw, 1, 5);
    graph_ud_uw_add_edge(graph_ud_uw, 1, 6);
    graph_ud_uw_add_edge(graph_ud_uw, 2, 4);
    graph_ud_uw_add_edge(graph_ud_uw, 2, 5);
    graph_ud_uw_add_edge(graph_ud_uw, 4, 7);
    graph_ud_uw_add_edge(graph_ud_uw, 5, 6);
    graph_ud_uw_add_edge(graph_ud_uw, 8, 9);

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

    int *count = (int *)malloc(sizeof(int));
    result = graph_ud_uw_connected_components(graph_ud_uw, result, count);
    int n = *count;
    vertex_ud_uw_t **components = (vertex_ud_uw_t **)malloc(n * sizeof(vertex_ud_uw_t *));
    for (int i = 0; i < n; ++i) {
        components[i] = (vertex_ud_uw_t *)malloc(sizeof(vertex_ud_uw_t));
        components[i]->head = NULL;
        components[i]->tail = NULL;
    }
    for (int j = 0; j < num; ++j) {
        edge_ud_uw_t *e = (edge_ud_uw_t *)malloc(sizeof(edge_ud_uw_t));
        e->data = j;
        e->next = NULL;
        if (components[result[j]]->head == NULL) {
            components[result[j]]->head = e;
        } else {
            components[result[j]]->tail->next = e;
        }
        components[result[j]]->tail = e;
    }

    edge_ud_uw_t *c1 = components[0]->head;
    for (int k = 0; k < 8; ++k) {
        assert(c1->data == k);
        c1 = c1->next;
    }
    edge_ud_uw_t *c2 = components[1]->head;
    for (int p = 8; p < 10; ++p) {
        assert(c2->data == p);
        c2 = c2->next;
    }


    graph_ud_uw_destroy(graph_ud_uw);
    for (int l = 0; l < n; ++l) {
        edge_ud_uw_t *c = components[l]->head;
        while (c != NULL) {
            edge_ud_uw_t *temp = c;
            c = c->next;
            free(temp);
        }
        free(c);
    }
    free(components);
    free(result);
    free(count);
}