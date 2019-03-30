/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 22:25:58 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/30 22:26:01 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corelib.h"

void		introduction_dump(t_core *a)
{
	t_player	*player;

	ft_printf("Introducing contestants...\n");
	player = a->players;
	while (player)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		player->number, player->length, player->prog_name, player->comment);
		player = player->next;
	}
}

void		init_winner(t_core *a)
{
	t_player	*winner;

	winner = a->players;
	while (1)
	{
		if (winner->number == a->last_say_live)
			break ;
		winner = winner->next;
	}
	ft_printf("Contestant %d, \"%s\", has won !\n",
	winner->number, winner->prog_name);
}

void		print_arena_dump(t_core *a)
{
	int		i;
	int		row;

	row = 0;
	while (row * 64 < MEM_SIZE)
	{
		i = -1;
		ft_printf("%#06x :", row * 64);
		while (++i < 64)
		{
			ft_printf(" %02x", a->arena[i + (row * 64)]);
		}
		ft_printf(" \n");
		row++;
	}
}

void		print_cycle_dump(t_core *a, t_carriage *c, int type)
{
	int	o;

	a->carrs_num = 0;
	c = a->carrs;
	while (c)
	{
		o = carret(c, a, a->arena);
		c = c->next;
		a->carrs_num++;
	}
	check_cycles(a);
	if (type == 1 && (a->n_cycles == a->dump || a->dump == 0) &&
		a->carrs && a->cycle_to_die > 0)
		print_arena_dump(a);
	else if (type == 1)
		init_winner(a);
	a->n_cycles++;
}

void		fight(t_core *a, t_carriage *c)
{
	introduction_dump(a);
	a->visual_flag = 0;
	print_cycle_dump(a, c, 0);
	while (a->cycle_to_die > 0 && a->carrs &&
	(a->n_cycles < a->dump || a->dump < 0))
		print_cycle_dump(a, c, 0);
	print_cycle_dump(a, c, 1);
}
