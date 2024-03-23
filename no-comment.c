// no-comment.c
// Solution IJC-DU1, Task B, 16.3.2024
// Author: Michal Repčík, FIT
// Compiled: gcc 11.4.0

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "error.h"

// Function that processes cmd line arguments and returns pointer to the file
FILE* process_file(int argc, char* argv[]) {
    FILE *fp = NULL;
    if (argc > 2) {
        error_exit("Only one argument suppported\n");
    }
    else if (argc == 2) {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            error_exit("Failed to read from the file\n");
        }
    }
    else {
        fp = stdin;
    }
    return fp;
}

// Function that checks if redirected stdout is the same as stdin
void check_stdout(FILE *fp) {
    struct stat input_file; 
    struct stat output_file;
    
    fstat(fileno(fp), &input_file);
    fstat(fileno(stdout), &output_file);

    if (input_file.st_ino == output_file.st_ino) {
        error_exit("Input file is the same as output file\n");
    }
}

// Function that removes comments from the input file
void remove_comments(FILE *fp) {
    int c;
    int state = 0; // Initial state

    while ((c = fgetc(fp)) != EOF) {
        switch (state) {
            case 0: // Initial state
                if (c == '/') {
                    state = 1; // Possibly the start of a comment
                } else if (c == '"') {
                    state = 4; // Inside a string literal
                    putchar(c);
                } else {
                    putchar(c); // Output character
                }
                break;
            case 1: // Possibly the start of a comment
                if (c == '*') {
                    state = 2; // Start of a multi-line comment
                } else if (c == '/') {
                    state = 6; // Start of a single-line comment
                } else {
                    state = 0; // Not a comment, output previous '/' and current character
                    putchar('/');
                    putchar(c);
                }
                break;
            case 2: // Inside a multi-line comment
                if (c == '*') {
                    state = 3; // Possibly the end of the comment
                }
                break;
            case 3: // Possibly the end of the multi-line comment
                if (c == '/') {
                    state = 0; // End of the comment
                } else if (c != '*') {
                    state = 2; // Still inside the comment
                }
                break;
            case 4: // Inside a string literal
                if (c == '\\') {
                    state = 5; // Possibly an escape sequence
                } else if (c == '"') {
                    state = 0; // End of the string literal
                }
                putchar(c);
                break;
            case 5: // Possibly inside an escape sequence
                state = 4; // Continue inside the string literal
                putchar(c);
                break;
            case 6: // Start of a single line-comment
                if (c == '\n') {
                    putchar(c);
                    state = 0; // End of comment
                }
                break;
        }
    }
}

// Main function
int main(int argc, char* argv[]) {
    FILE *fp;

    fp = process_file(argc, argv);
    check_stdout(fp);
    remove_comments(fp);
    
    fclose(fp);
    return 0;
}