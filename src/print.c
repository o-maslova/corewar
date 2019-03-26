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

void		create_rainbow_array(t_core *a)
{
	int i;
	int j;
	char *str;
	char **arr;

	i = 0;
	str = "52 124 196 160 161 203 202 166 208 214 221 220 178 184 \
		148 34 82 85 87 81 75 69 27 21 20 57 56 55 91 92 54 53";
	arr = ft_strsplit(str, ' ');
	while (i < MAINW_ROWS / 2)
	{
		VIS->rnbw[i] = ft_atoi(arr[i]);
		free(arr[i]);
		i++;
	}
	free(arr);
}

int		search_color(t_core *a, int color)
{
	int i;

	i = 0;
	while (i < MAINW_ROWS / 2)
	{
		if (VIS->rnbw[i] == color)
			return (i);
		i++;
	}
	return (-1);
}



void	rainbow(t_core *a, int color)
{
	int i;
	int j;
	int k;
	int pairs;
	int pos;
	int row;
	int that_color;

	j = -1;
	k = (a->last_say_live - 1) * PLAYER_FIELD;
	row = k / MAINW_ROWS - 1;
	pairs = 0;
	create_rainbow_array(a);
	pos = search_color(a, color) - 1;
	dprintf(g_fd, "pos = %d, k = %d\n\n", pos, k);
	while (++j < MEM_SIZE)
	{
		if (k == MEM_SIZE)
		{
			row = START_ROW - 1;
			k = 0;
		}
		if (k % MAINW_ROWS == 0 && pairs == 0)
		{
			++pos;
			usleep(500000);
			init_pair(pos, VIS->rnbw[pos], 16);
			pairs = 2;
		}
		if ((k % MAINW_ROWS) == 0)
		{
			wmove(VIS->main_win, ++row, 4);
			wrefresh(VIS->main_win);
			pairs--;
		}
		ELEM(k).color = pos;
		if (pos == (MAINW_ROWS / 2))
			pos = -1;
		that_color = ELEM(k).st ? COLOR_PAIR(ELEM(k).color)
		| A_BOLD | A_UNDERLINE : COLOR_PAIR(ELEM(k).color);
		wattron(VIS->main_win, that_color);
		wprintw(VIS->main_win, "%.2x", a->arena[k]);
		wattroff(VIS->main_win, that_color);
		waddch(VIS->main_win, ' ');
		k++;
	}
}

void raduga(t_core *a, int y)
{
	int column;
	int row;
	int i;

	row = HEIGTH + 8;
	column = 1;
	i = 4;
	VIS->raduga = newwin(24, 200, HEIGTH - 1, 0);
	dprintf(g_fd, "NORM 1\n");
	make_frame(VIS->raduga, COLOR_PAIR(FRAME));
	while (column < 256)
	{
		if (column % 32 == 0 || column == 1)
		{
			wmove(VIS->raduga, (row += 2), 4);
			i = 4;
		}
		// init_pair(column, column, 0);
		// wattron(VIS->raduga, COLOR_PAIR(column));
		// wprintw(VIS->raduga, "%d", column);
		// // wprintw(VIS->raduga, "*");
		// waddch(VIS->raduga, ' ');
		// wattroff(VIS->raduga, COLOR_PAIR(column));
		column++;
	}
	dprintf(g_fd, "NORM 3\n");
	wrefresh(VIS->raduga);
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
	// rainbow(a, VIS->p_colors[a->last_say_live - 1]);
	// raduga(a, row + 2);
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
