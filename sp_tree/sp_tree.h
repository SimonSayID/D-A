//
// Created by Simon on 2017/9/27.
//

#ifndef D_A_SP_TREE_H
#define D_A_SP_TREE_H

#include "../main.h"

typedef struct sp_node_s sp_node_t;

struct sp_node_s {
    sp_node_t       *left;
    sp_node_t       *right;
    sp_node_t       *parent;
    int             data;
};

sp_node_t* sp_tree_init(int data);

sp_node_t* sp_insert(sp_node_t* node, int data);

sp_node_t* sp_delete(sp_node_t* node, int data);

sp_node_t* sp_search(sp_node_t* node, int data);

#endif //D_A_SP_TREE_H
