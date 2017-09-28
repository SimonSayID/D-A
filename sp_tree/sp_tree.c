//
// Created by Simon on 2017/9/27.
//

#include "sp_tree.h"

static void sp_zig_left(sp_node_t *node) {
    sp_node_t *save = node->parent;

    sp_node_t *temp = node->left;
    if (temp != NULL) {
        temp->parent = node->parent;
    }
    node->parent->right = temp;
    node->left = node->parent;
    node->parent = node->parent->parent;
    node->left->parent = node;

    if (node->parent != NULL) {
        if (node->parent->left == save) {
            node->parent->left = node;
        } else {
            node->parent->right = node;
        }
    }
}

static void sp_zig_right(sp_node_t *node) {
    sp_node_t *save = node->parent;

    sp_node_t *temp = node->right;
    if (temp != NULL) {
        temp->parent = node->parent;
    }
    node->parent->left = temp;
    node->right = node->parent;
    node->parent = node->parent->parent;
    node->right->parent = node;

    if (node->parent != NULL) {
        if (node->parent->left == save) {
            node->parent->left = node;
        } else {
            node->parent->right = node;
        }
    }
}

static sp_node_t* sp_splay(sp_node_t *node) {
    sp_node_t *pos = node;
    while (pos->parent != NULL) {
        sp_node_t *g = node->parent->parent;
        sp_node_t *p = node->parent;
        if (g != NULL) {
            if (p == g->left) {
                if (pos == p->left) {
                    // zig-zig right
                    sp_zig_right(p);
                    sp_zig_right(p->left);
                } else {
                    // zig-zag-right
                    sp_zig_left(pos);
                    sp_zig_right(pos);
                }
            } else {
                if (pos == p->right) {
                    // zig-zig-left
                    sp_zig_left(p);
                    sp_zig_left(p->right);
                } else {
                    // zig-zag-left
                    sp_zig_right(pos);
                    sp_zig_left(pos);
                }
            }
        } else {
            if (pos == pos->parent->left) {
                sp_zig_right(pos);
            } else {
                sp_zig_left(pos);
            }
        }
    }
    return node;
}

sp_node_t* sp_tree_init(int data) {
    sp_node_t *root = (sp_node_t *)malloc(sizeof(sp_node_t));
    root->data = data;
    root->parent = root->left = root->right = NULL;
    return root;
}

sp_node_t* sp_insert(sp_node_t* node, int data) {
    if (node != NULL) {

        sp_node_t *new = (sp_node_t *)malloc(sizeof(sp_node_t));
        new->data = data;
        new->left = new->right = NULL;

        sp_node_t **pos = NULL;
        int exist = 1;
        while (node->data != data) {
            pos = (node->data > data) ? &node->left : &node->right;
            if (*pos == NULL) {
                exist = 0;
                *pos = new;
                break;
            }
            node = *pos;
        }
        new->parent = node;
        if (exist == 1) {
            free(new);
            return NULL;
        }

        node = sp_splay(new);

        return node;
    }
}

sp_node_t* sp_delete(sp_node_t* node, int data) {
    if (node != NULL) {
        sp_node_t *temp = node;
        while (temp != NULL && temp->data != data) {
            if (temp->data > data) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }

        if (temp != NULL) {
            temp = sp_splay(temp);
            sp_node_t *ls = temp->left;
            sp_node_t *rs = temp->right;
            free(temp);
            if (ls != NULL) {
                ls->parent = NULL;
                if (ls->right != NULL && rs != NULL) {
                    while (ls->right != NULL) {
                        ls = ls->right;
                    }
                    ls = sp_splay(ls);
                }
                if (rs != NULL) {
                    ls->right = rs;
                }
                node = ls;
            } else {
                node = rs;
            }
            if (rs != NULL) {
                rs->parent = ls;
            }
        }

        return node;
    }
}

sp_node_t* sp_search(sp_node_t* node, int data) {
    if (node != NULL) {
        sp_node_t **pos;
        while (node != NULL && node->data != data) {
            pos = (node->data > data) ? &node->left : &node->right;
            node = *pos;
        }
        if (node != NULL) {
            sp_splay(node);
        }
        return node;
    }
}