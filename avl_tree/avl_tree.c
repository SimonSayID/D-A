//
// Created by simon on 8/27/17.
//

#include "../main.h"

static int avl_height(avl_node_t *node){
    if (node != NULL) {
        return node->height;
    }
    return -1;
}

static avl_node_t* avl_left_rotation(avl_node_t *node){

    avl_node_t *temp = node->right;
    node->right = temp->left;
    temp->left = node;

    node->height = max(avl_height(node->left), avl_height(node->right)) + 1;
    temp->height = max(avl_height(temp->right), node->height) + 1;

    return temp;
}

static avl_node_t* avl_right_rotation(avl_node_t *node){

    avl_node_t *temp = node->left;
    node->left = temp->right;
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

        stack_avl_t *stacks = stacks_avl_init();
        do {
            stacks_avl_push(stacks, node);
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
        } while (node->data != data);
        if (node->data == data) {
            free(new);
            goto end;
        }

        while (stacks->next != NULL) {

            avl_node_t *rb = stacks_avl_top(stacks);
            rb->height = max(avl_height(rb->left), avl_height(rb->right)) + 1;
            avl_node_t *save = rb;

            if (avl_height(rb->left) - avl_height(rb->right) == 2){
                if (avl_height(rb->left->left) - avl_height(rb->left->right) == 1) {
                    rb = avl_right_rotation(rb);
                } else {
                    rb = avl_left_right_rotation(rb);
                }
            } else if (avl_height(rb->right) - avl_height(rb->left) == 2) {
                if (avl_height(rb->right->right) - avl_height(rb->right->left) == 1) {
                    rb = avl_left_rotation(rb);
                } else {
                    rb = avl_right_left_rotation(rb);
                }
            }

            stacks_avl_pop(stacks);
            avl_node_t *rbp = stacks_avl_top(stacks);
            if (rbp != NULL) {
                if (rbp->right == save) {
                    rbp->right = rb;
                } else {
                    rbp->left = rb;
                }
                rbp->height = max(avl_height(rbp->left), avl_height(rbp->right)) + 1;
            } else {
                node = rb;
            }
        }
        end:
        free(stacks);
        return node;
    }
    return NULL;
}

avl_node_t* avl_delete(avl_node_t *node, int data){
    if (node != NULL) {
        avl_node_t *temp = node;
        stack_avl_t *stack_avl = stacks_avl_init();
        while (temp != NULL && temp->data != data) {
            stacks_avl_push(stack_avl, temp);
            if (temp->data > data) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }

        if (temp != NULL) {
            /* root */
            if (temp->left != NULL && temp->right != NULL){

                int empty = 0;
                if (stack_avl->next == NULL) {
                    empty = 1;
                }

                avl_node_t *s = temp;
                temp = temp->left; // temp's left subtree root
                stacks_avl_push(stack_avl, temp);

                while (temp->right != NULL) {
                    temp = temp->right;
                    stacks_avl_push(stack_avl, temp);
                }

                s->data = temp->data;
                stacks_avl_pop(stack_avl);

                if (temp != s->left) {
                    avl_node_t *tp = stacks_avl_top(stack_avl);
                    tp->right = temp->left; //left subtree maximum node's parent adjustment
                    if (empty) {
                        stacks_avl_pop(stack_avl);
                        stacks_avl_push(stack_avl, s);
                        stacks_avl_push(stack_avl, tp);
                    }
                } else {
                    if (temp->left != NULL) {
                        s->left = temp->left;
                    } else {
                        s->left = NULL;
                    }
                    stacks_avl_push(stack_avl, s);
                }

            }
            else {

                avl_node_t *parent = stacks_avl_top(stack_avl);

                    /* no child */
                 if (temp->left == NULL && temp->right == NULL) {
                    if (parent != NULL) {
                        if (parent->right == temp) {
                            parent->right = NULL;
                        } else {
                            parent->left = NULL;
                        }
                    } else {
                        free(temp);
                        free(stack_avl);
                        node = NULL;
                        return node;
                    }
                }
                     /* left child */
                 else if (temp->left != NULL) {
                    if (parent != NULL) {
                        if (parent->right == temp) {
                            parent->right = temp->left;
                        } else {
                            parent->left = temp->left;
                        }
                    } else {
                        node = temp->left;
                    }
                }
                    /* right child */
                 else {
                    if (parent != NULL) {
                        if (parent->right == temp) {
                            parent->right = temp->right;
                        } else {
                            parent->left = temp->right;
                        }
                    } else {
                        node = temp->right;
                    }
                }
            }

            free(temp);

            while (stack_avl->next != NULL) {

                avl_node_t *rb = stacks_avl_top(stack_avl);
                rb->height = max(avl_height(rb->left), avl_height(rb->right)) + 1;
                avl_node_t *save = rb;

                if (avl_height(rb->left) - avl_height(rb->right) == 2) {
                    if (avl_height(rb->left->right) - avl_height(rb->left->left) == 1) {
                        rb = avl_left_right_rotation(rb);
                    } else {
                        rb = avl_right_rotation(rb);
                    }
                } else if (avl_height(rb->right) - avl_height(rb->left) == 2) {
                    if (avl_height(rb->right->left) - avl_height(rb->right->right) == 1) {
                        rb = avl_right_left_rotation(rb);
                    } else {
                        rb = avl_left_rotation(rb);
                    }
                }

                stacks_avl_pop(stack_avl);

                if (stack_avl->next != NULL) {
                    avl_node_t *rbp = stacks_avl_top(stack_avl);
                    if (rbp->right == save) {
                        rbp->right = rb;
                    } else {
                        rbp->left = rb;
                    }
                    rbp->height = max(avl_height(rbp->left), avl_height(rbp->right)) + 1;
                } else {
                    node = rb;
                }
            }

            free(stack_avl);
        }

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