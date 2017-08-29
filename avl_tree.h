//
// Created by simon on 8/27/17.
//

#ifndef ALG_AVL_TREE_H
#define ALG_AVL_TREE_H

#include "main.h"

struct avl_node_s {
    int           data;
    int           height;
    avl_node_t    *left;
    avl_node_t    *right;
};

static int avl_height(avl_node_t *node);

static avl_node_t* left_rotation(avl_node_t *node);

static avl_node_t* right_rotation(avl_node_t *node);

static avl_node_t* left_right_rotation(avl_node_t *node);

static avl_node_t* right_left_rotation(avl_node_t *node);

avl_node_t* avl_tree_init(int data);

avl_node_t* avl_insert(avl_node_t *node, int data);

avl_node_t* avl_delete(avl_node_t *node, int data);

avl_node_t* avl_search(avl_node_t *node, int data);

void avl_tree_test();

#endif //ALG_AVL_TREE_H
