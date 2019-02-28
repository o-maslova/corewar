/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_degree_of_three.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:14:59 by omaslova          #+#    #+#             */
/*   Updated: 2019/02/01 15:15:22 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_degree_of_three(int num)
{
	int i;
	int nb;

	i = 0;
	nb = num;
	while (nb / 3 >= 3)
	{
		nb = nb / 3;
		i++;
	}
	return (i);
}
