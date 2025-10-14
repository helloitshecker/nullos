#include <string.h>

size strlen(const char* str) {
    size i = 0;
    while (str[i] != '\0') i++;
    return i;
}
