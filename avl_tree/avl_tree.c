//
// Created by simon on 8/27/17.
//

#include "avl_tree.h"

static int avl_height(avl_node_t *node){
    if (node != NULL) {
        return node->height;
    }
    return -1;
}

static avl_node_t* avl_left_rotation(avl_node_t *node){
    node->right->parent = node->parent;
    avl_node_t *temp = node->right;

    if (temp->left != NULL) {
        temp->left->parent = node;
    }
    node->right = temp->left;

    node->parent = temp;
    temp->left = node;

    node->height = max(avl_height(node->left), avl_height(node->right)) + 1;
    temp->height = max(avl_height(temp->right), node->height) + 1;

    return temp;
}

static avl_node_t* avl_right_rotation(avl_node_t *node){
    node->left->parent = node->parent;
    avl_node_t *temp = node->left;

    if (temp->right != NULL) {
        temp->right->parent = node;
    }
    node->left = temp->right;

    node->parent = temp;
    temp->right = node;

    node->height = max(avl_height(node->left), avl_height(node->right)) + 1;
    temp->height = max(avl_height(temp->left), node->height) + 1;

    return temp;
}

static avl_node_t* avl_left_right_rotation(avl_node_t *node){
    node->left = avl_left_rotation(node->left);
    return avl_right_rotation(node);
}

static avl_node_t* avl_right_left_rotation(avl_node_t *node){
    node->right = avl_right_rotation(node->right);
    return avl_left_rotation(node);
}

static avl_node_t* avl_re_balance(avl_node_t *node) {

    node->height = max(avl_height(node->left), avl_height(node->right)) + 1;

    if (avl_height(node->left) - avl_height(node->right) == 2) {
        if (avl_height(node->left->right) - avl_height(node->left->left) == 1) {
            node = avl_left_right_rotation(node);
        } else {
            node = avl_right_rotation(node);
        }
    } else if (avl_height(node->right) - avl_height(node->left) == 2) {
        if (avl_height(node->right->left) - avl_height(node->right->right) == 1) {
            node = avl_right_left_rotation(node);
        } else {
            node = avl_left_rotation(node);
        }
    }

    return node;
}

avl_node_t* avl_tree_init(int data) {
    avl_node_t* root = (avl_node_t *)malloc(sizeof(avl_node_t));
    root->data = data;
    root->parent = root->left = root->right = NULL;
    root->height = 0;
    return root;
}

avl_node_t* avl_insert(avl_node_t *node, int data){
    if (node != NULL) {

        avl_node_t *new = (avl_node_t *)malloc(sizeof(avl_node_t));
        new->data = data;
        new->parent = new->left = new->right = NULL;
        new->height = 0;

        while (node->data != data) {
            new->parent = node;
            if (node->data > data) {
                if (node->left == NULL) {
                    node->left = new;
                    break;
                }
                node = node->left;
            } else {
                if (node->right == NULL) {
                    node->right = new;
                    break;
                }
                node = node->right;
            }
        }
        if (node->data == data) {
            free(new);
            goto end;
        }

        node = new;

        while (node != NULL) {

            avl_node_t *save = node;

            node = avl_re_balance(node);

            avl_node_t *p = node->parent;
            if (p != NULL) {
                if (p->left == save) {
                    p->left = node;
                } else {
                    p->right = node;
                }
            } else {
                goto end;
            }

            node = node->parent;
        }

        end:
            return node;
    }
    return NULL;
}

avl_node_t* avl_delete(avl_node_t *node, int data){
    if (node != NULL) {

        avl_node_t *del = node;
        avl_node_t *reb = NULL;

        while (del != NULL && del->data != data) {
            if (del->data > data) {
                del = del->left;
            } else {
                del = del->right;
            }
        }

        if (del != NULL) {

            if (del->left != NULL && del->right != NULL) {
                avl_node_t *predecessor = del->left;
                while (predecessor->right != NULL) {
                    predecessor = predecessor->right;
                }

                del->data = predecessor->data;

                if (predecessor->parent->right == predecessor) {
                    predecessor->parent->right = predecessor->left;
                } else {
                    predecessor->parent->left = predecessor->left;
                }

                reb = predecessor->parent;
                del = predecessor;

            } else if (del->left == NULL && del->right == NULL) {

                if (del->parent != NULL) {
                    if (del->parent->left == del) {
                        del->parent->left = NULL;
                    } else {
                        del->parent->right = NULL;
                    }
                } else {
                    node = NULL;
                }
                reb = del->parent;

            } else {

                if (del->parent != NULL) {
                    if (del->parent->left == del) {
                        del->parent->left = del->left != NULL ? del->left : del->right;
                        reb = del->parent->left;
                    } else {
                        del->parent->right = del->left != NULL ? del->left : del->right;
                        reb = del->parent->right;
                    }
                } else {
                    node = del->left != NULL ? del->left : del->right;
                    node->parent = NULL;
                }

                if (reb != NULL) {
                    reb->parent = del->parent;
                }

            }

            free(del);

            while (reb != NULL) {

                avl_node_t *save = reb;

                reb = avl_re_balance(reb);

                avl_node_t *p = reb->parent;
                if (p != NULL) {
                    if (p->left == save) {
                        p->left = reb;
                    } else {
                        p->right = reb;
                    }
                } else {
                    node = reb;
                    goto end;
                }
                reb = reb->parent;
            }

        }
    end:
        return node;
    }
}

avl_node_t* avl_search(avl_node_t *node, int data){
    while (node != NULL && node->data != data){
        if (node->data > data) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return node;
}