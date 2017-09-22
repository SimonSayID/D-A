//
// Created by simon on 8/27/17.
//

#ifndef ALG_AVL_TREE_H
#define ALG_AVL_TREE_H

#include "../main.h"

typedef struct avl_node_s               avl_node_t;

struct avl_node_s {
    avl_node_t    *left;
    avl_node_t    *right;
    avl_node_t    *parent;
    int           data;
    int           height;
};

avl_node_t* avl_tree_init(int data);

avl_node_t* avl_insert(avl_node_t *node, int data);

avl_node_t* avl_delete(avl_node_t *node, int data);

avl_node_t* avl_search(avl_node_t *node, int data);

#endif //ALG_AVL_TREE_H
