/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f11_f16.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 16:02:17 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/27 16:02:21 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corelib.h"

void	f11(t_core *a, t_carriage *c)
{
	short	arg[3];
	int		tmp;
	int		i;
	int		h;
	int		p;

	tmp = -1;
	c->error = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, a, c) + 2;
	if (c->error != 0)
		return ;
	i = a->arena[get_pos_arg(a, c, arg, 0) % MEM_SIZE] - 1;
	h = get_args(a, c, arg, 1);
	p = get_args(a, c, arg, 2);
	if (arg[1] == 4)
		read_byte4(a->arena, 0, c->pos + (h % IDX_MOD), (unsigned char *)&h);
	h = (h + p) % IDX_MOD;
	write_reg(a->arena, c->r[i],
		(MEM_SIZE + (c->pos + h) % MEM_SIZE) % MEM_SIZE, 0);
	while (a->visual_flag == 1 && ++tmp < 4)
	{
		ELEM(MOD(c->pos, h, tmp)).st = 50;
		ELEM(MOD(c->pos, h, tmp)).default_clr = CLR(-(c->player) - 1).st_clr;
	}
}

void	f12_f15_duplicate_carret(t_carriage *c, t_core *a, int pos)
{
	t_carriage	*new;
	int			i;
	int			p;

	if (!(new = ft_memalloc(sizeof(t_carriage))))
		free_all(a, "malloc error");
	new->player = c->player;
	new->len_of_player = c->len_of_player;
	new->live = c->live;
	new->number = a->carrs->number + 1;
	new->pos = MOD(c->pos, pos, 0);
	new->carry = c->carry;
	i = 0;
	while (i < REG_NUMBER)
	{
		p = -1;
		while (++p < REG_SIZE)
			new->r[i][p] = c->r[i][p];
		i++;
	}
	new->next = a->carrs;
	a->carrs = new;
	a->carrs_num++;
}

void	f12_f15(t_core *a, t_carriage *c, int p)
{
	int			i;
	short		g[1];
	t_carriage	*c2;

	c->jump = 3;
	g[0] = 2;
	i = get_args(a, c, g, 0);
	if (p == 1)
		f12_f15_duplicate_carret(c, a, i % IDX_MOD);
	else
		f12_f15_duplicate_carret(c, a, i);
}

void	f14(t_core *a, t_carriage *c)
{
	short	arg[3];
	int		p;
	int		i;
	int		h;

	c->error = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, a, c) + 2;
	p = a->arena[get_pos_arg(a, c, arg, 2) % MEM_SIZE] - 1;
	if (c->error != 0)
		return ;
	i = get_args(a, c, arg, 0);
	h = get_args(a, c, arg, 1);
	if (arg[0] == 4)
		read_byte4(a->arena, 0, c->pos + (i % IDX_MOD), (unsigned char *)&i);
	i = i + h;
	write_reg(c->r[p], a->arena, 0, MOD(c->pos, i, 0));
}

void	f16(t_core *a, t_carriage *c)
{
	short	arg[3];
	int		h;

	c->error = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, a, c) + 2;
	if (c->error != 0)
		return ;
	h = get_args(a, c, arg, 0);
	h %= 256;
}
