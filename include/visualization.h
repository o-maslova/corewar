/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 13:33:58 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/26 13:34:02 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZATION_H
# define VISUALIZATION_H

# include <curses.h>
# include <time.h>
# include "corelib.h"

# define CLEAR_LINE		20
# define SHOW_REGULATOR	(VIS->vremya + CLOCKS_PER_SEC / (VIS->c_per_s * 2))

# define BCHAR			'*'
# define MAINW_ROWS		64
# define PLAYER_FIELD	(MEM_SIZE / a->num_pl)
# define HEIGTH			(MEM_SIZE / MAINW_ROWS + 4)
# define MAIN_WDTH		(MAINW_ROWS * 3 + 7)
# define INFO_WDTH		(MAIN_WDTH / 3)
# define COLOR_NUM		(MAX_PLAYERS + 1)

# define RUN				' '
# define ONE_CYCLE_PASS		's'
# define MINUS_BIG			'q'
# define MINUS_SMALL		'w'
# define PLUS_BIG			'r'
# define PLUS_SMALL			'e'

# define SMALL_STEP			1
# define BIG_STEP			10
# define ST_CYC_PER_SEC		50
# define FOR_VISUAL			(VIS->c_per_s / 10)
# define ELEM(i)			(VIS->print[i])
# define CLR(i)				(VIS->clr[i])

# define FRAME				100
# define COLOR_GREY			80
# define COLOR_LGREY		145
# define COLOR_PURPLE		91
# define COLOR_LPURPLE		140
# define COLOR_LRED			160
# define COLOR_OHRA			178
# define COLOR_ROSE			132
# define COLOR_FUCSIA		126
# define COLOR_BURGUNDI		89
# define COLOR_BIRUSA		69
# define COLOR_GREEEN		34
# define COLOR_NBLUE		81
# define COLOR_LBLUE		159
# define COLOR_LIME			154
# define COLOR_LBROWN		130
# define COLOR_VASIL		111
# define COLOR_PINK			200
# define YEL				1

# define START_ROW			2

int						g_fd;

struct			s_color
{
	short				c_clr;
	short				st_clr;
	short				live_clr;
};

struct			s_paint
{
	short				in_field;
	short				st;
	short				live;
	short				color;
	short				default_clr;
};
struct			s_win
{
	bool				if_run;
	clock_t				vremya;
	int					c_per_s; // cycle per second
	short				rnbw[MAINW_ROWS / 2];
	short				p_colors[COLOR_NUM + 1];
	t_paint				print[MEM_SIZE];
	t_color				clr[MAX_PLAYERS + 1];
	WINDOW				*main_win;
	WINDOW				*info_win;
	WINDOW				*raduga;
};

void			put_colors(t_core *a);
void			initialize(t_core *a);
void			print_info_frame(t_core *a);
void			make_frame(WINDOW *win, int color);
void			destroy_win(WINDOW *local_win);
void			rainbow(t_core *a, int color);
WINDOW			*create_newwin(int heigth, int width, int start_y, int start_x);

#endif
