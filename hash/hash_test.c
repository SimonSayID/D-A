//
// Created by simon on 17-9-9.
//


#include "../main.h"

void hash_test() {
    const char *s1 = "helloaqweqwe";
    const char *s2 = "helloaqweqw";
    const char *s3 = "helloaqweq";
    hash_table_t *ht = hash_init(2);
    hash_insert(ht, s1);
    hash_insert(ht, s2);
    hash_insert(ht, s3);
    hash_list_node_t *node = hash_find(ht, s1);
    assert(node->data == "helloaqweqwe");
    node = hash_find(ht, s2);
    assert(node->data == "helloaqweqw");
    node = hash_find(ht, s3);
    assert(node->data == "helloaqweq");
    hash_delete(ht, s2);
    node = hash_find(ht, s2);
    assert(node == NULL);
    hash_delete(ht, s1);
    node = hash_find(ht, s1);
    assert(node == NULL);
    hash_delete(ht, s3);
    node = hash_find(ht, s3);
    assert(node == NULL);
    hash_insert(ht, s1);
    hash_insert(ht, s2);
    hash_insert(ht, s3);
    ht = hash_destroy(ht);
    assert(ht == NULL);
}