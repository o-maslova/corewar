#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <ncurses.h>

#define BCHAR			'*'
#define FRAME			1

void		make_frame(WINDOW *win);
void		destroy_win(WINDOW *local_win);
WINDOW		*create_newwin(int heigth, int width, int start_y, int start_x);

#endif