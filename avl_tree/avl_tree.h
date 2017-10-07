//
// Created by simon on 8/27/17.
//

#ifndef ALG_AVL_TREE_H
#define ALG_AVL_TREE_H

#include "../main.h"

typedef struct avl_node_s avl_node_t;
typedef struct avl_tree_s avl_tree_t;

struct avl_node_s {
    avl_node_t *left;
    avl_node_t *right;
    avl_node_t *parent;
    int data;
    int height;
};

struct avl_tree_s {
    avl_node_t *root;
};

avl_tree_t* avl_tree_init();

void avl_insert(avl_tree_t *tree, int data);

void avl_delete(avl_tree_t *tree, int data);

avl_node_t* avl_search(avl_tree_t *tree, int data);

#endif //ALG_AVL_TREE_H
