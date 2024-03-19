// bitset.h
// Solution IJC-DU1, Task A, 19.3.2024
// Author: Michal Repčík, FIT
// Compiled: gcc 11.4.0

#ifndef BITSET_H
#define BITSET_H

#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#include "error.h"

#define UL_BITS (sizeof(unsigned long)*CHAR_BIT)    //size of ul in bits

typedef unsigned long* bitset_t;        // Array of bits
typedef unsigned long bitset_index_t;   // Index for bit array

// MACROS THAT CANNOT BE INLINED 

// Function that creates and initializes bitset (reformated)
#define bitset_create(bitset, size) \
        static_assert(size > 0, "bitset_create: Size of an array should be greater than 0"); \
        unsigned long (bitset)[(size + UL_BITS - 1)/UL_BITS + 1] = {(size), }; 

// Function that dynamically allocates memory for bitset and initializes all bits to 0
#define bitset_alloc(bitset, size) \
    do { \
        assert(size > 0); \
        bitset = calloc((size + UL_BITS - 1)/UL_BITS + 1, sizeof(unsigned long)); \
        if (bitset == NULL) { \
            error_exit("bitset_alloc: Chyba alokace paměti"); \
        } \
        bitset[0] = (size); \
    } while (0)

#ifdef USE_INLINE 

// INLINE FUNCTIONS

// Function that frees dynamically allocated memory for bitset
static inline void bitset_free(bitset_t bitset) {
    if (bitset != NULL) {
        free(bitset);
    }
}

// Function that returs the size of a bitset
static inline bitset_index_t bitset_size(bitset_t bitset) {
    return bitset[0];
}

// Function that sets all bits in bitset to either 1 or 0
static inline void bitset_fill(bitset_t bitset, bool value) {
    unsigned long size = bitset[0];
    if (value == 1) {
        memset((bitset), -1, ((size + UL_BITS - 1)/UL_BITS + 1)*sizeof(unsigned long));
    }
    else {
        memset((bitset), -1, ((size + UL_BITS - 1)/UL_BITS + 1)*sizeof(unsigned long));
    }
    bitset[0] = size;
}

// Function that sets bit on given index in bitset to either 1 or 0
static inline void bitset_setbit(bitset_t bitset, bitset_index_t index, bool value) {
    if (index > bitset[0]) {
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", index, bitset[0]);
    }
    bitset_index_t i = index/UL_BITS + 1;
    unsigned offset = index % UL_BITS;

    if (value) {
        bitset[i] |= (1UL << offset); 
    }
    else {
        bitset[i] &= ~(1UL << offset);
    }
}

// Function that returns bit from bitset on given index 
static inline bool bitset_getbit(bitset_t bitset, bitset_index_t index) {
    if (index > bitset[0]) {
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", index, bitset[0]);
    }
    bitset_index_t i = index/UL_BITS + 1;
    unsigned offset = index % UL_BITS;

    return bitset[i] & (1UL << offset);
}

#else

// INLINE FUNCTIONS DEFINED AS MACROS

#define bitset_free(bitset) \
    do { \
        if (bitset != NULL) { \
            free(bitset); \
        } \
    } while(0)

#define bitset_size(bitset) \
    (bitset[0])

#define bitset_fill(bitset, value) \
    do { \
        unsigned long size = bitset[0]; \
        if (value == 1) { \
            memset((bitset), -1, ((size + UL_BITS - 1)/UL_BITS + 1)*sizeof(unsigned long)); \
        } else { \
            memset((bitset), 0, ((size + UL_BITS - 1)/UL_BITS + 1)*sizeof(unsigned long)); \
        } \
        bitset[0] = size; \
    } while (0)

// Functions reformatted for correct implementation within conditionals
#define bitset_setbit(bitset, index, value) \
    ((index > bitset[0]) ? \
    (error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)bitset[0]), 0) : \
    (value == 1) ? \
    (bitset[index/UL_BITS + 1] |= (1UL << (index % UL_BITS))) : \
    (bitset[index/UL_BITS + 1] &= ~(1UL << (index % UL_BITS))))

#define bitset_getbit(bitset, index) \
    (index > bitset[0]) ? \
    (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)bitset[0]), 0) : \
    ((((bitset)[index/UL_BITS + 1]) & (1UL << (index % UL_BITS)) ? 1 : 0))

#endif // USE_INLINE
#endif // BITSET_H