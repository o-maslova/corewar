/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:12:42 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/26 13:16:21 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualization.h"

t_carriage		*search_carriage(t_core *a, int pos)
{
	t_carriage	*tmp;

	tmp = a->carrs;
	while (tmp)
	{
		if (tmp->pos == pos)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void			put_colors(t_core *a)
{
	int			i;
	int			diff;
	t_carriage	*tmp;

	i = -1;
	diff = 1;
	while (++i < MEM_SIZE)
	{
		if (ELEM(i).in_field > 0)
			ELEM(i).in_field--;
		if (ELEM(i).in_field == 0 && ELEM(i).live == 0)
			ELEM(i).color = ELEM(i).default_clr;
		ELEM(i).st = ELEM(i).st > 0 ? ELEM(i).st - 1 : ELEM(i).st;
		ELEM(i).live = ELEM(i).live > 0 ? ELEM(i).live - 1 : ELEM(i).live;
		diff = i >= diff * PLAYER_FIELD ? diff + 1 : diff;
		tmp = search_carriage(a, i);
		if (tmp && ELEM(i).live == 0)
		{
			if (ELEM(i).default_clr == CLR(COLOR_NUM - 1).st_clr)
				ELEM(i).color = CLR(COLOR_NUM - 1).c_clr;
			else if (ELEM(i).in_field == 0)
				ELEM(i).color = ELEM(i).default_clr - 1;
		}
	}
}
