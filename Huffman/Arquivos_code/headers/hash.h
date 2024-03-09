#ifndef HASH_H
#define HASH_H

#define MAX_HASH_ADDRESS_SIZE 256

/** Hash Table - Mapeamento de bits **/
typedef struct HASH{
    void *table[MAX_HASH_ADDRESS_SIZE];
} HASH;

HASH *create_hash();

void put(HASH *new_hash, int key, char *representation);

void *get(HASH *ht, int key);

void free_hash(HASH *ht);

#endif //HASH_H
