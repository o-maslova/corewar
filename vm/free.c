/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 22:19:27 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/30 22:19:32 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corelib.h"

void		free_c(t_player *p, t_carriage *c, char *s)
{
	t_carriage	*h;

	while (c)
	{
		h = c->next;
		free(c);
		c = h;
	}
	ft_error(p, 4, s);
}

void		free_all(t_core *a, char *s)
{
	t_carriage	*c;
	t_player	*p;

	c = a->carrs;
	p = a->players;
	free(a);
	free_c(p, c, s);
}

void		free_p(t_player *p)
{
	t_player	*p2;

	while (p)
	{
		p2 = p->next;
		free(p);
		p = p2;
	}
}
