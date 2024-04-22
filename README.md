# Overview
This project contains 2 main programs: no-comment.c and primes.c \
no-comment.c is used for removing C/C++ like comments from files using finite state machine. \
primes.c is optimized Eratosthenes Sieve that uses custom bitset library. \
error.h and error.c are custom libraries for printing errors. \
eratosthenes.h and eratosthenes.c are files with seieve implementation that uses functions from bitset.h library. 
# How to use
To compile everything you can use command make all from Makefiile.
If you want to compile only some files use
<pre>
  make [name-of-file]
</pre>
You can run the program using command make run, that runs the primes file with both inlined and non-inlined macros.
To run no-comment you can use
<pre>
  ./no-comment [input-file] > [redirected-output-file]
</pre>
Note that redirected output must not be the input-file.
When output is not redirected it prints the contents to the stdin.

