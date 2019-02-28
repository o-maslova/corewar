/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 12:55:28 by omaslova          #+#    #+#             */
/*   Updated: 2018/12/03 12:55:33 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_overflow(char *str, int num)
{
	char *num_2;

	num_2 = ft_itoa(num);
	if (ft_strcmp(str, num_2) != 0)
		return (0);
	return (1);
}

int		ft_isnumstr(char *str)
{
	int i;
	int num;

	i = 0;
	if (str)
	{
		num = ft_atoi(str);
		if (ft_strlen(str) >= 10)
			if (!is_overflow(str, num))
				return (0);
		if (num < 0 || num > 2147483647)
			return (0);
		if (str[i] == '\0')
			return (0);
		while (str[i] != '\0')
		{
			if (!ft_isdigit(str[i]))
				return (0);
			i++;
		}
		return (1);
	}
	return (-1);
}
