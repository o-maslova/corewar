/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agalayko <agalayko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 22:58:38 by agalayko          #+#    #+#             */
/*   Updated: 2019/03/14 22:58:39 by agalayko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

inline static void	create_token(t_lexer *lex, int i, int type)
{
	if (lex->b_tok == NULL)
		create_first_token(lex, i, type);
	else
		create_new_token(lex, i, type);
}

int					get_token_lorn(char *line, int i, t_lexer *lex)
{
	int	j;

	j = 0;
	while (line[i + j] && ft_strchr(LABEL_CHARS, line[i + j]))
		j++;
	if (line[i + j] == LABEL_CHAR)
		lex->name_token = ft_strsub(line, i, j + 1);
	else
		lex->name_token = ft_strsub(line, i, j);
	if (line[i + j] == LABEL_CHAR)
	{
		j++;
		create_token(lex, i, 1);
	}
	else if (find_str_in_spl(lex->names_oper, lex->name_token))
		create_token(lex, i, 2);
	else if (find_str_in_spl(lex->names_regs, lex->name_token))
		create_token(lex, i, 3);
	else if (is_number(lex->name_token))
		create_token(lex, i, 7);
	else
		ft_test_error(lex->l_tok);
	return (i + j);
}

int					get_token_ind_lable(char *line, int i, t_lexer *lex)
{
	int	j;

	j = 1;
	while (line[i + j] && ft_strchr(LABEL_CHARS, line[i + j]))
		j++;
	lex->name_token = ft_strsub(line, i, j);
	if (lex->name_token[j - 1] == LABEL_CHAR)
		lexer_error(lex, i);
	create_token(lex, i, 6);
	return (i + j);
}

int					get_token_dir(char *line, int i, t_lexer *l)
{
	int	j;

	j = 1;
	if (line[i + j] == LABEL_CHAR)
	{
		j++;
		while (line[i + j] && ft_strchr(LABEL_CHARS, line[i + j]))
			j++;
		l->name_token = ft_strsub(line, i, j);
		if (l->name_token[j - 1] == LABEL_CHAR)
			lexer_error(l, i);
		create_token(l, i, 4);
	}
	else
	{
		if (line[i + j] == '-')
			j++;
		while (line[i + j] && ft_strchr(NUMBR_CHARS, line[i + j]))
			j++;
		l->name_token = ft_strsub(line, i, j);
		if (l->name_token[j - 1] == DIRECT_CHAR || l->name_token[j - 1] == '-')
			lexer_error(l, i);
		create_token(l, i, 5);
	}
	return (i + j);
}

int					get_token_chars(char *line, int i, t_lexer *lex)
{
	int	j;

	j = 1;
	if (line[i] == '-')
	{
		while (line[i + j] && ft_strchr(NUMBR_CHARS, line[i + j]))
			j++;
		lex->name_token = ft_strsub(line, i, j);
		if (lex->name_token[j - 1] == '-')
			lexer_error(lex, i);
		create_token(lex, i, 7);
	}
	else if (line[i] == ',')
		create_token(lex, i, 8);
	return (i + j);
}
