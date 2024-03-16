// error.h
// Solution IJC-DU1, Task B, 12.3.2024
// Author: Michal Repčík, FIT
// Compiled: gcc 12.3

#ifndef ERROR_H
#define ERROR_H

void warning(const char *fmt, ...);
void error_exit(const char *fmt, ...);

#endif // ERROR_H