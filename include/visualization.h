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

/*
** Macroses
*/

# define SHOW_REGULATOR	(VIS->vremya + CLOCKS_PER_SEC / (VIS->c_per_s))
# define ELEM(i)		(VIS->print[i])
# define CLR(i)			(VIS->clr[i])

/*
** Frames' defines
*/

# define BCHAR			'*'
# define START_ROW		2
# define CLEAR_LINE		25
# define MAINW_ROWS		64
# define PLAYER_FIELD	(MEM_SIZE / a->num_pl)
# define HEIGTH			(MEM_SIZE / MAINW_ROWS + 4)
# define MAIN_WDTH		(MAINW_ROWS * 3 + 7)
# define INFO_WDTH		(MAIN_WDTH / 3)
# define STAT_HGTH		(((HEIGTH - 4) / 4) * 3)
# define INFO_HGTH		(HEIGTH - STAT_HGTH + 1)
# define COLOR_NUM		(MAX_PLAYERS + 1)

/*
** Keys for managing
*/

# define RUN				' '
# define ONE_CYCLE_PASS		's'
# define MINUS_BIG			'q'
# define MINUS_SMALL		'w'
# define PLUS_BIG			'r'
# define PLUS_SMALL			'e'
# define EXIT				27

# define SMALL_STEP			1
# define BIG_STEP			10
# define ST_CYC_PER_SEC		50

/*
** Defines for colors
*/

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

# define MUS_FIGHT			1
# define MUS_MAGIC			2
# define MUS_END			3

/*
** Structure for storing colors for operations
*/
struct			s_color
{
	short				c_clr;
	short				st_clr;
	short				live_clr;
};

/*
** Structure for painting arena
*/
struct			s_paint
{
	short				in_field;
	short				st;
	short				live;
	short				color;
	short				default_clr;
};

struct			s_music
{
	bool				is_start;
	char				*m_fight;
	char				*magic;
};

/*
** Structure for visualization
*/
struct			s_win
{
	bool				if_run;
	bool				one_cycle;
	clock_t				vremya;
	int					c_per_s;
	short				rnbw[MAINW_ROWS / 2 + 1];
	short				p_colors[COLOR_NUM + 1];
	t_paint				print[MEM_SIZE];
	t_color				clr[MAX_PLAYERS + 1];
	t_music				music;
	WINDOW				*main_win;
	WINDOW				*stat_win;
	WINDOW				*info_win;
};

void			put_colors(t_core *a);
void			initialize(t_core *a);
void			end_of_game(t_core *a, int ch, t_carriage *c);
void			delete_it(t_core *a);
void			print_side_frame(t_core *a);
void			make_frame(WINDOW *win, int color);
void			print_side_frame(t_core *a);
void			destroy_win(WINDOW *local_win);
void			rainbow(t_core *a, int color);
void			define_music(t_core *a);
void			play_music(t_core *a, int what_now);
char			*search_player(t_core *a, int num);
WINDOW			*create_newwin(int heigth, int width, int start_y, int start_x);

#endif
