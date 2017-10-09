//
// Created by simon on 17-8-29.
//

#ifndef D_A_RB_TREE_H
#define D_A_RB_TREE_H

#include "../../main.h"

typedef struct rb_node_s                rb_node_t;

/*
 * color:
 * 0 is black, 1 is red
 * */

struct rb_node_s {
    rb_node_t *parent;
    rb_node_t *left;
    rb_node_t *right;
    int data;
    int color;
};

#define rb_color_red(node)              ((node)->color = 1)
#define rb_color_black(node)            ((node)->color = 0)
#define rb_color_is_red(node)           ((node)->color)
#define rb_color_is_black(node)         (!rb_color_is_red(node))

rb_node_t *rb_tree_init(int data);

rb_node_t *rb_tree_insert(rb_node_t *node, int data);

rb_node_t *rb_tree_delete(rb_node_t *node, int data);

rb_node_t *rb_tree_search(rb_node_t *node, int data);

#endif //D_A_RB_TREE_H
