#include <stdio.h>
#include "stdlib.h"
#include <string.h>

#define BUF_SIZE 10
#define INIT_SIZE 25

int main() {
    char* buffer = malloc(INIT_SIZE * sizeof(char));
    char temp_buffer[BUF_SIZE];
    size_t cur_len = 0, all_len = INIT_SIZE, temp_len;

    do {
        fgets(temp_buffer,BUF_SIZE,stdin);
        temp_len = strlen(temp_buffer);

        if (cur_len + temp_len > all_len) {
            all_len *= 2;
            buffer = realloc(buffer, all_len);
        }

        strcpy(buffer + cur_len, temp_buffer);
        cur_len += temp_len;

    } while (temp_len == BUF_SIZE - 1 && temp_buffer[BUF_SIZE - 2] != '\n');

    printf("Hello, %s", buffer);
    return 0;
}
