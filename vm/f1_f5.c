/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f1_f5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 16:02:29 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/27 16:02:33 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corelib.h"

void	f1(t_core *a, t_carriage *c)
{
	int		i;
	short	p[1];

	c->live = a->n_cycles;
	p[0] = 2;
	i = get_args(a, c, p, 0);
	i *= -1;
	a->num_lives++;
	if (i <= a->num_pl && i > 0)
	{
		if (a->visual_flag == 1)
		{
			ELEM(c->pos).live = 50;
			ELEM(c->pos).color = CLR(-(c->player) - 1).live_clr;
			if (ELEM(c->pos).default_clr != CLR(-(c->player) - 1).st_clr)
				ELEM(c->pos).in_field = 50;
		}
		a->live_in_p[i - 1] += 1;
		a->last_say_live = i;
		a->n[i - 1] = a->n_cycles;
	}
	c->jump = 5;
}

void	f2_f13(t_core *a, t_carriage *c, int f)
{
	short	arg[3];
	int		i;
	int		h;

	c->error = fun_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, a, c) + 2;
	h = a->arena[get_pos_arg(a, c, arg, 1) % MEM_SIZE] - 1;
	if (c->error != 0)
		return ;
	i = get_args(a, c, arg, 0);
	if (arg[0] == 4)
	{
		if (f == 0 && i % IDX_MOD != i)
			i %= IDX_MOD;
		read_byte4(a->arena, 0, MOD(c->pos, i, 0), (unsigned char *)&i);
	}
	read_byte4((unsigned char *)&i, 0, 0, c->r[h]);
	c->carry = i == 0 ? 1 : 0;
}

void	f3(t_core *a, t_carriage *c)
{
	short	arg[3];
	int		tmp;
	int		i;
	int		h;

	tmp = -1;
	c->error = fun_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, a, c) + 2;
	if (c->error != 0)
		return ;
	i = a->arena[get_pos_arg(a, c, arg, 0) % MEM_SIZE] - 1;
	if (arg[1] == 1)
	{
		h = a->arena[get_pos_arg(a, c, arg, 1) % MEM_SIZE] - 1;
		write_reg(c->r[h], c->r[i], 0, 0);
		return ;
	}
	h = get_args(a, c, arg, 1);
	h %= IDX_MOD;
	write_reg(a->arena, c->r[i], MOD(c->pos, h, 0), 0);
	while (a->visual_flag == 1 && ++tmp < 4)
	{
		ELEM(MOD(c->pos, h, tmp)).st = 50;
		ELEM(MOD(c->pos, h, tmp)).default_clr = CLR(-(c->player) - 1).st_clr;
	}
}

void	f4(t_core *a, t_carriage *c)
{
	short			arg[3];
	unsigned int	i;
	unsigned int	h;
	int				p;

	c->error = fun_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, a, c) + 2;
	p = a->arena[get_pos_arg(a, c, arg, 2) % MEM_SIZE] - 1;
	if (c->error != 0)
		return ;
	i = get_args(a, c, arg, 0);
	h = get_args(a, c, arg, 1);
	i = i + h;
	h = 0;
	while (h < REG_SIZE)
		c->r[p][h++] = 0;
	read_byte4((unsigned char *)&i, 0, 0, c->r[p]);
	c->carry = i == 0 ? 1 : 0;
}

void	f5(t_core *a, t_carriage *c)
{
	short			arg[3];
	unsigned int	i;
	unsigned int	h;
	int				p;

	c->error = fun_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, a, c) + 2;
	p = a->arena[get_pos_arg(a, c, arg, 2) % MEM_SIZE] - 1;
	if (c->error != 0)
		return ;
	i = get_args(a, c, arg, 0);
	h = get_args(a, c, arg, 1);
	i = i - h;
	h = 0;
	while (h < REG_SIZE)
		c->r[p][h++] = 0;
	read_byte4((unsigned char *)&i, 0, 0, c->r[p]);
	c->carry = i == 0 ? 1 : 0;
}
