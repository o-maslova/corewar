/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agalayko <agalayko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:40:03 by agalayko          #+#    #+#             */
/*   Updated: 2019/03/13 18:40:04 by agalayko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

static int	codage_to_int(char *codage, t_codegen *code)
{
	int	i;
	int	num;
	int	res;

	i = code->n_args * 2;
	while (i < 8)
		codage[i++] = '0';
	i = 0;
	num = 128;
	res = 0;
	while (i < 8)
	{
		if (codage[i] == '1')
			res = res + num;
		num /= 2;
		i++;
	}
	return (res);
}

int			create_codage(t_codegen *code)
{
	char	*codage;
	int		i;

	codage = (char *)malloc(sizeof(char) * 9);
	codage[8] = '\0';
	i = -1;
	while (++i < code->n_args)
		if (code->ar[i] == 1)
		{
			codage[i * 2] = '0';
			codage[i * 2 + 1] = '1';
		}
		else if (code->ar[i] == 2)
		{
			codage[i * 2] = '1';
			codage[i * 2 + 1] = '0';
		}
		else
		{
			codage[i * 2] = '1';
			codage[i * 2 + 1] = '1';
		}
	i = codage_to_int(codage, code);
	free(codage);
	return (i);
}

static char	*create_name_file(char *filename)
{
	char	*name;
	int		i;

	name = (char *)malloc(sizeof(char) * (ft_strlen(filename) + 3));
	i = -1;
	while (filename[++i])
		name[i] = filename[i];
	i--;
	name[i++] = 'c';
	name[i++] = 'o';
	name[i++] = 'r';
	name[i] = '\0';
	return (name);
}

void		create_file(t_lexer *lex)
{
	char	*name;

	name = create_name_file(lex->file_name);
	lex->fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	free(name);
}
