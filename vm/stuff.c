/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stuff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 22:19:10 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/30 22:19:14 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corelib.h"

void		write_player(t_player *p, US_CHAR *a, int t)
{
	int	i;

	i = 0;
	while (i < (int)p->length)
	{
		a[t] = p->code[i];
		t++;
		i++;
	}
}

void		write_reg(US_CHAR *r, US_CHAR *c, int p, int t)
{
	int	i;

	i = 0;
	while (i < 4 && t > 0)
		r[i++] = 0;
	i = 0;
	if (t == -1)
		t = 0;
	while (i < REG_SIZE)
	{
		r[(p + i) % MEM_SIZE] = c[(t + i) % MEM_SIZE];
		i++;
	}
}

int			check_ret(int *t, int i)
{
	close(*t);
	*t = i;
	exit(0);
	return (-1);
}

uint32_t	revers(uint32_t n)
{
	uint32_t	b;

	b = (n >> 24) | ((n & 0xff0000) >> 8) |
		((n & 0xff00) << 8) | (n << 24);
	return (b);
}

US_CHAR		*ft_strncpy2(US_CHAR *dst, const US_CHAR *src, size_t len)
{
	int	l;

	l = -1;
	while (++l < (int)len)
	{
		if (l < (int)len)
			dst[l] = src[l];
	}
	return (dst);
}
