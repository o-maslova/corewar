/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 15:18:07 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/31 15:18:11 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	itoa_helper(uintmax_t i, int base, int m)
{
	while (1)
	{
		i /= base;
		m++;
		if (i == 0)
			break ;
	}
	return (m);
}

char		*ft_itoa_base(uintmax_t num, int base, int xx)
{
	char		*str;
	uintmax_t	i;
	uintmax_t	ppc;
	int			m;

	m = itoa_helper(num, base, 0);
	str = (char *)malloc(sizeof(char) * (m + 1));
	str[m] = '\0';
	m--;
	i = num;
	while (1)
	{
		ppc = i / base;
		if (i - ppc * base <= 9)
			str[m] = i - ppc * base + '0';
		else if (xx == 0)
			str[m] = i - ppc * base - 10 + 'a';
		else if (xx == 1)
			str[m] = i - ppc * base - 10 + 'A';
		i = ppc;
		m--;
		if (i == 0)
			break ;
	}
	return (str);
}
