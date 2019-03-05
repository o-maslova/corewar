#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <ncurses.h>
#include "typedef.h"
#include "op.h"

#define CLEAR_LINE		20

#define BCHAR			'*'
#define HEIGTH			(MEM_SIZE / 64 + 4)
#define MAIN_WDTH		(64 * 3 + 7)
#define INFO_WDTH		(MAIN_WDTH / 3)
#define COLOR_NUM		(MAX_PLAYERS + 1)

#define RUN				' '
#define ONE_CYCLE_PASS	's'

#define FRAME			1
#define COLOR_GREY		10
#define COLOR_VASIL		11
#define COLOR_ORANGE	12

#define START_ROW		2

int						g_fd;

struct					s_color
{
	short				c_clr;
	short				st_clr;
	short				live_clr;
	// short				c_pair;
	// short				st_pair;
	// short				live_pair;
};

struct					s_win
{
	bool				if_run;
	unsigned char		paint_arena[MEM_SIZE];
	t_color				clr[MAX_PLAYERS + 1];
	WINDOW				*main_win;
	WINDOW				*info_win;
};

void		put_colors(t_core *a);
void		put_player_colors(t_core *a);
void		initialize(t_core *a);
void		print_info_frame(t_core *a);
void		make_frame(WINDOW *win, int color);
void		destroy_win(WINDOW *local_win);
WINDOW		*create_newwin(int heigth, int width, int start_y, int start_x);

#endif