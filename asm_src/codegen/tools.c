/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agalayko <agalayko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:40:10 by agalayko          #+#    #+#             */
/*   Updated: 2019/03/13 18:40:11 by agalayko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

void		rotate_num(char *str, int size)
{
	int		i;
	char	t;
	int		s;

	i = 0;
	s = size / 2;
	if (size != 1)
		while (size != s)
		{
			t = str[i];
			str[i] = str[size - 1];
			str[size - 1] = t;
			i++;
			size--;
		}
}

static void	addon_byte(char *str, char *result, int i, int k)
{
	if ((int)str[k] / 16 < 10)
		result[i] = (int)str[k] / 16 + '0';
	else
		result[i] = (int)str[k] / 16 - 10 + 'a';
	i++;
	if ((int)str[k] % 16 < 10)
		result[i] = (int)str[k] % 16 + '0';
	else
		result[i] = (int)str[k] % 16 - 10 + 'a';
}

char		*str_to_byte(char *str, int type)
{
	char	*result;
	int		len;
	int		i;
	int		k;

	if (type == 1)
		len = PROG_NAME_LENGTH * 2;
	else
		len = COMMENT_LENGTH * 2;
	result = (char *)malloc(sizeof(char) * (len + 1));
	result[len] = '\0';
	i = 0;
	k = 0;
	while (str[k] && i < len)
	{
		addon_byte(str, result, i, k);
		i++;
		k++;
	}
	while (i < len)
		result[i++] = '0';
	return (result);
}

char		*get_magic(void)
{
	char *str;
	char *str2;

	str = ft_itoa_base(COREWAR_EXEC_MAGIC, 16, 0);
	str2 = ft_strjoin("00", str);
	free(str);
	return (str2);
}
