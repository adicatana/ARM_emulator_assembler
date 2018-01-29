#include "map.h"

// A simple hashmap implementation from string to int
// need an array of linked lists
map *initialize_map() {
    map *hm = malloc(sizeof(map));
    if (!hm) {
        return NULL;
    }

    for (int i = 0; i < NUMBER_OF_BUCKETS; i++) {
        hm->buckets[i] = NULL;
    }
    return hm;
}

// Hash value for every string
int hash_code(const char * const key) {
    if (!key) {
        return 0;
    }

    int lim = strlen(key);
    int hash_value = 0;

    for (int i = 0; i < lim; i++) {
        hash_value = ((long long) hash_value * base + key[i]) % NUMBER_OF_BUCKETS;
    }

    return hash_value;
}

// Node creation & alloc
struct node *alloc_node(char * const key, int value) {
    struct node *new_node = malloc(sizeof(struct node));

    if (!new_node) {
        perror("Memory allocation error.\n");
    }

    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;

    return new_node;

}

// Insertion into hm of value at key
void insert(char * const key, int value, map * const hm) {

    int hash = hash_code(key);
    
    if (!hm->buckets[hash]) {
        struct node *new_node = alloc_node(key, value);
        hm->buckets[hash] = new_node;
        return;
    } 

    struct node *root = hm->buckets[hash];
    
    while (!strcmp(root->key, key) && root->next) {
        root = root->next;
    }

    if (!strcmp(root->key, key)) {
        root->value = value;
        return;
    }

    struct node *new_node = alloc_node(key, value);
    root->next = new_node;

}

// Get key value from hm, error if no such key
int get(char * const key, const map * const hm) {
    int hash_value = hash_code(key);
    struct node *root = hm->buckets[hash_value];

    while (root) {
        if (!strcmp(root->key, key)) {
            return root->value;
        }
        root = root->next;
    }

    perror("No pair for key/value found in hashmap.\n");

    return 0;

}

// Freeing all the memory
void destroy_map(map *hm) {
    for (int i = 0; i < NUMBER_OF_BUCKETS; i++) {
        if (hm->buckets[i]) {
            struct node *root = hm->buckets[i];
            while (root) {
                struct node *curr = root;
                root = root->next;
                free(curr);
                curr = NULL;
            }
        }
    }
    free(hm);
    hm = NULL;
}    