#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

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
