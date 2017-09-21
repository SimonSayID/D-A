//
// Created by simon on 17-9-12.
//

#include "../main.h"

void bm_heap_test() {

    bm_heap_data_t d1, d2, d3;

    d1.key = 5;
    d1.data = 11;
    d2.key = 1;
    d2.data = 22;
    d3.key = 9;
    d3.data = 33;

    bm_heap_t *h1 = bm_heap_init();
    bm_heap_insert(h1, d1);
    bm_heap_insert(h1, d2);
    bm_heap_insert(h1, d3);

    bm_heap_node_t *min = bm_heap_find_min(h1);
    assert(min->key == 1);

    bm_heap_data_t v1, v2, v3;
    v1.key = 7;
    v1.data = 44;
    v2.key = 0;
    v2.data = 66;
    v3.key = 10;
    v3.data = 55;

    bm_heap_t *h2 = bm_heap_init();
    bm_heap_insert(h2, v1);
    bm_heap_insert(h2, v2);
    bm_heap_insert(h2, v3);

    bm_heap_t *h3 = bm_heap_merge(h1, h2);
    bm_heap_delete_min(h3);
    min = bm_heap_find_min(h3);
    assert(min->key == 1);

    h3 = bm_heap_destroy(h3);
    assert(h3 == NULL);
}