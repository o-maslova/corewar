/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f6_f10.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 16:02:46 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/27 16:02:48 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corelib.h"

void	f6(t_core *a, t_carriage *c)
{
	short	arg[3];
	int		i;
	int		h;
	int		p;

	p = 0;
	c->error = fun_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, a, c) + 2;
	i = get_args(a, c, arg, 0);
	p = get_args(a, c, arg, 1);
	h = a->arena[(get_pos_arg(a, c, arg, 2)) % MEM_SIZE] - 1;
	if (c->error != 0)
		return ;
	if (arg[0] == 4)
		read_byte4(a->arena, 0, MOD(c->pos, i % IDX_MOD, 0),
		(unsigned char *)&i);
	if (arg[1] == 4)
		read_byte4(a->arena, 0, MOD(c->pos, p % IDX_MOD, 0),
		(unsigned char *)&p);
	i = i & p;
	p = 0;
	while (p < REG_SIZE)
		c->r[h][p++] = 0;
	read_byte4((unsigned char *)&i, 0, 0, c->r[h]);
	c->carry = i == 0 ? 1 : 0;
}

void	f7(t_core *a, t_carriage *c)
{
	short	arg[3];
	int		i;
	int		h;
	int		p;

	p = 0;
	c->error = fun_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, a, c) + 2;
	i = get_args(a, c, arg, 0);
	p = get_args(a, c, arg, 1);
	h = a->arena[(get_pos_arg(a, c, arg, 2)) % MEM_SIZE] - 1;
	if (c->error != 0)
		return ;
	if (arg[0] == 4)
		read_byte4(a->arena, 0, MOD(c->pos, i % IDX_MOD, 0),
		(unsigned char *)&i);
	if (arg[1] == 4)
		read_byte4(a->arena, 0, MOD(c->pos, p % IDX_MOD, 0),
		(unsigned char *)&p);
	i = i | p;
	p = 0;
	while (p < REG_SIZE)
		c->r[h][p++] = 0;
	read_byte4((unsigned char *)&i, 0, 0, c->r[h]);
	c->carry = i == 0 ? 1 : 0;
}

void	f8(t_core *a, t_carriage *c)
{
	short	arg[3];
	int		i;
	int		h;
	int		p;

	p = 0;
	c->error = fun_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, a, c) + 2;
	i = get_args(a, c, arg, 0);
	p = get_args(a, c, arg, 1);
	h = a->arena[(get_pos_arg(a, c, arg, 2)) % MEM_SIZE] - 1;
	if (c->error != 0)
		return ;
	if (arg[0] == 4)
		read_byte4(a->arena, 0, MOD(c->pos, i % IDX_MOD, 0),
		(unsigned char *)&i);
	if (arg[1] == 4)
		read_byte4(a->arena, 0, MOD(c->pos, p % IDX_MOD, 0),
		(unsigned char *)&p);
	i = i ^ p;
	p = 0;
	while (p < REG_SIZE)
		c->r[h][p++] = 0;
	read_byte4((unsigned char *)&i, 0, 0, c->r[h]);
	c->carry = i == 0 ? 1 : 0;
}

void	f9(t_core *a, t_carriage *c)
{
	int		i;
	short	p[1];

	c->jump = 3;
	i = 0;
	p[0] = 2;
	if (c->carry != 0)
	{
		i = get_args(a, c, p, 0);
		c->jump = i % IDX_MOD;
	}
}

void	f10(t_core *a, t_carriage *c)
{
	short	arg[3];
	int		p;
	int		i;
	int		h;

	c->error = fun_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, a, c) + 2;
	p = a->arena[get_pos_arg(a, c, arg, 2) % MEM_SIZE] - 1;
	if (c->error != 0)
		return ;
	i = get_args(a, c, arg, 0);
	h = get_args(a, c, arg, 1);
	if (arg[0] == 4)
		read_byte4(a->arena, 0, MOD(c->pos, i % IDX_MOD, 0),
		(unsigned char *)&i);
	i = (i + h) % IDX_MOD;
	write_reg(c->r[p], a->arena, 0, MOD(c->pos, i, 0));
}
