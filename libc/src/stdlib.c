#include <stdlib.h>
#include <stdbool.h>

#define HEAP_SIZE 0x10000

extern char kernel_end;

static volatile u8* heap_start;
static volatile u8* heap_end;
static volatile u8* heap_current;

int atoi(const char* str) {
    int n = 0, s = 1;

    while (*str == ' ' || *str == '\t' || *str == '\n') str++;
    if (*str == '-' || *str == '+') s = (*str++ == '-') ? -1 : 1;

    while (*str >= '0' && *str <= '9')
        n = n * 10 + (*str++ - '0');

    return s * n;
}

void itoa(int num, char* str) {
    int i = 0;
    int isNegative = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    while (num != 0) {
        int digit = num % 10;
        str[i++] = '0' + digit;
        num = num / 10;
    }

    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}


void __malloc_init__(void) {
    const uintptr_t ptr = (uintptr_t)kernel_end;
    heap_start = (u8*)ptr;
    heap_end = heap_start + HEAP_SIZE;
    heap_current = heap_start;
}

void* malloc(size size) {
    if (heap_current + size > heap_end) {
        // memory cant be allocated
        return nullptr;
    } else {
        void* cur = (void*)heap_current;
        heap_current += size;
        return cur;
    }
}
