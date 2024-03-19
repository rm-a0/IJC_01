// primes.c
// Solution IJC-DU1, Task A, 19.3.2024
// Author: Michal Repčík, FIT
// Compiled: gcc 11.4.0

#include <stdio.h>
#include <time.h>

#include "bitset.h"
#include "error.h"
#include "eratosthenes.h"

#define SIZE 666000000 // 666 million

// Function that prints last 10 prime numbers in ascending order
void print_primes(bitset_t bitset) {
    unsigned p_count = 0;
    bitset_index_t p_array[10];

    // Store last 10 prime numbers into an array
    for (bitset_index_t i = SIZE - 1; i >= 1; i--) {
        if (bitset_getbit(bitset, i) == 1) {
            p_array[p_count] = i;
            p_count++;
            if (p_count == 10) {
                break;
            }
        }
    }

    for (int i = p_count - 1; i >= 0; i--) {
        printf("%lu\n", p_array[i]);
    }
}

// Main function
int main(void) {
    clock_t start = clock();

    bitset_create(bitset, SIZE);
    eratosthenes(bitset);
    print_primes(bitset);

    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}