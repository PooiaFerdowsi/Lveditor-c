#include "lv.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <ctype.h>
#include <errno.h>

#include "winm.h"
#include "basics.h"
#include "glob.h"
#include "input.h"
#include "screen.h"

/* 
 *  get an key from input and process it
 */
void process_key() 
{
    char c = read_key();

    switch (c) {
        case CTRL_KEY('q'):
            exit(0);
            break;
    }
}

/*
 * initialize basic variables of editor such as screen cols and rows and buffer and ...
 */
void init_editor()
{
    if (get_window_size(&window.screenrows,&window.screencols))
        die("windows");
}

int main() 
{

    enable_raw_mode();
    init_editor();

    while (1) {
        refresh_screen();
        process_key();
    }
    return 0;
}
