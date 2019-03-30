/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 22:25:36 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/30 22:25:39 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corelib.h"

void		read_byte2(US_CHAR *a, int pos, int pos2, US_CHAR *num)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		num[(1 - i + pos) % MEM_SIZE] = a[pos2 % MEM_SIZE];
		i++;
		pos2++;
	}
}

void		read_byte4(US_CHAR *a, int pos, int pos2, US_CHAR *num)
{
	int	i;

	i = 0;
	while (i < REG_SIZE)
	{
		num[(REG_SIZE - 1 - i + pos) % MEM_SIZE] = a[pos2 % MEM_SIZE];
		i++;
		pos2++;
	}
}

short		get_pos_arg(t_core *a, t_carriage *c, short arg[3], short num)
{
	unsigned int	ar;
	short			pos;

	ar = 0;
	pos = c->pos + 1 + a->op_tab[c->f - 1].codage;
	while (ar < (unsigned int)num)
	{
		if (arg[ar] == 1)
			pos += 1;
		else if (arg[ar] == 2)
			pos += a->op_tab[c->f - 1].lable;
		else
			pos += 2;
		ar++;
	}
	return (pos);
}

int			get_args(t_core *a, t_carriage *c, short arg[3], short num)
{
	int		ar;
	short	pos;

	ar = 0;
	pos = get_pos_arg(a, c, arg, num);
	if (arg[num] == 1)
	{
		ar = a->arena[pos % MEM_SIZE] - 1;
		if (ar > 15 || ar < 0)
			return (++(c->error));
		read_byte4(c->r[ar], 0, 0, (US_CHAR *)&ar);
	}
	else if (arg[num] == 2 && a->op_tab[c->f - 1].lable == 4)
		read_byte4(a->arena, 0, pos, (US_CHAR *)&ar);
	else if (arg[num] == 4 || arg[num] == 2)
	{
		read_byte2(a->arena, 0, pos, (US_CHAR *)&ar);
		ar = (ar >= 0x8000) ? (ar - 0xffff - 1) : ar;
	}
	return (ar);
}
