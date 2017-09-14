//
// Created by simon on 8/27/17.
//

#ifndef ALG_CONFIG_H
#define ALG_CONFIG_H

#include "os.h"

typedef struct list_s                   list_t;
typedef struct queue_s                  queue_t;
typedef struct stack_s              stack_t;
typedef struct avl_node_s               avl_node_t;
typedef struct rb_node_s                rb_node_t;
typedef struct hash_list_node_s         hash_list_node_t;
typedef struct hash_table_s             hash_table_t;
typedef struct bm_heap_node_s           bm_heap_node_t;

#ifndef max
int max(int a, int b);
#endif

size_t next_prime(size_t num);

#endif //ALG_CONFIG_H
