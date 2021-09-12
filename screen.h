#ifndef SCREEN_H
# define SCREEN_H

void cls();
void draw_rows();
void refresh_screen();

// cursor stuff
int get_cursor_position(int *,int *);

#endif
