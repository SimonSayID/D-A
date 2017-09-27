//
// Created by simon on 17-8-29.
//

#include "rb_tree.h"


static rb_node_t *rb_left_rotation(rb_node_t *node) {

    node->color = 1;

    rb_node_t *temp = node->right;
    if (temp->left != NULL) {
        temp->left->parent = node;
    }
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
    if (temp->right != NULL) {
        temp->right->parent = node;
    }
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

static int is_nephews_both_black(rb_node_t *node) {
    if (node != NULL) {
        if (node->left == NULL && node->right == NULL) {
            return 1;
        }
        if (node->left != NULL && node->right != NULL) {
            if (rb_color_is_black(node->left) && rb_color_is_black(node->right)) {
                return 1;
            }
        }
    }
    return 0;
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

        int exist = 1;
        rb_node_t **pos = NULL;
        while (temp->data != data) {
            new->parent = temp;
            pos = (temp->data > data) ? &temp->left : &temp->right;
            if (*pos == NULL) {
                exist = 0;
                *pos = new;
                break;
            }
            temp = *pos;
        }
        if (exist == 1) {
            free(new);
            return NULL;
        }

        while (new != NULL) {
            if (new->parent != NULL) {
                if (rb_color_is_red(new) && rb_color_is_red(new->parent)) {
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
                            if (grandparent->right != NULL && rb_color_is_red(grandparent->right)) {
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
                            if (grandparent->left != NULL && rb_color_is_red(grandparent->left)) {
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

rb_node_t *rb_tree_delete(rb_node_t *node, int data) {
    if (node != NULL) {
        rb_node_t *temp = node;
        while (temp != NULL && temp->data != data) {
            if (temp->data > data) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }

        if (temp != NULL) {

            // check the delete node is root first,
            // if it is, find the successor in the left subtree
            if (temp->left != NULL && temp->right != NULL) {
                rb_node_t *suc = temp->left;
                while (suc->right != NULL) {
                    suc = suc->right;
                }
                temp->data = suc->data;
                temp = suc;
            }

            // delete node is red and not child
            if (temp->right == NULL && temp->left == NULL
                && rb_color_is_red(temp)) {
                if (temp->parent->left == temp) {
                    temp->parent->left = NULL;
                } else {
                    temp->parent->right = NULL;
                }
                free(temp);
                goto end;
            }

            // delete node with one child
            // (definitely is black node with red child if the tree is red black tree)
            if (temp->left != NULL || temp->right != NULL) {
                rb_node_t *child = temp->left != NULL ? temp->left : temp->right;
                rb_color_black(child);
                if (temp->parent != NULL) {
                    if (temp->parent->left == temp) {
                        temp->parent->left = child;
                    } else {
                        temp->parent->right = child;
                    }
                } else {
                    node = child;
                }
                child->parent = temp->parent;
                free(temp);
                goto end;
            }

            // delete node is black with no child

            if (temp == node) {
                free(temp);
                node = NULL;
                goto end;
            }

            // create double black node
            rb_node_t *dbn = malloc(sizeof(rb_node_t));
            dbn->color = 2;

            if (temp->parent->left == temp) {
                temp->parent->left = dbn;
            } else {
                temp->parent->right = dbn;
            }
            dbn->parent = temp->parent;

            free(temp);

            while (dbn != NULL && dbn->color == 2) {

                // case 1
                if (dbn == node) {
                    goto end;
                }

                // case 2
                rb_node_t *sibling = dbn->parent->left == dbn ? dbn->parent->right : dbn->parent->left;
                if (rb_color_is_black(dbn->parent) && rb_color_is_red(sibling)
                    && is_nephews_both_black(sibling)) {
                    if (dbn->parent->left == dbn) {
                        dbn->parent = rb_left_rotation(dbn->parent);
                        if (dbn->parent->parent == NULL) {
                            node = dbn->parent;
                        }
                        dbn->parent = dbn->parent->left;
                    } else {
                        dbn->parent = rb_right_rotation(dbn->parent);
                        if (dbn->parent->parent == NULL) {
                            node = dbn->parent;
                        }
                        dbn->parent = dbn->parent->right;
                    }
                }

                // case 3
                sibling = dbn->parent->left == dbn ? dbn->parent->right : dbn->parent->left;
                if (rb_color_is_black(dbn->parent) && rb_color_is_black(sibling) && is_nephews_both_black(sibling)) {
                    if (rb_color_is_red(dbn->parent)) {
                        rb_color_black(dbn->parent);
                    } else {
                        dbn->parent->color = 2;
                    }
                    rb_color_red(sibling);
                    if (dbn->parent->left == dbn) {
                        dbn->parent->left = NULL;
                    } else {
                        dbn->parent->right = NULL;
                    }
                }

                // case 4
                sibling = dbn->parent->left == dbn ? dbn->parent->right : dbn->parent->left;
                if (sibling != NULL) {
                    if (rb_color_is_red(dbn->parent) && rb_color_is_black(sibling)
                        && is_nephews_both_black(sibling)) {
                        rb_color_red(sibling);
                        rb_color_black(dbn->parent);
                        if (dbn->parent->left == dbn) {
                            dbn->parent->left = NULL;
                        } else {
                            dbn->parent->right = NULL;
                        }
                        free(dbn);
                        goto end;
                    }
                }

                // case 5
                sibling = dbn->parent->left == dbn ? dbn->parent->right : dbn->parent->left;
                if (sibling != NULL) {
                    if (rb_color_is_black(sibling)) {
                        if (dbn->parent->left == dbn
                            && sibling->left != NULL && rb_color_is_red(sibling->left)
                            && (sibling->right == NULL || rb_color_is_black(sibling->right))) {

                            dbn->parent->right = rb_right_rotation(dbn->parent->right);

                        } else if (dbn->parent->right == dbn
                                   && sibling->right != NULL && rb_color_is_red(sibling->right)
                                   && (sibling->left == NULL || rb_color_is_black(sibling->left))) {

                            dbn->parent->left = rb_left_rotation(dbn->parent->left);

                        }
                    }
                }

                // case 6
                sibling = dbn->parent->left == dbn ? dbn->parent->right : dbn->parent->left;
                if (sibling != NULL) {
                    if (rb_color_is_black(sibling)) {
                        if (dbn->parent->left == dbn
                            && sibling->right != NULL && rb_color_is_red(sibling->right)) {

                            dbn->parent = rb_left_rotation(dbn->parent);
                            dbn->parent->left->left = NULL;
                            if (dbn->parent->parent != NULL) {
                                if (dbn->parent->parent->left == dbn->parent) {
                                    dbn->parent->parent->left = dbn->parent;
                                } else {
                                    dbn->parent->parent->right = dbn->parent;
                                }
                            } else {
                                node = dbn->parent;
                            }

                        } else if (dbn->parent->right == dbn
                                   && sibling->left != NULL && rb_color_is_red(sibling->left)) {

                            dbn->parent = rb_right_rotation(dbn->parent);
                            dbn->parent->right->right = NULL;
                            if (dbn->parent->parent != NULL) {
                                if (dbn->parent->parent->left == dbn->parent) {
                                    dbn->parent->parent->left = dbn->parent;
                                } else {
                                    dbn->parent->parent->right = dbn->parent;
                                }
                            } else {
                                node = dbn->parent;
                            }

                        }

                        rb_color_red(dbn->parent);
                        rb_color_black(dbn->parent->left);
                        rb_color_black(dbn->parent->right);
                        free(dbn);
                        goto end;
                    }
                }

                rb_node_t *save = dbn->parent;
                free(dbn);
                dbn = save;
            }

        }
    }

    end:
    if (node != NULL) {
        rb_color_black(node);
        node->parent = NULL;
    }
    return node;
}

rb_node_t *rb_tree_search(rb_node_t *node, int data) {
    while (node != NULL && node->data != data) {
        if (node->data > data) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return node;
}