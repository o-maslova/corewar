/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmediany <bmediany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 10:38:35 by bmediany          #+#    #+#             */
/*   Updated: 2019/02/01 10:38:36 by bmediany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corelib.h"

void		ft_error(t_player *p, int t, char *s)
{
	free_p(p);
	if (t == 0)
		ft_printf("Error: file %s must have .cor type\n", s);
	if (t == 1)
		ft_printf("Error: file %s not valide\n", s);
	if (t == 3)
		ft_printf("Error: exec code file %s not valide\n", s);
	if (t == 4)
		ft_printf("Error: %s\n", s);
	if (t < 0)
		ft_printf("Error: can't find file %s, or access is denied\n", s);
	exit(0);
}

t_core		*make_core(t_carriage *c, US_CHAR *s, t_player *p, int *d)
{
	t_core	*a;

	if (!(a = ft_memalloc(sizeof(t_core))))
		free_c(p, c, "malloc error");
	a->arena = s;
	a->visual_flag = d[1];
	a->dump = d[0];
	a->cycle_to_die = CYCLE_TO_DIE;
	make_core2(a);
	a->players = p;
	a->carrs = c;
	return (a);
}

void		do_this(t_player *p, int t, int *d)
{
	t_carriage	*c;
	t_core		*arena;
	US_CHAR		a[MEM_SIZE];

	ft_bzero(a, MEM_SIZE);
	c = make_carret(a, p, NULL, t);
	arena = make_core(c, a, p, d);
	arena->num_pl = t;
	arena->last_say_live = t;
	if (arena->visual_flag == 1)
		visual_fight(arena, c);
	else
		fight(arena, c);
}

int			main(int ac, char **av)
{
	int			dump[2];
	t_player	*player;

	dump[0] = -1;
	dump[1] = -1;
	if (ac < 2)
		printf("Error: no arguments\n");
	else if (ac > MAX_ARGS_NUMBER + 1)
		printf("Error: t00 many arguments\n");
	else
	{
		player = creat_player(NULL, -1, NULL);
		check_args(ac, av, player, dump);
	}
	return (0);
}
