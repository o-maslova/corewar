/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 13:16:42 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/26 13:16:48 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualization.h"

char				*search_player(t_core *a, int num)
{
	t_player	*tmp;

	tmp = a->players;
	while (tmp)
	{
		if (tmp->number == num)
			return (tmp->prog_name);
		tmp = tmp->next;
	}
	return (NULL);
}

static void				print_players(t_core *a, int *row)
{
	int			i;
	t_player	*tmp;

	i = 0;
	tmp = a->players;
	while (tmp)
	{
		mvwprintw(VIS->stat_win, (*row += 2), 4, "Player -%d : ", tmp->number);
		wattron(VIS->stat_win, COLOR_PAIR(VIS->clr[tmp->number - 1].st_clr));
		wprintw(VIS->stat_win, "%.*s", tmp->prog_name);
		wattroff(VIS->stat_win, COLOR_PAIR(VIS->clr[tmp->number - 1].st_clr));
		mvwprintw(VIS->stat_win, ++(*row), 6, "Last live :\t\t\t%-*d",
		CLEAR_LINE, a->n[i]);
		mvwprintw(VIS->stat_win, ++(*row), 6,
		"Lives in current period :\t\t%-*d", CLEAR_LINE, a->live_in_p[i++]);
		tmp = tmp->next;
	}
}

// void raduga(t_core *a, int y)
// {
// 	int column;
// 	int row;
// 	int i;

// 	row = HEIGTH + 8;
// 	column = 1;
// 	i = 4;
// 	VIS->raduga = newwin(24, 200, HEIGTH - 1, 0);
// 	make_frame(VIS->raduga, COLOR_PAIR(FRAME));
// 	while (column < 256)
// 	{
// 		if (column % 32 == 0 || column == 1)
// 		{
// 			wmove(VIS->raduga, (row += 2), 4);
// 			i = 4;
// 		}
// 		init_pair(column, column, 0);
// 		wattron(VIS->raduga, COLOR_PAIR(column));
// 		wprintw(VIS->raduga, "%d", column);
// 		waddch(VIS->raduga, ' ');
// 		wattroff(VIS->raduga, COLOR_PAIR(column));
// 		column++;
// 	}
// 	wrefresh(VIS->raduga);
// }

static void				print_info(t_core *a)
{
	int row;

	row = START_ROW - 1;
	wattron(VIS->info_win, A_BOLD | A_UNDERLINE);
	mvwprintw(VIS->info_win, (row += 2), 4, "To operate cycles/second limit:");
	wattroff(VIS->info_win, A_BOLD | A_UNDERLINE);
	wattron(VIS->info_win, A_BOLD);
	mvwprintw(VIS->info_win, (row += 2), 4, "q - reduce by \t%-*d",
	CLEAR_LINE, BIG_STEP);
	mvwprintw(VIS->info_win, (row += 2), 4, "w - reduce by \t%-*d",
	CLEAR_LINE, SMALL_STEP);
	mvwprintw(VIS->info_win, (row += 2), 4, "e - increase by \t%-*d",
	CLEAR_LINE, SMALL_STEP);
	mvwprintw(VIS->info_win, (row += 2), 4, "r - increase by \t%-*d",
	CLEAR_LINE, BIG_STEP);
	mvwprintw(VIS->info_win, (row += 4), 4, "To pass one cycle press 's'");
}

static void				print_static(t_core *a, int row)
{
	print_players(a, &row);
	mvwprintw(VIS->stat_win, (row += 2), 4, "CYCLE_TO_DIE :\t%-*d",
	CLEAR_LINE, a->cycle_to_die);
	mvwprintw(VIS->stat_win, (row += 2), 4, "CYCLE_DELTA :\t%-*d",
	CLEAR_LINE, CYCLE_DELTA);
	mvwprintw(VIS->stat_win, (row += 2), 4, "NBR_LIVE :\t\t%-*d",
	CLEAR_LINE, NBR_LIVE);
	mvwprintw(VIS->stat_win, (row += 2), 4, "MAX_CHECKS :\t%-*d",
	CLEAR_LINE, MAX_CHECKS);
	if (a->cycle_to_die < 0)
	{
		mvwprintw(VIS->stat_win, (row += 2), 4, "The winner is :\t");
		wattron(VIS->stat_win,
		COLOR_PAIR(VIS->clr[a->last_say_live - 1].st_clr));
		wprintw(VIS->stat_win, "%s", search_player(a, a->last_say_live));
		wattroff(VIS->stat_win,
		COLOR_PAIR(VIS->clr[a->last_say_live - 1].st_clr));
		mvwprintw(VIS->stat_win, (row += 4), 4, "%-*s", CLEAR_LINE,
		(VIS->rnbw[0] < 0) ? "...wait for magic..." : "Press any key to finish");
	}
}

void					print_side_frame(t_core *a)
{
	int		row;

	row = START_ROW + 4;
	print_info(a);
	wattron(VIS->stat_win, A_BOLD);
	mvwprintw(VIS->stat_win, START_ROW, 4,
	"%-*s", CLEAR_LINE, (VIS->if_run) ? "** RUNNING **" : "** PAUSED **");
	mvwprintw(VIS->stat_win, row, 4, "Cycles/second limit :\t%-*d",
	CLEAR_LINE, VIS->c_per_s);
	mvwprintw(VIS->stat_win, (row += 3), 4, "Cycle :\t\t%-*d",
	CLEAR_LINE, a->n_cycles);
	mvwprintw(VIS->stat_win, (row += 2), 4, "Processes :\t\t%-*d",
	CLEAR_LINE, a->carrs_num);
	print_static(a, row);
	wrefresh(VIS->info_win);
	wrefresh(VIS->stat_win);
}
