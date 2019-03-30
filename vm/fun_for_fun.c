/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_for_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 22:18:41 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/30 22:18:46 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corelib.h"

int			ft_type_codage(t_core *arena, t_carriage *car, short *arg)
{
	int		i;
	int		error;

	i = 0;
	error = 0;
	while (i < arena->op_tab[car->f - 1].nb_args)
	{
		if (arg[i] == 0 ||
		((arg[i] & arena->op_tab[car->f - 1].args[i])) != arg[i])
			error = 1;
		i++;
	}
	return (error);
}

int			fun_codage(t_core *arena, t_carriage *car, short *arg)
{
	int		i;
	int		codage;
	int		one;

	i = 0;
	one = 128;
	codage = ((int)arena->arena[(car->pos + 1) % MEM_SIZE]);
	while (i < arena->op_tab[car->f - 1].nb_args)
	{
		if (codage >= one + (one / 2))
			arg[i] = 3;
		else if (codage >= one)
			arg[i] = 2;
		else if (codage >= (one / 2))
			arg[i] = 1;
		else
			arg[i] = 0;
		codage -= (arg[i] * (one / 2));
		if (arg[i] == 3)
			arg[i]++;
		i++;
		one /= 4;
	}
	return (ft_type_codage(arena, car, arg));
}

int			byte_cal(short *a, int i, t_core *s, t_carriage *c)
{
	int	p;
	int	t;

	p = 0;
	t = 0;
	while (p < s->op_tab[c->f - 1].nb_args)
	{
		if (a[p] == 1)
		{
			t += 1;
			if (s->arena[(c->pos + t + 1) % MEM_SIZE] > 16
			|| s->arena[(c->pos + t + 1) % MEM_SIZE] < 1)
				c->error++;
		}
		if (a[p] == 2)
			t += i;
		if (a[p] == 4)
			t += 2;
		p++;
	}
	return (t);
}

void		functions2(t_carriage *c, t_core *a, int f)
{
	if (f == 12)
		f12_f15(a, c, 1);
	if (f == 13)
		f2_f13(a, c, 1);
	if (f == 14)
		f14(a, c);
	if (f == 15)
		f12_f15(a, c, 0);
	if (f == 16)
		f16(a, c);
}

void		functions(t_carriage *c, t_core *a, int f)
{
	if (f == 1)
		f1(a, c);
	if (f == 2)
		f2_f13(a, c, 0);
	if (f == 3)
		f3(a, c);
	if (f == 4)
		f4(a, c);
	if (f == 5)
		f5(a, c);
	if (f == 6)
		f6(a, c);
	if (f == 7)
		f7(a, c);
	if (f == 8)
		f8(a, c);
	if (f == 9)
		f9(a, c);
	if (f == 10)
		f10(a, c);
	if (f == 11)
		f11(a, c);
	if (f > 11)
		functions2(c, a, f);
}
