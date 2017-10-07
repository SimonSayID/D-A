//
// Created by Simon on 2017/9/27.
//

#ifndef D_A_SP_TREE_H
#define D_A_SP_TREE_H

#include "../main.h"

typedef struct sp_node_s sp_node_t;
typedef struct sp_tree_s sp_tree_t;

struct sp_node_s {
    sp_node_t       *left;
    sp_node_t       *right;
    sp_node_t       *parent;
    int             data;
};

struct sp_tree_s {
    sp_node_t *root;
};

sp_tree_t* sp_tree_init();

void sp_insert(sp_tree_t* tree, int data);

void sp_delete(sp_tree_t* tree, int data);

sp_node_t* sp_search(sp_tree_t* tree, int data);

#endif //D_A_SP_TREE_H
