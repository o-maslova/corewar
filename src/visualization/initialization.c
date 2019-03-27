/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 13:16:29 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/26 13:16:31 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualization.h"

void				make_frame(WINDOW *win, int color)
{
	wattron(win, color | A_BOLD);
	wborder(win, BCHAR, BCHAR, BCHAR, BCHAR, BCHAR, BCHAR, BCHAR, BCHAR);
	wattroff(win, color | A_BOLD);
}

static void			fill_the_array(t_core *a)
{
	int			indx;
	int			clr_indx;
	int			num_of_pair;

	indx = -1;
	clr_indx = 0;
	num_of_pair = 210;
	while (++indx < COLOR_NUM)
	{
		num_of_pair += 5;
		CLR(indx).c_clr = num_of_pair++;
		init_pair(CLR(indx).c_clr, VIS->p_colors[COLOR_NUM],
		VIS->p_colors[clr_indx]);
		CLR(indx).st_clr = num_of_pair++;
		init_pair(CLR(indx).st_clr, VIS->p_colors[clr_indx],
		VIS->p_colors[COLOR_NUM]);
		CLR(indx).live_clr = num_of_pair;
		init_pair(CLR(indx).live_clr, COLOR_WHITE, VIS->p_colors[clr_indx]);
		clr_indx++;
	}
}

static void			create_col_pairs(t_core *a)
{
	VIS->p_colors[0] = COLOR_LRED;
	VIS->p_colors[1] = COLOR_GREEEN;
	VIS->p_colors[2] = COLOR_BIRUSA;
	VIS->p_colors[3] = COLOR_PURPLE;
	VIS->p_colors[4] = 8;
	VIS->p_colors[5] = COLOR_BLACK;
	fill_the_array(a);
}

static void			put_player_colors(t_core *a)
{
	int			i;
	int			step;
	t_player	*tmp;

	i = 0;
	tmp = a->players;
	step = 0;
	while (i < MEM_SIZE)
	{
		while (tmp && i < tmp->length + step)
			VIS->print[i++].default_clr = CLR(tmp->number - 1).st_clr;
		if (tmp)
		{
			step += PLAYER_FIELD;
			tmp = tmp->next;
		}
		if (!tmp && a->num_pl % 2 != 0)
			step++;
		while (i < step)
			VIS->print[i++].default_clr = CLR(COLOR_NUM - 1).st_clr;
	}
}

void				initialize(t_core *a)
{
	VIS = (t_win *)ft_memalloc(sizeof(t_win));
	VIS->if_run = false;
	VIS->vremya = clock();
	VIS->c_per_s = ST_CYC_PER_SEC;
	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	cbreak();
	noecho();
	start_color();
	init_pair(FRAME, COLOR_OHRA, COLOR_OHRA);
	VIS->main_win = newwin(HEIGTH, MAIN_WDTH, 0, 0);
	make_frame(VIS->main_win, COLOR_PAIR(FRAME));
	VIS->info_win = newwin(HEIGTH, INFO_WDTH, 0, MAIN_WDTH - 1);
	make_frame(VIS->info_win, COLOR_PAIR(FRAME));
	create_col_pairs(a);
	put_player_colors(a);
	pass_cycle(a);
	refresh();
}
