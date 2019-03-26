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

static char				*search_player(t_core *a, int num)
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
		mvwprintw(VIS->info_win, (*row += 2), 4, "Player -%d : ", tmp->number);
		wattron(VIS->info_win, COLOR_PAIR(VIS->clr[tmp->number - 1].st_clr));
		wprintw(VIS->info_win, "%.*s", tmp->prog_name);
		wattroff(VIS->info_win, COLOR_PAIR(VIS->clr[tmp->number - 1].st_clr));
		mvwprintw(VIS->info_win, ++(*row), 6, "Last live :\t\t\t%-*d",
		CLEAR_LINE, a->n[i]);
		mvwprintw(VIS->info_win, ++(*row), 6,
		"Lives in current period :\t\t%-*d", CLEAR_LINE, a->live_in_p[i++]);
		tmp = tmp->next;
	}
}

static void				print_info2(t_core *a, int row)
{
	print_players(a, &row);
	mvwprintw(VIS->info_win, (row += 2), 4, "CYCLE_TO_DIE :\t%-*d",
	CLEAR_LINE, a->cycle_to_die);
	mvwprintw(VIS->info_win, (row += 2), 4, "CYCLE_DELTA :\t%-*d",
	CLEAR_LINE, CYCLE_DELTA);
	mvwprintw(VIS->info_win, (row += 2), 4, "NBR_LIVE :\t\t%-*d",
	CLEAR_LINE, NBR_LIVE);
	mvwprintw(VIS->info_win, (row += 2), 4, "MAX_CHECKS :\t%-*d",
	CLEAR_LINE, MAX_CHECKS);
	if (a->carrs_num == 0)
	{
		mvwprintw(VIS->info_win, (row += 2), 4, "The winner is :\t");
		wattron(VIS->info_win,
		COLOR_PAIR(VIS->clr[a->last_say_live - 1].st_clr));
		wprintw(VIS->info_win, "%s", search_player(a, a->last_say_live));
		wattroff(VIS->info_win,
		COLOR_PAIR(VIS->clr[a->last_say_live - 1].st_clr));
		mvwprintw(VIS->info_win, (row += 2), 4, "Press any key to finish");
	}
}

void					print_info_frame(t_core *a)
{
	int		row;
	int		i;

	row = START_ROW + 4;
	i = -1;
	wattron(VIS->info_win, A_BOLD);
	mvwprintw(VIS->info_win, START_ROW, 4,
	"%-*s", CLEAR_LINE, (VIS->if_run) ? "** RUNNING **" : "** PAUSED **");
	mvwprintw(VIS->info_win, row, 4, "Cycles/second limit :\t%-*d",
	CLEAR_LINE, VIS->c_per_s);
	mvwprintw(VIS->info_win, (row += 3), 4, "Cycle :\t\t%-*d",
	CLEAR_LINE, a->n_cycles);
	mvwprintw(VIS->info_win, (row += 2), 4, "Processes :\t\t%-*d",
	CLEAR_LINE, a->carrs_num);
	print_info2(a, row);
	wrefresh(VIS->info_win);
}
