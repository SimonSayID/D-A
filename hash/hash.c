//
// Created by simon on 17-9-9.
//

#include "../main.h"


uintptr_t hash_key(const char *str) {
    uintptr_t key = 0;

    u_char *data = (u_char *) str;
    size_t size = strlen(str);

    for (int i = 0; i < size; ++i) {
        key = (uintptr_t) key * 31 + data[i];
    }

    return key % HASH_TABLE_SIZE;
}

hash_table_t *hash_init(size_t table_size) {
    if (table_size < HASH_TABLE_SIZE) {
        table_size = HASH_TABLE_SIZE;
    }

    hash_table_t *ht = malloc(sizeof(hash_table_t));
    ht->table_size = table_size;
    ht->counter = 0;
    ht->lists = (hash_list_node_t **) calloc(ht->table_size, sizeof(hash_list_node_t *));

    return ht;
}

void hash_insert(hash_table_t *ht, const char *str) {
    hash_list_node_t *p, *new;
    uint64_t index = hash_key(str);
    p = ht->lists[index];
    while (p != NULL) {
        if (strcmp(p->data, str) == 0) {
            break;
        }
        p = p->next;
    }
    if (p == NULL) {
        new = (hash_list_node_t *) malloc(sizeof(hash_list_node_t));
        p = ht->lists[index];
        new->data = str;
        if (p != NULL) {
            new->next = p->next;
            p->next = new;
        } else {
            new->next = NULL;
            ht->lists[index] = new;
        }
        ht->counter++;
    }
}

void hash_delete(hash_table_t *ht, const char *str) {
    uint64_t index = hash_key(str);
    hash_list_node_t *p = ht->lists[index];
    hash_list_node_t *save = p;
    while (p != NULL) {
        if (strcmp(p->data, str) == 0) {
            break;
        }
        save = p;
        p = p->next;
    }
    if (p != NULL) {
        if (save == p) {
            ht->lists[index] = p->next;
            free(p);
        } else {
            save->next = p->next;
            free(p);
        }
        ht->counter--;
    }
}

hash_list_node_t *hash_find(hash_table_t *ht, const char *str) {
    uint64_t index = hash_key(str);
    hash_list_node_t *p = ht->lists[index];
    while (p != NULL) {
        if (strcmp(p->data, str) == 0) {
            break;
        }
        p = p->next;
    }
    return p;
}

hash_table_t *hash_destroy(hash_table_t *ht) {
    for (int i = 0; i < ht->table_size; ++i) {
        hash_list_node_t *d = ht->lists[i];
        while (d != NULL) {
            hash_list_node_t *t = d->next;
            free(d);
            d = t;
        }
    }
    free(ht->lists);
    free(ht);
    ht = NULL;
    return ht;
}