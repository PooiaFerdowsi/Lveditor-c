#ifndef WINM_H
# define WINM_H

#include <termio.h>

struct editor_conf_t {
    int screenrows;
    int screencols;
    struct termios orig_term;
};

typedef struct editor_conf_t editor_config;

extern editor_config window;

void disable_raw_mode();
void enable_raw_mode();

int get_window_size(int *, int *);

short check_window_size();

#endif
