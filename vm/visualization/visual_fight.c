/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_fight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 22:39:32 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/30 22:39:35 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corelib.h"

void		print_cycle(t_core *a, int first_step, t_carriage *c)
{
	int			o;

	a->carrs_num = 0;
	c = a->carrs;
	a->n_cycles = a->n_cycles + first_step;
	while (c)
	{
		o = carret(c, a, a->arena);
		c = c->next;
		a->carrs_num++;
	}
	check_cycles(a);
	if (first_step == 0)
		play_music(a, MUS_FIGHT);
	if (VIS->one_cycle)
	{
		VIS->if_run = true;
		print_side_frame(a);
	}
	put_colors(a);
	print_arena(a, FRAME);
}

int			check_cyc_per_sec(t_core *a, char ch)
{
	if (!VIS->music.is_start)
		system("pkill afplay");
	if (ch == MINUS_BIG)
		VIS->c_per_s -= BIG_STEP;
	if (ch == PLUS_BIG)
		VIS->c_per_s += BIG_STEP;
	if (ch == MINUS_SMALL)
		VIS->c_per_s -= SMALL_STEP;
	if (ch == PLUS_SMALL)
		VIS->c_per_s += SMALL_STEP;
	(VIS->c_per_s < 1) && (VIS->c_per_s = 1);
	(VIS->c_per_s > 1000) && (VIS->c_per_s = 1000);
	return (1);
}

void		print_arena(t_core *a, int frame)
{
	int		i;
	int		row;
	int		that_color;

	i = -1;
	frame = 0;
	row = START_ROW - 1;
	while (++i < MEM_SIZE)
	{
		if ((i % MAINW_ROWS) == 0)
			wmove(VIS->main_win, ++row, 4);
		that_color = ELEM(i).st ? COLOR_PAIR(ELEM(i).color)
		| A_BOLD | A_UNDERLINE : COLOR_PAIR(ELEM(i).color);
		wattron(VIS->main_win, that_color);
		wprintw(VIS->main_win, "%.2x", a->arena[i]);
		wattroff(VIS->main_win, that_color);
		waddch(VIS->main_win, ' ');
	}
	wrefresh(VIS->main_win);
}

void		visual_fight(t_core *a, t_carriage *c)
{
	int			ch;

	system("clear");
	initialize(a);
	print_cycle(a, 0, c);
	while ((ch = getch()) != EXIT && a->cycle_to_die > 0 && a->carrs)
	{
		VIS->music.is_start = ch == TURNOFF_MUS ? false : true;
		if (ch == RUN)
			VIS->if_run = !VIS->if_run;
		else if (ch == ONE_CYCLE_PASS)
		{
			VIS->one_cycle = true;
			print_cycle(a, 1, c);
			(VIS->if_run = false) && (!VIS->one_cycle);
		}
		if (VIS->if_run && clock() >= SHOW_REGULATOR)
		{
			VIS->vremya = clock();
			print_cycle(a, 1, c);
		}
		check_cyc_per_sec(a, ch);
		print_side_frame(a);
	}
	end_of_game(a, ch);
}
