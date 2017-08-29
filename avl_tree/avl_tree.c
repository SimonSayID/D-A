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

        stack_avl_t *stacks = stacks_avl_init();
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
            new = NULL;
            goto end;
        }

        while (stacks->next != NULL) {
            avl_node_t *rb = stacks_avl_top(stacks);
            avl_node_t *save = rb;

            if (avl_height(rb->left) - avl_height(rb->right) == 2){
                if (data < rb->left->data) {
                    rb = right_rotation(rb);
                } else {
                    rb = left_right_rotation(rb);
                }
            } else if (avl_height(rb->right) - avl_height(rb->left) == 2) {
                if (data > rb->right->data) {
                    rb = left_rotation(rb);
                } else {
                    rb = right_left_rotation(rb);
                }
            }
            rb->height = max(avl_height(rb->left), avl_height(rb->right)) + 1;

            stacks_avl_pop(stacks);
            avl_node_t *rbp = stacks_avl_top(stacks);
            if (rbp != NULL) {
                if (rbp->right == save) {
                    rbp->right = rb;
                } else {
                    rbp->left = rb;
                }
                rbp->height = max(avl_height(rbp->left), avl_height(rbp->right)) + 1;
                continue;
            }

            node = rb;
        }
        end:
        free(stacks);
        stacks = NULL;
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
            } else if (temp->data < data) {
                temp = temp->right;
            }
        }

        if (temp != NULL) {
            /* root */
            if (temp->left != NULL && temp->right != NULL){

                avl_node_t *s = temp;
                temp = temp->left; // temp's left subtree root
                stacks_avl_push(stack_avl, temp);

                while (temp->right != NULL) {
                    temp = temp->right;
                    stacks_avl_push(stack_avl, temp);
                }

                s->data = temp->data;

                if (temp != s->left) {
                    avl_node_t *tp = stacks_avl_top(stack_avl);
                    tp->right = temp->left; //left subtree maximum node's parent adjustment
                } else {
                    if (temp->left != NULL) {
                        s->left = temp->left;
                    } else {
                        s->left = NULL;
                    }
                    stacks_avl_pop(stack_avl);
                    stacks_avl_push(stack_avl, s);
                }

            }
                /* no child */
            else if (temp->left == NULL && temp->right == NULL) {

                avl_node_t *parent = stacks_avl_top(stack_avl);
                if (parent != NULL) {
                    if (parent->right == temp) {
                        parent->right = NULL;
                    } else {
                        parent->left = NULL;
                    }
                }
            }
                /* left child */
            else if (temp->left != NULL && temp->right == NULL) {

                avl_node_t *parent = stacks_avl_top(stack_avl);
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
            else if (temp->left == NULL && temp->right != NULL) {

                avl_node_t *parent = stacks_avl_top(stack_avl);
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

            free(temp);
            temp = NULL;

            while (stack_avl->next != NULL) {

                avl_node_t *rb = stacks_avl_top(stack_avl);
                avl_node_t *save = rb;

                rb->height = max(avl_height(rb->left), avl_height(rb->right));
                if (avl_height(rb->left) - avl_height(rb->right) == 2) {
                    if (avl_height(rb->left->right) - avl_height(rb->left->left) == 2) {
                        rb = left_right_rotation(rb);
                    } else {
                        rb = right_rotation(rb);
                    }
                } else if (avl_height(rb->right) - avl_height(rb->left) == 2) {
                    if (avl_height(rb->right->left) - avl_height(rb->right->right) == 2) {
                        rb = right_left_rotation(rb);
                    } else {
                        rb = left_rotation(rb);
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
            stack_avl = NULL;
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

/*********for learning***********/
// test node number = 22;
static void avl_tree_test1() {
    avl_node_t *root = avl_tree_init(1);
    root = avl_insert(root, 2);
    root = avl_insert(root, 3);
    root = avl_insert(root, 4);
    root = avl_insert(root, 5);
    root = avl_insert(root, 6);
    root = avl_insert(root, 7);
    root = avl_insert(root, 8);
    root = avl_insert(root, 9);
    root = avl_insert(root, 10);
    root = avl_insert(root, 11);
    root = avl_insert(root, 12);
    root = avl_insert(root, 13);
    root = avl_insert(root, 14);
    root = avl_insert(root, 15);
    root = avl_insert(root, 16);
    root = avl_insert(root, 17);
    root = avl_insert(root, 18);
    root = avl_insert(root, 19);
    root = avl_insert(root, 20);
    root = avl_insert(root, 21);
    root = avl_insert(root, 22);

    root = avl_delete(root, 1);
    root = avl_delete(root, 2);
    root = avl_delete(root, 3);
    root = avl_delete(root, 4);
    root = avl_delete(root, 5);
    root = avl_delete(root, 6);
    root = avl_delete(root, 7);
    root = avl_delete(root, 8);
    root = avl_delete(root, 9);
    root = avl_delete(root, 10);
    root = avl_delete(root, 11);
    root = avl_delete(root, 12);
    root = avl_delete(root, 13);
    root = avl_delete(root, 14);
    root = avl_delete(root, 15);
    root = avl_delete(root, 16);
    root = avl_delete(root, 18);
    root = avl_delete(root, 19);
    root = avl_delete(root, 20);
    root = avl_delete(root, 21);
    root = avl_delete(root, 22);
    root = avl_delete(root, 17);
}

static void avl_tree_test2() {
    avl_node_t* root = avl_tree_init(22);
    root = avl_insert(root, 21);
    root = avl_insert(root, 20);
    root = avl_insert(root, 19);
    root = avl_insert(root, 18);
    root = avl_insert(root, 17);
    root = avl_insert(root, 16);
    root = avl_insert(root, 15);
    root = avl_insert(root, 14);
    root = avl_insert(root, 13);
    root = avl_insert(root, 12);
    root = avl_insert(root, 11);
    root = avl_insert(root, 10);
    root = avl_insert(root, 9);
    root = avl_insert(root, 8);
    root = avl_insert(root, 7);
    root = avl_insert(root, 6);
    root = avl_insert(root, 5);
    root = avl_insert(root, 4);
    root = avl_insert(root, 3);
    root = avl_insert(root, 2);
    root = avl_insert(root, 1);

    root = avl_delete(root, 1);
    root = avl_delete(root, 2);
    root = avl_delete(root, 3);
    root = avl_delete(root, 4);
    root = avl_delete(root, 5);
    root = avl_delete(root, 6);
    root = avl_delete(root, 7);
    root = avl_delete(root, 8);
    root = avl_delete(root, 9);
    root = avl_delete(root, 10);
    root = avl_delete(root, 11);
    root = avl_delete(root, 12);
    root = avl_delete(root, 13);
    root = avl_delete(root, 14);
    root = avl_delete(root, 15);
    root = avl_delete(root, 16);
    root = avl_delete(root, 17);
    root = avl_delete(root, 18);
    root = avl_delete(root, 19);
    root = avl_delete(root, 20);
    root = avl_delete(root, 21);
    root = avl_delete(root, 22);
}

static void avl_tree_test3() {
    avl_node_t*root = avl_tree_init(1);
    root = avl_insert(root, 2);
    root = avl_insert(root, 3);
    root = avl_insert(root, 4);
    root = avl_insert(root, 5);
    root = avl_insert(root, 6);
    root = avl_insert(root, 7);
    root = avl_insert(root, 8);
    root = avl_insert(root, 9);
    root = avl_insert(root, 10);
    root = avl_insert(root, 11);
    root = avl_insert(root, 12);
    root = avl_insert(root, 13);
    root = avl_insert(root, 14);
    root = avl_insert(root, 15);
    root = avl_insert(root, 16);
    root = avl_insert(root, 17);
    root = avl_insert(root, 18);
    root = avl_insert(root, 19);
    root = avl_insert(root, 20);
    root = avl_insert(root, 21);
    root = avl_insert(root, 22);

    root = avl_delete(root, 22);
    root = avl_delete(root, 21);
    root = avl_delete(root, 20);
    root = avl_delete(root, 19);
    root = avl_delete(root, 18);
    root = avl_delete(root, 17);
    root = avl_delete(root, 16);
    root = avl_delete(root, 15);
    root = avl_delete(root, 14);
    root = avl_delete(root, 13);
    root = avl_delete(root, 12);
    root = avl_delete(root, 11);
    root = avl_delete(root, 10);
    root = avl_delete(root, 9);
    root = avl_delete(root, 8);
    root = avl_delete(root, 7);
    root = avl_delete(root, 6);
    root = avl_delete(root, 5);
    root = avl_delete(root, 4);
    root = avl_delete(root, 3);
    root = avl_delete(root, 2);
    root = avl_delete(root, 1);
}

static void avl_tree_test4() {
    avl_node_t*root = avl_tree_init(22);
    root = avl_insert(root, 21);
    root = avl_insert(root, 20);
    root = avl_insert(root, 19);
    root = avl_insert(root, 18);
    root = avl_insert(root, 17);
    root = avl_insert(root, 16);
    root = avl_insert(root, 15);
    root = avl_insert(root, 14);
    root = avl_insert(root, 13);
    root = avl_insert(root, 12);
    root = avl_insert(root, 11);
    root = avl_insert(root, 10);
    root = avl_insert(root, 9);
    root = avl_insert(root, 8);
    root = avl_insert(root, 7);
    root = avl_insert(root, 6);
    root = avl_insert(root, 5);
    root = avl_insert(root, 4);
    root = avl_insert(root, 3);
    root = avl_insert(root, 2);
    root = avl_insert(root, 1);

    root = avl_delete(root, 22);
    root = avl_delete(root, 21);
    root = avl_delete(root, 20);
    root = avl_delete(root, 19);
    root = avl_delete(root, 18);
    root = avl_delete(root, 17);
    root = avl_delete(root, 16);
    root = avl_delete(root, 15);
    root = avl_delete(root, 14);
    root = avl_delete(root, 13);
    root = avl_delete(root, 12);
    root = avl_delete(root, 11);
    root = avl_delete(root, 10);
    root = avl_delete(root, 9);
    root = avl_delete(root, 8);
    root = avl_delete(root, 7);
    root = avl_delete(root, 6);
    root = avl_delete(root, 5);
    root = avl_delete(root, 4);
    root = avl_delete(root, 3);
    root = avl_delete(root, 2);
    root = avl_delete(root, 1);
}
/*********for learning***********/

/***********for test*************/
// test node number = 100000;
static void avl_tree_test5() {
    avl_node_t *root = avl_tree_init(0);
    for (int i = 1; i <= 100000; ++i) {
        root = avl_insert(root, i);
    }
    for (int j = 100000; j >= 0; --j) {
        root = avl_delete(root, j);
    }
}

static void avl_tree_test6() {
    avl_node_t *root = avl_tree_init(0);
    for (int j = 100000; j > 0; --j) {
        root = avl_insert(root, j);
    }
    for (int i = 0; i <= 100000; ++i) {
        root = avl_delete(root, i);
    }
}

static void avl_tree_test7() {
    avl_node_t *root = avl_tree_init(0);
    for (int i = 1; i <= 100000; ++i) {
        root = avl_insert(root, i);
    }
    for (int i = 0; i <= 100000; ++i) {
        root = avl_delete(root, i);
    }
}

static void avl_tree_test8() {
    avl_node_t *root = avl_tree_init(0);
    for (int j = 100000; j > 0; --j) {
        root = avl_insert(root, j);
    }
    for (int j = 100000; j >= 0; --j) {
        root = avl_delete(root, j);
    }
}
/***********for test*************/

void avl_tree_test(){
//    avl_tree_test1();
//    avl_tree_test2();
//    avl_tree_test3();
//    avl_tree_test4();
//    avl_tree_test5();
//    avl_tree_test6();
//    avl_tree_test7();
//    avl_tree_test8();
}