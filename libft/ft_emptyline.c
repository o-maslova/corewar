/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_emptyline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 13:36:35 by omaslova          #+#    #+#             */
/*   Updated: 2018/12/03 13:36:38 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_emptyline(char *str)
{
	int i;
	int space_amount;

	i = 0;
	space_amount = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t')
			space_amount++;
		i++;
	}
	if (i == space_amount || str[0] == '\n')
		return (1);
	return (0);
}
