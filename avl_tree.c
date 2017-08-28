//
// Created by simon on 8/27/17.
//

#include "main.h"

static int avl_height(avl_node_t *node){
    if (node != NULL) {
        return node->height;
    }
    return -1;
}

static avl_node_t* left_rotation(avl_node_t *node){

    avl_node_t *temp = node->right;
    node->right = temp->left;
    temp->left = node;

    node->height = max(avl_height(node->left), avl_height(node->right)) + 1;
    temp->height = max(avl_height(temp->right), node->height) + 1;

    return temp;
}

static avl_node_t* right_rotation(avl_node_t *node){

    avl_node_t *temp = node->left;
    node->left = temp->right;
    temp->right = node;

    node->height = max(avl_height(node->left), avl_height(node->right)) + 1;
    temp->height = max(avl_height(temp->left), node->height) + 1;

    return temp;
}

static avl_node_t* left_right_rotation(avl_node_t *node){
    node->left = left_rotation(node->left);
    return right_rotation(node);
}

static avl_node_t* right_left_rotation(avl_node_t *node){
    node->right = right_rotation(node->right);
    return left_rotation(node);
}

avl_node_t* avl_tree_init(int data) {
    avl_node_t* root = (avl_node_t *)malloc(sizeof(avl_node_t));
    root->data = data;
    root->left = root->right = NULL;
    return root;
}

avl_node_t* avl_insert(avl_node_t *node, int data){
    if (node != NULL) {
        avl_node_t *new = (avl_node_t *)malloc(sizeof(avl_node_t));
        new->data = data;
        new->left = new->right = NULL;
        new->height = 0;
        stacks_t *stacks = stacks_avl_init();
        int flag = 0;
        do {
            if (node->data > data) {
                stacks_avl_push(stacks, node);
                if (node->left == NULL) {
                    node->left = new;
                    break;
                }
                node = node->left;
            } else if (node->data < data) {
                stacks_avl_push(stacks, node);
                if (node->right == NULL) {
                    node->right = new;
                    break;
                }
                node = node->right;
            }
        } while (node->data != data);
        if (node->data == data) {
            free(new);
            goto end;
        }
        while (stacks->next != NULL) {
            avl_node_t *check = stacks_avl_top(stacks);
            if (avl_height(check->left)
                - avl_height(check->right) == 2){
                if (data < check->left->data) {
                    check = right_rotation(check);
                } else {
                    check = left_right_rotation(check);
                }
                flag = 1;
            } else if (avl_height(check->right)
                       - avl_height(check->left) == 2) {
                if (data > check->right->data) {
                    check = left_rotation(check);
                } else {
                    check = right_left_rotation(check);
                }
                flag = 2;
            }
            check->height = max(avl_height(check->left),
                                avl_height(check->right)) + 1;
            stacks_avl_pop(stacks);
            avl_node_t *temp = stacks_avl_top(stacks);
            if (temp != NULL) {
                switch (flag) {
                    case 1:
                        temp->left = check;
                        break;
                    case 2:
                        temp->right = check;
                        break;
                    default:
                        break;
                }
                temp->height = max(avl_height(temp->left),
                                   avl_height(temp->right)) + 1;
                continue;
            }
            node = check;
            flag = 0;
        }
        end:
        free(stacks);
        return node;
    }
    return NULL;
}

avl_node_t* avl_delete(avl_node_t *node, int data){
    if (node != NULL) {
        int rotation_flag = 0;
        stacks_t *stacks = stacks_avl_init();
        while (node != NULL && node->data != data){
            if (node->data > data) {
                stacks_avl_push(stacks, node);
                node = node->left;
            } else if (node->data < data) {
                stacks_avl_push(stacks, node);
                node = node->right;
            }
        }
        if (stacks->next == NULL) {
            stacks_avl_push(stacks, node);
        }
        if (node != NULL && node->data == data) {
            avl_node_t *parent = stacks_avl_top(stacks);
            int direction = 0;
            if(parent != NULL) {
                if (parent->left == node) {
                    direction = 1;
                } else if (parent->right == node) {
                    direction = 2;
                }
            }
            if (node->left != NULL && node->right != NULL) {
                avl_node_t *backup = node;
                backup = backup->left;
                if (backup->right != NULL) {
                    stacks_avl_push(stacks, backup);
                    while (backup->right != NULL) {
                        backup = backup->right;
                        stacks_avl_push(stacks, backup);
                    }
                    avl_node_t *successor = stacks_avl_top(stacks);
                    node->data = successor->data;
                    stacks_avl_pop(stacks);
                    avl_node_t *s_parent = stacks_avl_top(stacks);
                    s_parent->right = successor->left;
                } else {
                    node->data = backup->data;
                    node->left = backup->left;
                    stacks_avl_push(stacks, node);
                    free(backup);
                    backup = NULL;
                }
            } else if (node->left != NULL && node->right == NULL) {
                if (direction == 1) {
                    parent->left = node->left;
                } else if (direction == 2) {
                    parent->right = node->left;
                }
                free(node);
                node = NULL;
            } else if (node->left == NULL && node->right != NULL) {
                if (direction == 1) {
                    parent->left = node->right;
                } else if (direction == 2) {
                    parent->right = node->right;
                }
                free(node);
                node = NULL;
            } else if (node->left == NULL && node->right == NULL) {
                if (direction == 1) {
                    parent->left = NULL;
                } else if (direction == 2) {
                    parent->right = NULL;
                }
                free(node);
                node = NULL;
            }
        } else {
            goto end;
        }
        while (stacks->next != NULL) {
            avl_node_t *check = stacks_avl_top(stacks);
            check->height = max(avl_height(check->left), avl_height(check->right)) + 1;
            if (avl_height(check->left) - avl_height(check->right) == 2) {
                if (avl_height(check->left->left) == -1) {
                    check = left_right_rotation(check);
                    rotation_flag = 2;
                } else {
                    check = right_rotation(check);
                    rotation_flag = 1;
                }
            } else if (avl_height(check->right) - avl_height(check->left) == 2) {
                if (avl_height(check->right->right) == -1) {
                    check = right_left_rotation(check);
                    rotation_flag = 1;
                } else {
                    check = left_rotation(check);
                    rotation_flag = 2;
                }
            }
            stacks_avl_pop(stacks);
            avl_node_t *child_adjust = stacks_avl_top(stacks);
            if (child_adjust != NULL) {
                switch (rotation_flag) {
                    case 1:
                        child_adjust->left = check;
                        rotation_flag = 0;
                        break;
                    case 2:
                        child_adjust->right = check;
                        rotation_flag = 0;
                        break;
                    default:
                        break;
                }
            }
            node = check;
        }
        end:
        free(stacks);
        return node;
    }
}

avl_node_t* avl_search(avl_node_t *node, int data){
    if (node->data == data) {
        return node;
    }
    while (node != NULL && node->data != data){
        if (node->data > data) {
            node = node->left;
        } else if (node->data < data) {
            node = node->right;
        }
    }
    if (node != NULL) {
        return node;
    }
    return NULL;
}