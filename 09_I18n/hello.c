#include <stdio.h>
#include <stdlib.h>

#include <libintl.h>
#include <locale.h>
#include <string.h>
#include <libgen.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "po"

int find_middle(int a, int b) {
    return ((a+b)/2);
}

int main()
{
    /* Setting the i18n environment */
    setlocale (LC_ALL, "");
    bindtextdomain ("hello", LOCALE_PATH);
    textdomain ("hello");

    printf(_("Set in mind a number between 1 and 100\n"));
    int lower_bound = 1;
    int upper_bound = 100;

    while (1) {
        if (lower_bound == 99) {
            break;
        }
        if (lower_bound == upper_bound || ((lower_bound + 1) == upper_bound)) {
            printf(_("I have guessed. Your number is %d !!\n"), upper_bound - 1);
            break;
        }
        int mid = find_middle(lower_bound, upper_bound);
        printf(_("Is your number more or equal than %d ?\n"), mid);
        char ch = getchar();
        char a[2];
        a[0] = ch;
        a[1] = '\0';
        if (!strcmp(a, _("y"))) {
            lower_bound = mid;
        } else {
            upper_bound = mid;
        }
        ch = getchar();
    } 

    if (lower_bound == 99) {
        printf(_("Is your number more or equal than %d ?\n"), 100);
        char ch = getchar();
        char a[2];
        a[0] = ch;
        a[1] = '\0';
        if (!strcmp(a, _("y"))) {
            printf(_("I have guessed. Your number is %d !!\n"), 100);
        } else {
            printf(_("I have guessed. Your number is %d !!\n"), 99);
        }
        ch = getchar();
    }

    return EXIT_SUCCESS;
}
