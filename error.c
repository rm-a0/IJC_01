// error.c
// Solution IJC-DU1, Task B, 15.3.2024
// Author: Michal Repčík, FIT
// Compiled: gcc 11.4.0

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "error.h"

// Function for printing warning msgs
void warning(const char *fmt, ...) {
	fprintf(stderr, "Warning: ");
	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
}

// Funtion for printing error msgs
void error_exit(const char *fmt, ...) {
	fprintf(stderr, "Error: ");
	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	exit(1);
}