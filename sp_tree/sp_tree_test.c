//
// Created by Simon on 2017/9/27.
//

#include "sp_tree.h"

void sp_tree_test() {
    sp_node_t *node = sp_tree_init(2);
    // zig-right
    node = sp_insert(node, 1);
    assert(node->data == 1);
    assert(node->right->data == 2);
    // zig-zig-left
    node = sp_insert(node, 3);
    assert(node->data == 3);
    assert(node->left->data == 2);
    assert(node->left->left->data == 1);
    // zig-zig-right and zig-right
    node = sp_insert(node, 0);
    assert(node->data == 0);
    assert(node->right->data == 3);
    assert(node->right->left->data == 1);
    assert(node->right->left->right->data == 2);
    // zig-zig-left
    node = sp_insert(node, 4);
    assert(node->data == 4);
    assert(node->left->data == 3);
    assert(node->left->left->data == 0);
    assert(node->left->left->right->data == 1);
    assert(node->left->left->right->right->data == 2);
    // zig-left
    node = sp_insert(node, 7);
    // zig-zag-right
    node = sp_insert(node, 6);
    assert(node->data == 6);
    assert(node->left->data == 4);
    assert(node->right->data == 7);
    // zig-zig-left
    node = sp_insert(node, 11);
    // zig-zag-right
    node = sp_insert(node, 9);
    // zig-zag-left
    node = sp_insert(node, 10);
    assert(node->data == 10);
    assert(node->left->data == 9);
    assert(node->right->data == 11);



    // deletion that trigger find maximum of the left tree and splay
    node = sp_delete(node, 3);
    assert(node->data == 2);
    assert(node->left->data == 1);
    assert(node->right->data == 10);
    // deletion that no left tree
    node = sp_delete(node , 0);
    assert(node->data == 1);
    assert(node->left == NULL);
    assert(node->right->data == 2);
    // deletion that is normal
    node = sp_delete(node , 2);
    assert(node->data == 1);
    assert(node->left == NULL);
    assert(node->right->data == 10);
    // deletion that no left tree
    node = sp_delete(node, 1);
    // deletion that no right tree
    node = sp_delete(node, 11);
    assert(node->data == 10);
    assert(node->left->data == 7);
    assert(node->right == NULL);



    // search root
    node = sp_search(node, 10);
    // search left node
    node = sp_search(node, 7);
    assert(node->data == 7);
    assert(node->left->data == 4);
    assert(node->right->data == 10);
    // search right node
    node = sp_search(node, 10);
    assert(node->data == 10);
    assert(node->left->data == 7);
    assert(node->right == NULL);



    // clean
    node = sp_delete(node, 10);
    node = sp_delete(node, 6);
    node = sp_delete(node, 9);
    node = sp_delete(node, 4);
    node = sp_delete(node, 7);
    assert(node == NULL);
}