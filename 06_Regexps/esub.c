#include "regex.h"
#include <stdio.h>
#include "string.h"
#include <ctype.h>
#include "math.h"
#include <stdlib.h>
#include "stdbool.h"
#define MAX_POCKET 20

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void print_pocket(int begin, int end, char * string) {
    for (int i = begin; i < end; i++) {
        putc(string[i], stdout);
    }
}


int main(int argc, char **argv) {
    if (argc < 4) {
        puts("Wrong usage of esub tool");
    }

    char *regexp = argv[1], *substitution = argv[2], *string = argv[3];
    regex_t regex;
    char errbuf[100];
    int err;

    if (0 != (err = regcomp(&regex, regexp, REG_EXTENDED))) {
      regerror(err, &regex, errbuf, 100);
      printf("regcomp() failed with '%s'\n", errbuf);
      exit(EXIT_FAILURE);
   }

    regmatch_t pm[MAX_POCKET];
    err = regexec(&regex, string, MAX_POCKET, pm, 0);

    for (int i = 0; i < MIN(pm[0].rm_so, strlen(string)); i++) {
        putc(string[i], stdout);
    }
    if (err == REG_NOMATCH) {
        putc('\n', stdout);
    }

    bool esc_status = false;
    if (err != REG_NOMATCH) {
    for (char *str = substitution; *str != '\0'; str++) {
        if (*str=='\\' && !esc_status) {
            esc_status = 1;
            continue;
        }
        if (isdigit(*str) && esc_status) {
            if (pm[atoi(str)].rm_so == -1 ) {
                printf("BAD POCKET INDEX\n");
                regfree(&regex);
                return -1;
            }
            print_pocket(pm[atoi(str)].rm_so, pm[atoi(str)].rm_eo, string);
            esc_status = 0;
            continue;
        }
        if (*str=='\\' && esc_status) {
            putc(*str, stdout);
            esc_status = 0;
            continue;
        }
        if (esc_status) {
            esc_status = 0;
            switch (*str) {
                case '\'':
                    putc('\'', stdout);
                    continue;
                case '\"':
                    putc('\"', stdout);
                    continue;
                case 'a':
                    putc('\a', stdout);
                    continue;
                case 'b':
                    putc('\b', stdout);
                    continue;
                case 'e':
                    putc('\e', stdout);
                    continue;
                case 'f':
                    putc('\f', stdout);
                    continue;
                case 'n':
                    putc('\n', stdout);
                    continue;
                case 'r':
                    putc('\r', stdout);
                    continue;
                case 't':
                    putc('\t', stdout);
                    continue;
                case 'v':
                    putc('\v', stdout);
                    continue;
            }
        }
        putc(*str, stdout);
    }

    if (esc_status) {
        printf("\nBAD SUBSTITUTE, abort...\n");
        regfree(&regex);
        return -1;
    }
    
    for (int i = pm[0].rm_eo; i < strlen(string); i++) {
        putc(string[i], stdout);
    }
    putc('\n',stdout);
    }
    regfree(&regex);
    return 0;

}
