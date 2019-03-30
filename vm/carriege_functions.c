/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriege_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 22:18:29 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/30 22:18:33 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corelib.h"

t_carriage	*make_carret2(t_player *p, int i, int l)
{
	t_carriage	*c;

	c = ft_memalloc(sizeof(t_carriage) * 1);
	c->player = (0xffffffff ^ p->number) + 1;
	c->len_of_player = p->length;
	read_byte4((US_CHAR *)&c->player, 0, 0, c->r[0]);
	c->pos = l;
	c->jump = 0;
	c->carry = 0;
	c->cast = 1;
	c->live = 0;
	c->number = i;
	c->f = 0;
	return (c);
}

t_carriage	*make_carret(US_CHAR *a, t_player *p, t_carriage *c, int t)
{
	t_carriage	*o;
	int			i;
	int			l;

	l = MEM_SIZE / t;
	i = 0;
	while (p)
	{
		o = make_carret2(p, i++, l * (p->number - 1));
		o->next = c;
		write_player(p, a, l * (p->number - 1));
		c = o;
		p = p->next;
	}
	return (c);
}

int			carret(t_carriage *c, t_core *a, US_CHAR *s)
{
	if (c->cast == 0 && (s[c->pos] > 16 || s[c->pos] < 1))
	{
		c->pos = (c->pos + 1) % MEM_SIZE;
		return (0);
	}
	if (c->cast == 0 && (s[c->pos] <= 16 && s[c->pos] > 0))
	{
		c->f = s[c->pos];
		c->cast = a->op_tab[c->f - 1].cycle;
	}
	c->cast--;
	if (c->f != 0 && c->cast == 0)
	{
		functions(c, a, c->f);
		c->pos = (MEM_SIZE + (c->pos + c->jump) % MEM_SIZE) % MEM_SIZE;
		c->f = 0;
		c->jump = 0;
		c->error = 0;
	}
	return (0);
}

void		check_cycles_carret(t_core *a, t_carriage *c, t_carriage *c2)
{
	while (c)
		if (c->live <= a->last_check)
		{
			if (c == a->carrs)
			{
				a->carrs = c->next;
				free(c);
				c = a->carrs;
				c2 = a->carrs;
			}
			else
			{
				c2->next = c->next;
				free(c);
				c = c2->next;
			}
		}
		else if (c2 == c)
			c = c->next;
		else
		{
			c = c->next;
			c2 = c2->next;
		}
}

void		check_cycles(t_core *a)
{
	if (a->n_cycles - a->last_check == a->cycle_to_die)
	{
		ft_bzero(a->live_in_p, (sizeof(int) * 4));
		if (a->num_lives >= NBR_LIVE)
		{
			a->cycle_to_die -= CYCLE_DELTA;
			a->max_checks = 0;
		}
		else
			a->max_checks++;
		if (a->max_checks == MAX_CHECKS)
		{
			a->cycle_to_die -= CYCLE_DELTA;
			a->max_checks = 0;
		}
		a->num_lives = 0;
		check_cycles_carret(a, a->carrs, a->carrs);
		a->last_check = a->n_cycles;
	}
}
