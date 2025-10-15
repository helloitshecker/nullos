#ifndef LIBC_STDLIB_H
#define LIBC_STDLIB_H

#include <stdint.h>
#include <stdbool.h>

int atoi(const char* str);
void itoa(int num, char* str);

void __malloc_init__(void);
void* malloc(size size);

#endif
