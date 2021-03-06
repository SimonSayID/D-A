#include "main.h"
#include "test.h"

int main() {
    list_test();
    stack_test();
    queue_test();
    sort_test();
    avl_tree_test();
    rb_tree_test();
    sp_tree_test();
    bm_heap_test();
    hash_test();
    graph_d_uw_test();
    graph_d_w_test();
    graph_ud_uw_test();
    graph_ud_w_test();
    size_t num = 998;
    num = next_prime(num);
    printf("%lld\n", num);
    return 0;
}