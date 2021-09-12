#include "screen.h"

#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#include "winm.h"
#include "input.h"

/*
 *  clear all of the screen
 */
void cls() 
{
    write(STDOUT_FILENO,"\x1b[2J",4);
}

/*
 *  write tiles into screen 
 */
void draw_rows() 
{
    int y;
    for (y = 0; y < window.screenrows; y++) {
        write(STDOUT_FILENO, "~\r\n", 3);
    }
}

/*
 *  refresh editor screen and print tiles and  ...
 */
void refresh_screen() 
{
    cls();
    write(STDOUT_FILENO, "\x1b[H", 3);

    draw_rows();

    write(STDOUT_FILENO, "\x1b[H", 3);
}

// cursor stuff

int get_cursor_position(int *rows, int *cols){
    char buf[32];
    unsigned int i = 0;
    if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) 
        return -1;
    while (i < sizeof(buf) - 1) {
        if (read(STDIN_FILENO, &buf[i], 1) != 1) 
            break;
        if (buf[i] == 'R') 
            break;
        i++;
    }
    buf[i] = '\0';
    if (buf[0] != '\x1b' || buf[1] != '[') 
        return -1;
    if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) 
        return -1;
    return 0;
}
