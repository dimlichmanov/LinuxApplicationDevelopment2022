#include "ncurses.h"
#include <sys/stat.h>
#include "stdlib.h"
#include "unistd.h"
#include "fcntl.h"
#include "string.h"
#include "locale.h"

#define margin 3

int main(int argc, char **argv) {
    WINDOW *display;
    int n,  fd, W, H, done, num_strings = 0;
    char *buf;
    char **strings;
    size_t len;

    struct stat info;
    stat(argv[1], &info);
    len = info.st_size;
    buf = malloc(len+2);
    buf[len] = '\n';

    fd = open(argv[1], O_RDONLY);
    read(fd, buf, len*sizeof(char));

    for (int i = 0; i < len; i++) {
        if (buf[i] == '\n') {
            num_strings++;
        }
    }
    num_strings++;
    close(fd);

    strings = (char**)malloc((num_strings + 1) * sizeof(char*));
    strings[0] = &buf[0];
    int j = 1;

    for (int i = 0; i < len; i++) {
        if (buf[i] == '\n') {
            strings[j] = &buf[i + 1];
            j++;
            if (j == num_strings) {
                break;
            }
        }
    }
    strings[num_strings] = &buf[len];

    for (int h = 0; h < num_strings; h++) {
        char* temp = strings[h];
        int curr_size = strings[h + 1] - strings[h];
        strings[h] = (char*)malloc((curr_size + 1) * sizeof(char));
        strings[h][curr_size] = '\0';
        memcpy(strings[h], temp, curr_size*sizeof(char));
    }

    free(buf);

    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();

    W = COLS - 2 * margin;
    H = LINES - 2 * margin;
    printw("File: %s", argv[1]);

    curs_set(0);
    refresh();
    display = newwin(H, W, margin, margin);
    keypad(display, TRUE);
    scrollok(display, TRUE);
    n = 0; //topper string
    done = FALSE;

    do {
        werase(display);
        for (int i = 0; (i + n < num_strings) && (i < H); i++) {
            mvwprintw(display, i+2, 2, "%s", strings[n + i]);
        }
        box(display, 0, 0);
        wrefresh(display);
        switch(wgetch(display)) {
            case 27:done = TRUE; break;
            case KEY_DOWN: n = n < num_strings - 1 ? n+1 : n; break;
            case KEY_UP: n = n > 0 ? n-1 : n; break;
        }
    } while (!done);

    endwin();

    for (int h = 0; h < num_strings; h++) {
        free(strings[h]);
    }
    free(strings);
}