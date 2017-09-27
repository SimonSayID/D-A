//
// Created by simon on 17-8-31.
//

#include "rb_tree.h"

void rb_tree_test() {

    // left rotation
    rb_node_t *root = rb_tree_init(1);
    root = rb_tree_insert(root, 2);
    root = rb_tree_insert(root, 3);
    assert(root->data == 2);
    assert(rb_color_is_black(root));
    assert(root->left->data == 1);
    assert(rb_color_is_red(root->left));
    assert(root->right->data == 3);
    assert(rb_color_is_red(root->right));

    // push blackness down from grandparent (right child right parent)
    root = rb_tree_insert(root, 4);
    assert(rb_color_is_black(root->left));
    assert(rb_color_is_black(root->right));

    // delete red node
    root = rb_tree_delete(root, 4);
    assert(root->right->right == NULL);

    // delete black node (right)
    // this trigger case 3
    root = rb_tree_delete(root, 3);
    assert(root->right == NULL);
    assert(rb_color_is_red(root->left));

    // delete black node (root) with one red child
    root = rb_tree_delete(root, 2);
    assert(root->data == 1);
    assert(root->left == NULL);
    assert(root->right == NULL);

    // delete node is only root
    root = rb_tree_delete(root, 1);
    assert(root == NULL);

    // right rotation
    root = rb_tree_init(5);
    root = rb_tree_insert(root, 4);
    root = rb_tree_insert(root, 3);
    assert(root->data == 4);
    assert(rb_color_is_black(root));
    assert(root->left->data == 3);
    assert(rb_color_is_red(root->left));
    assert(root->right->data == 5);
    assert(rb_color_is_red(root->right));

    // push blackness down from grandparent (left child left parent)
    root = rb_tree_insert(root, 2);
    assert(rb_color_is_black(root->left));
    assert(rb_color_is_black(root->right));

    // delete black node (right)
    // this trigger case 6 (right_rotation)
    root = rb_tree_delete(root, 5);
    assert(root->data == 3);
    assert(root->left->data == 2);
    assert(root->right->data == 4);
    assert(rb_color_is_black(root->left));
    assert(rb_color_is_black(root->right));

    // delete black node (left)
    // this trigger case 3
    root = rb_tree_delete(root, 2);

    // delete black node with right red child
    root = rb_tree_delete(root, 3);
    assert(root->data == 4);
    root = rb_tree_delete(root, 4);

    // push blackness down from grandparent (left child right parent)
    root = rb_tree_init(10);
    root = rb_tree_insert(root, 20);
    root = rb_tree_insert(root, 30);
    root = rb_tree_insert(root, 25);
    assert(rb_color_is_black(root->left));
    assert(rb_color_is_black(root->right));

    // delete black node with left red child
    root = rb_tree_delete(root, 30);
    assert(root->right->data == 25);

    // delete black node (root)
    // trigger case 3
    root = rb_tree_delete(root, 20);
    assert(root->data == 10);
    assert(rb_color_is_red(root->right));

    // clean
    root = rb_tree_delete(root, 25);
    root = rb_tree_delete(root, 10);

    // push blackness down from grandparent (right child left parent)
    root = rb_tree_init(10);
    root = rb_tree_insert(root, 20);
    root = rb_tree_insert(root, 30);
    root = rb_tree_insert(root, 15);
    assert(rb_color_is_black(root->left));
    assert(rb_color_is_black(root->right));

    // delete black node(right)
    // trigger case 5 (left rotation) and case 6 (right rotation)
    root = rb_tree_delete(root, 30);
    assert(root->data == 15);
    assert(rb_color_is_black(root->left));
    assert(rb_color_is_black(root->right));

    // delete black node(right)
    // trigger case 5 (right rotation) and case 6 (left rotation)
    root = rb_tree_insert(root, 18);
    root = rb_tree_delete(root, 10);
    assert(root->data == 18);
    assert(rb_color_is_black(root->left));
    assert(rb_color_is_black(root->right));

    // left_right_rotation
    root = rb_tree_delete(root, 20);
    root = rb_tree_insert(root, 30);
    root = rb_tree_insert(root, 16);
    root = rb_tree_insert(root, 25);
    root = rb_tree_insert(root, 27);
    assert(root->right->data == 27);
    assert(root->right->left->data == 25);
    assert(root->right->right->data == 30);
    assert(rb_color_is_black(root->right));
    assert(rb_color_is_red(root->right->left));
    assert(rb_color_is_red(root->right->right));

    // delete node
    root = rb_tree_delete(root, 18);
    root = rb_tree_delete(root, 16);
    root = rb_tree_delete(root, 27);
    root = rb_tree_delete(root, 25);
    root = rb_tree_delete(root, 15);
    root = rb_tree_delete(root, 30);

    // right_left_rotation
    root = rb_tree_init(10);
    root = rb_tree_insert(root, 20);
    root = rb_tree_insert(root, 30);
    root = rb_tree_insert(root, 15);
    root = rb_tree_insert(root, 13);
    assert(root->left->data == 13);
    assert(root->left->left->data == 10);
    assert(root->left->right->data == 15);
    assert(rb_color_is_black(root->left));
    assert(rb_color_is_red(root->left->left));
    assert(rb_color_is_red(root->left->right));

    // delete black node
    // trigger case 2 (right rotation) and case 6 (right rotation)
    root = rb_tree_insert(root, 14);
    root = rb_tree_insert(root, 18);
    root = rb_tree_delete(root, 30);
    assert(rb_color_is_red(root->right));
    assert(rb_color_is_black(root->right->left));
    assert(rb_color_is_black(root->right->right));
    assert(root->right->data == 15);
    assert(root->right->left->data == 14);
    assert(root->right->right->data == 20);

    // delete black node
    // trigger case 2 (left rotation) and case 4
    root = rb_tree_delete(root, 10);
    assert(root->data == 15);
    assert(root->left->data == 13);
    assert(root->right->data == 20);
    assert(rb_color_is_black(root->left));
    assert(rb_color_is_black(root->right));

    // clean
    root = rb_tree_delete(root, 13);
    root = rb_tree_delete(root, 15);
    root = rb_tree_delete(root, 20);
    root = rb_tree_delete(root, 14);
    root = rb_tree_delete(root, 18);
    assert(root == NULL);
}