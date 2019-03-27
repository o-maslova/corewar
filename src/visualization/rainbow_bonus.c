/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rainbow_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 14:06:08 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/27 14:06:12 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualization.h"

static void			winner(t_core *a)
{
	int i;
	int j;
	int row;
	
	i = 0;
	j = 9;
	row = START_ROW - 1;
	init_pair(250, 16, 16);
	while (i < MEM_SIZE)
	{
		if (row >= 28 && row <= 35)
		{
			j--;
			while (i % MAINW_ROWS != 0)
			{
				ELEM(i).color = 250;
				ELEM(i + j).color = 250;
				i++;
			}
			usleep(200000);
			print_arena(a, FRAME);
		}
		if (i % MAINW_ROWS == 0)
			row++;
		i++;
		// if (row == 35)
		// {
		// 	wattron(VIS->main_win, CLR(a->last_say_live - 1).st_clr);
		// 	waddstr(VIS->main_win, row - 5, 30, search_player(a, a->last_say_live));
		// 	// wprintw(VIS->info_win, "%30s", search_player(a, a->last_say_live));
		// 	wattroff(VIS->main_win, CLR(a->last_say_live - 1).st_clr);
		// }
	}
}

static void			create_rainbow_array(t_core *a)
{
	int		i;
	int		j;
	char	*str;
	char	**arr;

	i = 0;
	str = "0 125 124 196 160 161 203 202 166 208 214 221 220 178 184 \
		148 34 82 85 87 81 75 69 27 21 20 57 56 55 91 92 54 161";
	arr = ft_strsplit(str, ' ');
	while (i < (MAINW_ROWS / 2 + 1))
	{
		VIS->rnbw[i] = ft_atoi(arr[i]);
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int			search_color(t_core *a, int color)
{
	int i;

	i = 0;
	while (i < (MAINW_ROWS / 2 + 1))
	{
		if (VIS->rnbw[i] == color)
			return (i);
		i++;
	}
	return (-1);
}

static int			coloring_cell(t_core *a, int k, int color, int *row)
{
	int i;
	int that_color;

	i = -1;
	while (++i < MAINW_ROWS * 2)
	{
		if ((i % MAINW_ROWS) == 0)
			wmove(VIS->main_win, (*row)++, 4);
		ELEM(k).color = color;
		that_color = ELEM(k).st ? COLOR_PAIR(ELEM(k).color)
		| A_BOLD | A_UNDERLINE : COLOR_PAIR(ELEM(k).color);
		wattron(VIS->main_win, that_color);
		wprintw(VIS->main_win, "%.2x", a->arena[k]);
		wattroff(VIS->main_win, that_color);
		waddch(VIS->main_win, ' ');
		k++;
	}
	if (k == MEM_SIZE)
	{
		k = 0;
		*row = START_ROW;
	}
	wrefresh(VIS->main_win);
	return (k);
}

void				rainbow(t_core *a, int color)
{
	int i;
	int k;
	int pos;
	int row;

	create_rainbow_array(a);
	k = (a->last_say_live - 1) * PLAYER_FIELD;
	if ((MEM_SIZE % a->num_pl) != 0)
		k += 43;
	row = k / MAINW_ROWS + 2;
	pos = search_color(a, color);
	i = 0;
	while (i < MEM_SIZE)
	{
		usleep(200000);
		init_pair(pos, VIS->rnbw[pos], 16);
		k = coloring_cell(a, k, pos++, &row);
		i += MAINW_ROWS * 2;
		if (pos == (MAINW_ROWS / 2 + 1))
			pos = 1;
	}
	usleep(500000);
	// winner(a);
	init_pair(FRAME, color, color);
	print_arena(a, FRAME);
}
