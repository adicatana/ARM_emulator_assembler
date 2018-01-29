#ifndef __MAP_H__
#define __MAP_H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define NUMBER_OF_BUCKETS 100


struct node {
    char *key;
    int value;
    struct node *next;
};

typedef struct {
    struct node *buckets[NUMBER_OF_BUCKETS];
} map;

map *initialize_map();
void insert(char * const key, int value, map * const hm);
int get(char * const key, const map * const hm);
void destroy_map(map * const);

#endif