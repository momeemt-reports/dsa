#ifndef __OPEN_ADDRESSING_H__
#define __OPEN_ADDRESSING_H__

#include <stdio.h>
#include <stdlib.h>

#define HASH_TABLE_PRIME 11

// typedef enum {
//     EMPTY,
//     DELETED,
//     OCCUPIED,
// } HashItemState;

// typedef struct {
//     int data;
//     HashItemState state;
// } HashItem;

// typedef enum HashTableType {
//     LINEAR_PROBING,
//     DOUBLE_HASHING,
// } HashTableType;

// typedef struct {
//     HashItem *items;
//     HashTableType type;
//     unsigned int size;
//     unsigned int prime;
// } HashTable;

// HashTable *create_hash_table(HashTableType type, int size);
// unsigned int hash_by_size(HashTable *table, int data);
// unsigned int hash_by_prime(HashTable *table, int data);
// int liner_probing_hash(HashTable *table, int data);
// int double_hashing_hash(HashTable *table, int data);
// int calc_hash(HashTable *table, int data);
// void insert_hash(HashTable *table, int data);
// int search_hash(HashTable *table, int data);
// void delete_hash(HashTable *table, int data);
// void display_hash_table(HashTable *table);
// void delete_hash_table(HashTable *table);

typedef enum state { EMPTY, DELETED, OCCUPIED } State;

typedef struct dict_data {
    int name;
    State state;
} DictData;

typedef struct dict_open_addr {
    DictData *H;
    int B;
} DictOpenAddr;

DictOpenAddr *create_dict(int len);
int h(DictOpenAddr *dict, int d, int count);
int g(DictOpenAddr *dict, int d, int count);
void insert_hash(DictOpenAddr *dict, int d);
void insert_hash2(DictOpenAddr *dict, int d);
int search_hash(DictOpenAddr *dict, int d);
int search_hash2(DictOpenAddr *dict, int d);
void delete_hash(DictOpenAddr *dict, int d);
void delete_hash2(DictOpenAddr *dict, int d);
void display_dict_open_addr(DictOpenAddr *dict);
void delete_dict(DictOpenAddr *dict);

#endif  // __OPEN_ADDRESSING_H__
