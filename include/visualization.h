#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <ncurses.h>
#include <time.h>
#include "typedef.h"
#include "op.h"

#define CLEAR_LINE		20
#define CYCLE_PER_SEC	((a->visual->end - a->visual->start) / CLOCKS_PER_SEC)

#define BCHAR			'*'
#define HEIGTH			(MEM_SIZE / 64 + 4)
#define MAIN_WDTH		(64 * 3 + 7)
#define INFO_WDTH		(MAIN_WDTH / 3)
#define COLOR_NUM		(MAX_PLAYERS + 1)

#define RUN				' '
#define ONE_CYCLE_PASS	's'
#define MINUS_BIG		'q'
#define MINUS_SMALL		'w'
#define PLUS_BIG		'r'
#define PLUS_SMALL		'e'

#define DUMP			'x' //need to delete

#define SMALL_STEP		1
#define BIG_STEP		10

#define FRAME			100
#define COLOR_GREY		80
#define COLOR_LGREY		145
#define COLOR_PURPLE	90
#define COLOR_LPURPLE	140
#define COLOR_LRED		160
#define COLOR_OHRA		178
#define COLOR_ROSE		132
#define COLOR_FUCSIA	126
#define COLOR_BURGUNDI	89
#define COLOR_BIRUSA	30
#define COLOR_LEMON		184
#define COLOR_NBLUE		81
#define COLOR_LBLUE		159
#define COLOR_LIME		154
#define COLOR_LBROWN	130
#define COLOR_VASIL		111
#define COLOR_PINK		200
#define YEL				1



#define START_ROW		2

int						g_fd;

struct					s_color
{
	short				c_clr;
	short				st_clr;
	short				live_clr;
};

struct					s_paint
{
	short				not_in_field;
	short				is_st;
	short				i_live;
	short				color;
	short				default_clr;
};


struct					s_win
{
	bool				if_run;
	clock_t				start;
	clock_t				end;
	int					c_per_s; // cycle per second
	t_paint				paint_arena[MEM_SIZE];
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