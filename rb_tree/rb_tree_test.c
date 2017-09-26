//
// Created by simon on 17-8-31.
//

#include "rb_tree.h"

void rb_tree_test() {

    rb_tree_t *tree = rb_tree_init();
    rb_tree_insert(tree, 1);
    rb_tree_insert(tree, 2);
    rb_tree_insert(tree, 3);
    assert(tree->root->data == 2);
    assert(tree->root->left->data == 1);
    assert(tree->root->left->color == 1);
    assert(tree->root->right->data == 3);
    assert(tree->root->right->color == 1);
    rb_tree_insert(tree, 4);
    assert(tree->root->left->color == 0);
    assert(tree->root->right->color == 0);
    rb_tree_delete(tree, 2);
    assert(tree->root->data == 3);
    assert(tree->root->left->data == 1);
    assert(tree->root->left->color == 1);
    assert(tree->root->right->data == 4);
    assert(tree->root->right->color == 1);

}