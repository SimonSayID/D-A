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
    root = avl_delete(root, 1);
    root = avl_delete(root, 4);
    root = avl_delete(root, 8);
    root = avl_delete(root, 7);
    root = avl_delete(root, 6);
    root = avl_delete(root, 5);
    root = avl_delete(root, 3);
    root = avl_delete(root, 10);
    printf("done\n");
    return 0;
}