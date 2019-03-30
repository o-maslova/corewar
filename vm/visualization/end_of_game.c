/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 22:39:16 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/30 22:39:19 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corelib.h"

void		delete_it(t_core *a)
{
	play_music(a, MUS_END);
	free(VIS);
	delwin(VIS->main_win);
	delwin(VIS->stat_win);
	delwin(VIS->info_win);
	endwin();
	system("clear");
	exit(0);
}

void		end_of_game(t_core *a, int ch, t_carriage *c)
{
	if (ch == EXIT)
		delete_it(a);
	ft_memset(VIS->rnbw, -1, (sizeof(short) * MAINW_ROWS / 2 + 1));
	print_side_frame(a);
	ch = wgetch(VIS->main_win);
	if (ch == RUN)
	{
		play_music(a, MUS_MAGIC);
		rainbow(a, VIS->p_colors[a->last_say_live - 1]);
		print_arena(a, FRAME);
		print_side_frame(a);
	}
	if ((ch = wgetch(VIS->main_win)))
		delete_it(a);
}
