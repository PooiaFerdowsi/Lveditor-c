#include "glob.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "screen.h"

/*
 *  clear screen and set cursor to 0 and then print errors and finally exit
 */
void die(const char *s) {
    cls();
    write(STDOUT_FILENO, "\x1b[H", 3);

    perror(s);
    exit(1);
}
