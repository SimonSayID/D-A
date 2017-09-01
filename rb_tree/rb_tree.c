//
// Created by simon on 17-8-29.
//

#include "../main.h"

static rb_node_t *rb_left_rotation(rb_node_t *node) {

    node->color = 1;

    rb_node_t *temp = node->right;
    node->right = temp->left;
    temp->left = node;

    temp->parent = node->parent;
    node->parent = temp;

    temp->color = 0;

    return temp;
}

static rb_node_t *rb_right_rotation(rb_node_t *node) {

    node->color = 1;

    rb_node_t *temp = node->left;
    node->left = temp->right;
    temp->right = node;

    temp->parent = node->parent;
    node->parent = temp;

    temp->color = 0;

    return temp;
}

static rb_node_t *rb_left_right_rotation(rb_node_t *node) {
    node->left = rb_left_rotation(node->left);
    return rb_right_rotation(node);
}

static rb_node_t *rb_right_left_rotation(rb_node_t *node) {
    node->right = rb_right_rotation(node->right);
    return rb_left_rotation(node);
}

rb_node_t *rb_tree_init(int data) {
    rb_node_t *root = (rb_node_t *) malloc(sizeof(rb_node_t));
    root->data = data;
    root->color = 0;
    root->left = root->right = root->parent = NULL;
    return root;
}

rb_node_t *rb_tree_insert(rb_node_t *node, int data) {
    if (node != NULL) {

        rb_node_t *new = (rb_node_t *) malloc(sizeof(rb_node_t));
        new->data = data;
        new->color = 1;
        new->left = new->right = new->parent = NULL;

        rb_node_t *temp = node;

        do {
            new->parent = temp;
            if (temp->data > data) {
                if (temp->left == NULL) {
                    temp->left = new;
                    break;
                }
                temp = temp->left;
            } else if (temp->data < data) {
                if (temp->right == NULL) {
                    temp->right = new;
                    break;
                }
                temp = temp->right;
            }
        } while (temp->data != data);

        if (temp->data == data) {
            return NULL;
        }

        while (new != NULL) {
            if (new->parent != NULL) {
                if (rb_is_red(new) && rb_is_red(new->parent)) {
                    rb_node_t *grandparent = new->parent->parent;
                    rb_node_t *save = grandparent;
                    if (grandparent != NULL) {
                        int parent_direction = 0;
                        int node_direction = 0;
                        if (grandparent->left == new->parent) {
                            parent_direction = 1;
                        }
                        if (new->parent->left == new) {
                            node_direction = 1;
                        }
                        //grandparent's parent is left child
                        if (parent_direction) {
                            if (grandparent->right != NULL && rb_is_red(grandparent->right)) {
                                rb_color_black(new->parent);
                                rb_color_black(grandparent->right);
                                rb_color_red(grandparent);
                            } else {
                                if (node_direction) {
                                    grandparent = rb_right_rotation(grandparent);
                                } else {
                                    grandparent = rb_left_right_rotation(grandparent);
                                }
                            }
                            new = grandparent->left;
                        }
                            //grandparent's parent is right child
                        else {
                            if (grandparent->left != NULL && rb_is_red(grandparent->left)) {
                                rb_color_black(grandparent->right);
                                rb_color_black(grandparent->left);
                                rb_color_red(grandparent);
                            } else {
                                if (node_direction) {
                                    grandparent = rb_right_left_rotation(grandparent);
                                } else {
                                    grandparent = rb_left_rotation(grandparent);
                                }
                            }
                            new = grandparent->right;
                        }
                        if (grandparent->parent != NULL) {
                            if (grandparent->parent->left == save) {
                                grandparent->parent->left = grandparent;
                            } else {
                                grandparent->parent->right = grandparent;
                            }
                        }
                    }
                }
            } else {
                node = new;
            }
            new = new->parent;
        }

        node->color = 0;
    }
    return node;
}

