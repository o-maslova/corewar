/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nechto.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 22:25:00 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/30 22:25:03 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corelib.h"

T_P			*find_place(T_P *cur, T_P *new_cur, short pos[MAX_PLAYERS], int num)
{
	while (cur)
	{
		if (pos[num] != 0 && cur->pos == pos[num])
		{
			new_cur->next = ft_memcpy(ft_memalloc(S_T_P), cur, S_T_P);
			new_cur = new_cur->next;
			return (new_cur);
		}
		else if (pos[num] == 0 && cur->number == -1)
		{
			cur->number = num + 1;
			new_cur->next = ft_memcpy(ft_memalloc(S_T_P), cur, S_T_P);
			new_cur = new_cur->next;
			return (new_cur);
		}
		cur = cur->next;
	}
	return (new_cur);
}

t_player	*player_numb(t_player *player, int *shitty, int t)
{
	t_player	*next_p;
	short		pos[MAX_PLAYERS];
	int			i;

	next_p = player->next;
	t = 0;
	ft_bzero(pos, sizeof(short) * MAX_PLAYERS);
	i = 0;
	while (next_p != NULL)
	{
		if (next_p->number > *shitty || next_p->number < 1)
			next_p->number = -1;
		else if (next_p->number != -1 && pos[next_p->number - 1] == 0)
			pos[next_p->number - 1] = next_p->pos;
		else if (next_p->number != -1 && pos[next_p->number - 1] != 0)
			next_p->number = -1;
		next_p = next_p->next;
	}
	player = move_p(player, player->next, pos, *shitty);
	return (player);
}

void		start_game(t_player *pl, int *shitty, int *dump)
{
	if (!pl->next)
		ft_error(pl, 4, "Hey, where are the fighters?");
	pl = player_numb(pl, shitty, 1);
	if (*shitty == -1)
		ft_error(pl, 4, "malloc error 2");
	if (*shitty > MAX_PLAYERS)
		ft_error(pl, 4, "Error: too many players");
	do_this(pl, *shitty, dump);
}

void		check_args(int argc, char **argv, t_player *pl, int *dump)
{
	int	i;
	int	fln;
	int	t;

	i = 0;
	t = 0;
	while (++i < argc)
	{
		fln = typeofarg(argv[i], &t, -1, pl);
		if (fln == 2 && i + 2 < argc)
		{
			fln = flag_n(argv, ++i, &t, pl);
			i++;
		}
		dump[1] = (fln == 8) ? 1 : dump[1];
		if (fln == 4 && i + 1 < argc)
			dump[0] = flag_d(argv, ++i);
		else if (fln == 5 || (fln == 4 && i + 1 >= argc))
			ft_error(pl, 4, "flag -d not valid");
		else if (fln == 3 || (fln == 2 && i + 2 >= argc))
			ft_error(pl, 4, "flag -n not valid");
		else if (fln == -1)
			ft_error(pl, t, argv[i]);
	}
	start_game(pl, &t, dump);
}
