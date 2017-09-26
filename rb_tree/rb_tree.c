//
// Created by simon on 17-8-29.
//

#include "rb_tree.h"

static void rb_left_rotation(rb_node_t **root, rb_node_t *sentinel, rb_node_t *node) {

    rb_node_t *temp = node->right;
    node->right = temp->left;
    if (temp->left != sentinel) {
        temp->left->parent = node;
    }

    temp->parent = node->parent;

    if (node == *root) {
        *root = temp;
    } else if (node == node->parent->left) {
        node->parent->left = temp;
    } else {
        node->parent->right = temp;
    }

    temp->left = node;
    node->parent = temp;
}

static void rb_right_rotation(rb_node_t **root, rb_node_t *sentinel, rb_node_t *node) {

    rb_node_t *temp = node->left;
    node->left = temp->right;
    if (temp->right != sentinel) {
        temp->right->parent = node;
    }

    temp->parent = node->parent;

    if (node == *root) {
        *root = temp;
    } else if (node == node->parent->left) {
        node->parent->left = temp;
    } else {
        node->parent->right = temp;
    }

    temp->right = node;
    node->parent = temp;
}

rb_tree_t *rb_tree_init() {
    rb_tree_t *tree = (rb_tree_t *) malloc(sizeof(rb_tree_t));
    rb_node_t *sentinel = (rb_node_t *) malloc(sizeof(rb_node_t));
    sentinel->color = 0;
    tree->root = sentinel;
    tree->sentinel = sentinel;
    return tree;
}

void rb_tree_insert(rb_tree_t *tree, int data) {

    if (tree != NULL) {

        rb_node_t *sentinel = tree->sentinel;
        rb_node_t **root = &tree->root;
        rb_node_t **pos = NULL;
        rb_node_t *temp = tree->root;

        rb_node_t *new = (rb_node_t *)malloc(sizeof(rb_node_t));
        new->data = data;
        new->color = 1;
        new->left = new->right = sentinel;

        if (*root == sentinel) {
            new->parent = NULL;
            rb_color_black(new);
            *root = new;
            return ;
        }

        int exist = 1;
        while ( temp->data != data) {
            pos = (temp->data > data) ? &temp->left : &temp->right;
            if (*pos == sentinel) {
                exist = 0;
                *pos = new;
                break;
            }
            temp = *pos;
        }
        new->parent = temp;
        if (exist == 1) {
            free(new);
            return;
        }

        while (new != *root && rb_color_is_red(new->parent)) {

            if (new->parent == new->parent->parent->left) {
                temp = new->parent->parent->right;

                if (rb_color_is_red(temp)) {
                    rb_color_black(new->parent);
                    rb_color_black(temp);
                    rb_color_red(new->parent->parent);

                    new = new->parent->parent;
                } else {

                    if (new == new->parent->right) {
                        new = new->parent;
                        rb_left_rotation(root, sentinel, new);
                    }

                    rb_color_black(new->parent);
                    rb_color_red(new->parent->parent);
                    rb_right_rotation(root, sentinel, new->parent->parent);
                }

            } else {
                temp = new->parent->parent->left;

                if (rb_color_is_red(temp)) {
                    rb_color_black(new->parent);
                    rb_color_black(temp);
                    rb_color_red(new->parent->parent);

                    new = new->parent->parent;
                } else {

                    if (new == new->parent->left) {
                        new = new->parent;
                        rb_right_rotation(root, sentinel, new);
                    }

                    rb_color_black(new->parent);
                    rb_color_red(new->parent->parent);
                    rb_left_rotation(root, sentinel, new->parent->parent);
                }
            }

        }

        rb_color_black(*root);
    }
}

void rb_tree_delete(rb_tree_t *tree, int data) {
    if (tree != NULL) {
        rb_node_t **root = &tree->root;
        rb_node_t *sentinel = tree->sentinel;
        rb_node_t *pos = tree->root;
        rb_node_t *temp;
        rb_node_t *subst;
        rb_node_t *c;
        int red;

        while (pos != sentinel && pos->data != data) {
            pos = (pos->data > data) ? pos->left : pos->right;
        }
        if (pos == sentinel) {
            return ;
        }

        if (pos->left == sentinel) {
            temp = pos->right;
            subst = pos;
        } else if (pos->right == sentinel) {
            temp = pos->left;
            subst = pos;
        } else {
            subst = pos->right;
            while (subst->left != sentinel) {
                subst = subst->left;
            }
            if (subst->left != sentinel) {
                temp = subst->left;
            } else {
                temp = subst->right;
            }
        }

        if (subst == *root) {
            *root = temp;
            rb_color_black(temp);
            free(pos);
            return;
        }

        red = rb_color_is_red(subst);

        if (subst == subst->parent->left) {
            subst->parent->left = temp;
        } else {
            subst->parent->right = temp;
        }

        if (subst == pos) {
            temp->parent = subst->parent;
        } else {

            if (subst->parent == pos) {
                temp->parent = subst;
            } else {
                temp->parent = subst->parent;
            }

            subst->left = pos->left;
            subst->right = pos->right;
            subst->parent = pos->parent;
            rb_color_copy(subst, pos);

            if (pos == *root) {
                *root = subst;
            } else {
                if (pos == pos->parent->left) {
                    pos->parent->left = subst;
                } else {
                    pos->parent->right = subst;
                }
            }

            if (subst->left != sentinel) {
                subst->left->parent = subst;
            }

            if (subst->right != sentinel) {
                subst->right->parent = subst;
            }
        }

        free(pos);

        if (red == 1) {
            return;
        }

        while (temp != *root && rb_color_is_red(temp)) {

            if (temp == temp->parent->left) {
                c = temp->parent->right;

                if (rb_color_is_red(c)) {
                    rb_color_black(c);
                    rb_color_red(temp->parent);
                    rb_left_rotation(root, sentinel, temp->parent);
                    c = temp->parent->right;
                }

                if (rb_color_is_black(c->left) && rb_color_is_black(c->right)) {
                    rb_color_red(c);
                    temp = temp->parent;
                } else {
                    if (rb_color_is_black(c->right)) {
                        rb_color_black(c->left);
                        rb_color_red(c);
                        rb_right_rotation(root, sentinel, c);
                        c = temp->parent->right;
                    }

                    rb_color_copy(c, temp->parent);
                    rb_color_black(temp->parent);
                    rb_color_black(c->right);
                    rb_left_rotation(root, sentinel, temp->parent);
                    temp = *root;
                }

            } else {
                c = temp->parent->left;

                if (rb_color_is_red(c)) {
                    rb_color_black(c);
                    rb_color_red(temp->parent);
                    rb_right_rotation(root, sentinel, temp->parent);
                    c = temp->parent->left;
                }

                if (rb_color_is_black(c->left) && rb_color_is_black(c->right)) {
                    rb_color_red(c);
                    temp = temp->parent;
                } else {
                    if (rb_color_is_black(c->left)) {
                        rb_color_black(c->right);
                        rb_color_red(c);
                        rb_left_rotation(root, sentinel, c);
                        c = temp->parent->left;
                    }

                    rb_color_copy(c, temp->parent);
                    rb_color_black(temp->parent);
                    rb_color_black(c->left);
                    rb_right_rotation(root, sentinel, temp->parent);
                    temp = *root;
                }
            }
        }

        rb_color_black(temp);
    }
}

rb_node_t *rb_tree_search(rb_tree_t *tree, int data) {
    rb_node_t *node = tree->root;
    while (node != NULL && node->data != data) {
        if (node->data > data) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return node;
}