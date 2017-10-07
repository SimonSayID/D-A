//
// Created by Simon on 2017/9/27.
//

#include "sp_tree.h"

void sp_tree_test() {
    sp_tree_t *tree = sp_tree_init();
    // zig-right
    sp_insert(tree, 2);
    sp_insert(tree, 1);
    sp_node_t *node = tree->root;
    assert(node->data == 1);
    assert(node->right->data == 2);
    // zig-zig-left
    sp_insert(tree, 3);
    node = tree->root;
    assert(node->data == 3);
    assert(node->left->data == 2);
    assert(node->left->left->data == 1);
    // zig-zig-right and zig-right
    sp_insert(tree, 0);
    node = tree->root;
    assert(node->data == 0);
    assert(node->right->data == 3);
    assert(node->right->left->data == 1);
    assert(node->right->left->right->data == 2);
    // zig-zig-left
    sp_insert(tree, 4);
    node = tree->root;
    assert(node->data == 4);
    assert(node->left->data == 3);
    assert(node->left->left->data == 0);
    assert(node->left->left->right->data == 1);
    assert(node->left->left->right->right->data == 2);
    // zig-left
    sp_insert(tree, 7);
    // zig-zag-right
    sp_insert(tree, 6);
    node = tree->root;
    assert(node->data == 6);
    assert(node->left->data == 4);
    assert(node->right->data == 7);
    // zig-zig-left
    sp_insert(tree, 11);
    // zig-zag-right
    sp_insert(tree, 9);
    // zig-zag-left
    sp_insert(tree, 10);
    node = tree->root;
    assert(node->data == 10);
    assert(node->left->data == 9);
    assert(node->right->data == 11);



    // deletion that trigger find maximum of the left tree and splay
    sp_delete(tree, 3);
    node = tree->root;
    assert(node->data == 2);
    assert(node->left->data == 1);
    assert(node->right->data == 10);
    // deletion that no left tree
    sp_delete(tree , 0);
    node = tree->root;
    assert(node->data == 1);
    assert(node->left == NULL);
    assert(node->right->data == 2);
    // deletion that is normal
    sp_delete(tree , 2);
    node = tree->root;
    assert(node->data == 1);
    assert(node->left == NULL);
    assert(node->right->data == 10);
    // deletion that no left tree
    sp_delete(tree, 1);
    // deletion that no right tree
    sp_delete(tree, 11);
    node = tree->root;
    assert(node->data == 10);
    assert(node->left->data == 7);
    assert(node->right == NULL);



    // search root
    node = sp_search(tree, 10);
    assert(node->data == 10);
    // search left node
    node = sp_search(tree, 7);
    assert(node->data == 7);
    node = tree->root;
    assert(node->data == 7);
    assert(node->left->data == 4);
    assert(node->right->data == 10);
    // search right node
    node = sp_search(tree, 10);
    assert(node->data == 10);
    node = tree->root;
    assert(node->data == 10);
    assert(node->left->data == 7);
    assert(node->right == NULL);



    // clean
    sp_delete(tree, 10);
    sp_delete(tree, 6);
    sp_delete(tree, 9);
    sp_delete(tree, 4);
    sp_delete(tree, 7);
    assert(tree->root == NULL);
    free(tree);
}