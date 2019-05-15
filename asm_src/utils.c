/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agalayko <agalayko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:30:31 by agalayko          #+#    #+#             */
/*   Updated: 2019/03/13 18:30:31 by agalayko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

int				length_of_int(int num)
{
	int	i;

	i = 1;
	while (num / 10 > 0)
	{
		i++;
		num /= 10;
	}
	return (i);
}

char			*join_with_free(char *str1, char *str2)
{
	char *str3;

	str3 = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (str3);
}

static char		*ft_num(char *num1, char *num2)
{
	char	*num;
	int		len;
	int		i;

	num = ft_memset(ft_strnew(9), '0', 9);
	num[0] = '[';
	len = ft_strlen(num1);
	i = 0;
	while (num1[i])
		num[4 - len--] = num1[i++];
	num[4] = ':';
	len = ft_strlen(num1);
	i = 0;
	while (num2[i])
		num[8 - len--] = num2[i++];
	num[8] = ']';
	free(num1);
	free(num2);
	return (num);
}

static char		*ft_addition_error(t_token *token, char *str)
{
	char	*tmp;

	if (!ft_strcmp(token->name_token, "EOL"))
	{
		tmp = ft_strjoin(str, " ENDLINE");
		free(str);
		ft_error_asm(tmp);
	}
	else if (!ft_strcmp(token->name_token, ","))
		return (ft_strjoin(str, " SEPARATOR \""));
	else if (token->index < 2001)
		return (ft_strjoin(str, " DIRECT_LABEL \""));
	else if (token->index < 3001)
		return (ft_strjoin(str, " DIRECT \""));
	else if (token->index < 4001)
		return (ft_strjoin(str, " INDIRECT_LABEL \""));
	else
		return (ft_strjoin(str, " INSTRUCTION \""));
	return (NULL);
}

void			ft_test_error(t_token *token)
{
	char	*str;
	char	*tmp;

	if (!token)
		ft_error_asm(ERR_NULL);
	tmp = ft_num(ft_itoa(token->posy + 1), ft_itoa(token->posx + 1));
	str = ft_strjoin(ERR_TOKEN, tmp);
	free(tmp);
	tmp = ft_addition_error(token, str);
	free(str);
	str = ft_strjoin(tmp, token->name_token);
	free(tmp);
	tmp = ft_strjoin(str, "\"");
	free(str);
	ft_error_asm(tmp);
}
