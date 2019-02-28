/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 12:40:08 by omaslova          #+#    #+#             */
/*   Updated: 2018/04/11 17:09:58 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	power(int n, int i)
{
	int num;

	num = n;
	if (i == 0)
		return (1);
	while (i > 1)
	{
		num *= n;
		i--;
	}
	return (num);
}

static int	check(int n)
{
	if (n == -2147483648)
		n = n % 1000000000;
	if (n < 0)
		return (-n);
	return (n);
}

static int	count_of_digits(int nb)
{
	int i;

	i = 1;
	while (nb / 10 > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	int		i;
	int		j;
	int		nb;
	char	*str;

	j = 0;
	nb = check(n);
	i = count_of_digits(nb);
	i = (n < 0 ? i + 1 : i);
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (n < 0)
	{
		str[j++] = '-';
		if (n == -2147483648)
			str[j++] = '2';
	}
	i = (n < 0 ? i - 2 : i - 1);
	while (i >= 0)
	{
		str[j++] = (nb / (power(10, i))) + 48;
		nb = nb % (power(10, i--));
	}
	str[j] = '\0';
	return (str);
}
