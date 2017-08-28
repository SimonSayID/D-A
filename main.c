#include "main.h"

int main() {
    avl_node_t *root = avl_tree_init(1);
    root = avl_insert(root, 2);
    root = avl_insert(root, 3);
    root = avl_insert(root, 4);
    root = avl_insert(root, 5);
    root = avl_insert(root, 6);
    root = avl_insert(root, 7);
    root = avl_insert(root, 8);
    root = avl_insert(root, 9);
    root = avl_insert(root, 10);
    root = avl_insert(root, 11);
    root = avl_insert(root, 12);
    root = avl_insert(root, 13);
    root = avl_insert(root, 14);
    root = avl_insert(root, 15);
    root = avl_insert(root, 16);
    root = avl_insert(root, 17);
    root = avl_insert(root, 18);
    root = avl_insert(root, 19);
    root = avl_insert(root, 20);
    root = avl_insert(root, 21);
    root = avl_insert(root, 22);
    root = avl_delete(root, 17);
    root = avl_delete(root, 15);
    root = avl_delete(root, 10);
    root = avl_delete(root, 11);
    root = avl_delete(root, 12);
    avl_node_t *node = avl_search(root, 22);
    node = avl_search(root, 20);
    node = avl_search(root, 17);
    node = avl_search(root, 12);
    node = avl_search(root, 3);
    printf("done\n");
    return 0;
}