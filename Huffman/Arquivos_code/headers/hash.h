#ifndef HUFFMAN_HASH_H
#define HUFFMAN_HASH_H

#define MAX_HASH_ADDRESS_SIZE 256

/** Hash Table - Mapeamento de bits **/
typedef struct HASH{
    void *table[MAX_HASH_ADDRESS_SIZE];
} HASH;
