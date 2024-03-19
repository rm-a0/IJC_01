// eratosthenes.c
// Solution IJC-DU1, Task A, 17.3.2024
// Author: Michal Repčík, FIT
// Compiled: gcc 11.4.0

#include <stdio.h>
#include <math.h>

#include "bitset.h"
#include "error.h"
#include "eratosthenes.h"

void eratosthenes(bitset_t bitset) {
    bitset_index_t size = bitset_size(bitset);
    // Set all numbers to 1
    bitset_fill(bitset, 1);

    // Set every even number to 0
    for (bitset_index_t i = 4; i < size; i += 2) {
        bitset_setbit(bitset,  i, 0);
    }

    // We can skip by 2 after setting every even number to 0
    for (bitset_index_t i = 3; i <= sqrt(size); i += 2) {
        // Set every multiple of given number to 0
        if (bitset_getbit(bitset, i) == 1) {
            for (bitset_index_t j = i*i; j < size; j += 2*i)
            {
                bitset_setbit(bitset, j, 0);
            }
        }
    }
}