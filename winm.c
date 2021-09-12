#include "winm.h"

#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include "glob.h"
#include "screen.h"

editor_config window;

void disable_raw_mode()
{
   if (tcsetattr(STDIN_FILENO,TCSAFLUSH,&window.orig_term) == -1) 
       die("disable raw mode");
}

void enable_raw_mode() 
{
    if (tcgetattr(STDIN_FILENO, &window.orig_term) == -1)
        die("tcgetattr");

    atexit(disable_raw_mode);

    struct termios raw = window.orig_term;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) 
        die("tcsetattr");
}

int get_window_size(int *rows, int *cols) {
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return -1;
        return get_cursor_position(rows, cols);
    } else {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;
    }
}
