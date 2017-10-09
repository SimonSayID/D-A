//
// Created by simon on 17-8-31.
//

#include "avl_tree.h"

void avl_tree_test() {

    // left rotation
    avl_tree_t *tree = avl_tree_init();
    avl_insert(tree, 0);
    avl_insert(tree, 1);
    avl_insert(tree, 2);
    avl_node_t *root = tree->root;
    assert(root->data == 1);
    assert(root->left->data == 0);
    assert(root->right->data == 2);

    // delete root (not trigger rotation)
    avl_delete(tree, 1);
    root = tree->root;
    assert(root->data == 0);
    avl_delete(tree, 0);
    root = tree->root;
    assert(root->data == 2);
    avl_delete(tree, 2);
    root = tree->root;
    assert(root == NULL);

    // right rotation
    avl_insert(tree, 2);
    avl_insert(tree, 1);
    avl_insert(tree, 0);
    root = tree->root;
    assert(root->data == 1);
    assert(root->left->data == 0);
    assert(root->right->data == 2);

    // delete node with no child (not trigger rotation)
    avl_delete(tree, 0);
    root = tree->root;
    assert(root->left == NULL);
    avl_delete(tree, 2);
    root = tree->root;
    assert(root->right == NULL);
    avl_delete(tree, 1);
    root = tree->root;
    assert(root == NULL);

    // left_right_rotation
    avl_insert(tree, 30);
    avl_insert(tree, 10);
    avl_insert(tree, 20);
    root = tree->root;
    assert(root->data == 20);
    assert(root->left->data == 10);
    assert(root->right->data == 30);

    // delete node with one child (not trigger rotation)
    avl_insert(tree, 15);
    avl_insert(tree, 25);
    avl_delete(tree, 10); // with right child
    root = tree->root;
    assert(root->left->data == 15);
    avl_delete(tree, 30); // with left child
    root = tree->root;
    assert(root->right->data == 25);

    // right_left_rotation
    avl_insert(tree, 50);
    avl_insert(tree, 40);
    root = tree->root;
    assert(root->right->data == 40);
    assert(root->right->left->data == 25);
    assert(root->right->right->data == 50);

    // delete left child that can trigger left rotation
    avl_delete(tree, 15);
    root = tree->root;
    assert(root->data == 40);
    assert(root->left->data == 20);
    assert(root->right->data == 50);
    assert(root->left->right->data == 25);

    // delete left child that can trigger right_left rotation
    avl_insert(tree, 45);
    avl_delete(tree, 25);
    avl_delete(tree, 20);
    root = tree->root;
    assert(root->data == 45);
    assert(root->left->data == 40);
    assert(root->right->data == 50);

    // delete right child that can trigger right rotation
    avl_insert(tree, 55);
    avl_delete(tree, 40);
    root = tree->root;
    assert(root->data == 50);
    assert(root->left->data == 45);
    assert(root->right->data == 55);

    // delete right child that can trigger left_right rotation
    avl_insert(tree, 48);
    avl_delete(tree, 55);
    root = tree->root;
    assert(root->data == 48);
    assert(root->left->data == 45);
    assert(root->right->data == 50);

    // delete root that can trigger find left subtree maximum (does not trigger maximum parent rotation)
    avl_insert(tree, 46);
    avl_delete(tree, 48);
    root = tree->root;
    assert(root->data == 46);
    assert(root->left->data == 45);
    assert(root->right->data == 50);

    // delete root that can trigger find left subtree maximum (trigger maximum parent right rotation)
    avl_delete(tree, 45);
    avl_insert(tree, 30);
    avl_insert(tree, 55);
    avl_insert(tree, 20);
    avl_insert(tree, 35);
    avl_insert(tree, 10);
    avl_delete(tree, 46);
    root = tree->root;
    assert(root->data == 35);
    assert(root->left->data == 20);
    assert(root->left->right->data == 30);
    assert(root->left->left->data == 10);

    // delete root that can trigger find left subtree maximum (trigger maximum parent right_left rotation)
    avl_insert(tree, 15);
    avl_delete(tree, 35);
    root = tree->root;
    assert(root->data == 30);
    assert(root->left->data == 15);
    assert(root->left->left->data == 10);
    assert(root->left->right->data == 20);

    //free the memory
    avl_delete(tree, 30);
    avl_delete(tree, 15);
    avl_delete(tree, 10);
    avl_delete(tree, 20);
    avl_delete(tree, 50);
    avl_delete(tree, 55);
    root = tree->root;
    assert(root == NULL);
    free(tree);
}
