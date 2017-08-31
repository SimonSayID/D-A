//
// Created by simon on 17-8-31.
//

#include "../main.h"

void avl_tree_test() {

    // left rotation
    avl_node_t *root = avl_tree_init(0);
    root = avl_insert(root, 1);
    root = avl_insert(root, 2);
    assert(root->data == 1);
    assert(root->left->data == 0);
    assert(root->right->data == 2);

    // delete root (not trigger rotation)
    root = avl_delete(root, 1);
    assert(root->data == 0);
    root = avl_delete(root, 0);
    assert(root->data == 2);
    root = avl_delete(root, 2);
    assert(root == NULL);

    // right rotation
    root = avl_tree_init(2);
    root = avl_insert(root, 1);
    root = avl_insert(root, 0);
    assert(root->data == 1);
    assert(root->left->data == 0);
    assert(root->right->data == 2);

    // delete node with no child (not trigger rotation)
    root = avl_delete(root, 0);
    assert(root->left == NULL);
    root = avl_delete(root, 2);
    assert(root->right == NULL);
    root = avl_delete(root, 1);
    assert(root == NULL);

    // left_right_rotation
    root = avl_tree_init(30);
    root = avl_insert(root, 10);
    root = avl_insert(root, 20);
    assert(root->data == 20);
    assert(root->left->data == 10);
    assert(root->right->data == 30);

    // delete node with one child (not trigger rotation)
    root = avl_insert(root, 15);
    root = avl_insert(root, 25);
    root = avl_delete(root, 10); // with right child
    assert(root->left->data == 15);
    root = avl_delete(root, 30); // with left child
    assert(root->right->data == 25);

    // right_left_rotation
    root = avl_insert(root, 50);
    root = avl_insert(root, 40);
    assert(root->right->data == 40);
    assert(root->right->left->data == 25);
    assert(root->right->right->data == 50);

    // delete left child that can trigger left rotation
    root = avl_delete(root, 15);
    assert(root->data == 40);
    assert(root->left->data == 20);
    assert(root->right->data == 50);
    assert(root->left->right->data == 25);

    // delete left child that can trigger right_left rotation
    root = avl_insert(root, 45);
    root = avl_delete(root, 25);
    root = avl_delete(root, 20);
    assert(root->data == 45);
    assert(root->left->data == 40);
    assert(root->right->data == 50);

    // delete right child that can trigger right rotation
    root = avl_insert(root, 55);
    root = avl_delete(root, 40);
    assert(root->data == 50);
    assert(root->left->data == 45);
    assert(root->right->data == 55);

    // delete right child that can trigger left_right rotation
    root = avl_insert(root, 48);
    root = avl_delete(root, 55);
    assert(root->data == 48);
    assert(root->left->data == 45);
    assert(root->right->data == 50);

    // delete root that can trigger find left subtree maximum (does not trigger maximum parent rotation)
    root = avl_insert(root, 46);
    root = avl_delete(root, 48);
    assert(root->data == 46);
    assert(root->left->data == 45);
    assert(root->right->data == 50);

    // delete root that can trigger find left subtree maximum (trigger maximum parent right rotation)
    root = avl_delete(root, 45);
    root = avl_insert(root, 30);
    root = avl_insert(root, 55);
    root = avl_insert(root, 20);
    root = avl_insert(root, 35);
    root = avl_insert(root, 10);
    root = avl_delete(root, 46);
    assert(root->data == 35);
    assert(root->left->data == 20);
    assert(root->left->right->data == 30);
    assert(root->left->left->data == 10);

}
