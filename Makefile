# Makefile
# Solution IJC-DU1, Task A, 19.3.2024
# Author: Michal Repčík, FIT
# Compiled: gcc 11.4.0

CC = gcc
CFLAGS = -O2 -g -std=c11 -pedantic -Wall -Wextra -fsanitize=address
LDFLAGS = -fsanitize=address
OPFLAGS = -DUSE_INLINE
LIBS = -lm

TARGETS = primes primes-i no-comment

.PHONY: all run clean zip

all: $(TARGETS)

primes: primes.o error.o eratosthenes.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) $(LDFLAGS)

primes-i: primes.o error.o eratosthenes.o
	$(CC) $(CFLAGS) $(OPFLAGS) $^ -o $@ $(LIBS) $(LDFLAGS)

no-comment: no-comment.o error.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

run: primes primes-i
	ulimit -s unlimited && \
    ./primes && \
    ./primes-i

clean:
	rm -f $(TARGETS) *.o

zip:
	zip xrepcim00.zip *.c *.h Makefile
