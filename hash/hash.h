//
// Created by simon on 17-9-9.
//

#ifndef D_A_HASH_H
#define D_A_HASH_H

#include "../main.h"

#define HASH_TABLE_SIZE 2

typedef struct hash_list_node_s hash_list_node_t;

struct hash_list_node_s {
    const char *data;
    hash_list_node_t *next;
};

struct hash_table_s {
    size_t table_size;
    size_t counter;
    hash_list_node_t **lists;
};

uintptr_t hash_key(const char *str);

hash_table_t *hash_init(size_t table_size);

void hash_insert(hash_table_t *ht, const char *str);

void hash_delete(hash_table_t *ht, const char *str);

hash_list_node_t *hash_find(hash_table_t *ht, const char *str);

hash_table_t *hash_destroy(hash_table_t *ht);

void hash_test();

#endif //D_A_HASH_H
