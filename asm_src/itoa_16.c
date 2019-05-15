/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_16.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agalayko <agalayko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 23:03:23 by agalayko          #+#    #+#             */
/*   Updated: 2019/03/14 23:03:23 by agalayko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

char	*itoa_16(uintmax_t num, int xx)
{
	char	*str;
	int		ost;

	str = (char *)malloc(sizeof(char) * (xx + 1));
	str[xx] = '\0';
	ost = 0;
	while (1)
	{
		xx--;
		if (num == 0 || xx == -1)
			break ;
		ost = num % 16;
		if (ost < 10)
			str[xx] = ost + '0';
		else
			str[xx] = ost - 10 + 'a';
		num = num / 16;
	}
	if (xx == -1 && num != 0)
		while (str[++xx])
			str[xx] = 'f';
	else
		while (xx >= 0)
			str[xx--] = '0';
	return (str);
}
