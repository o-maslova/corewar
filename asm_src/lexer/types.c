/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agalayko <agalayko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:21:39 by agalayko          #+#    #+#             */
/*   Updated: 2019/03/13 18:21:39 by agalayko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

int	type_1(t_lexer *lex, t_token *current)
{
	while (current->next != NULL)
	{
		if (current->index > 200 && current->index < 1001)
			if (ft_strcmp(current->name_token, lex->name_token) == 0)
				return (current->index);
		current = current->next;
	}
	(lex->lbl)++;
	return (lex->lbl - 1);
}

int	type_4(t_lexer *lex, t_token *current)
{
	while (current->next != NULL)
	{
		if (current->index > 1000 && current->index < 2001)
			if (ft_strcmp(current->name_token, lex->name_token) == 0)
				return (current->index);
		current = current->next;
	}
	(lex->dir_lab)++;
	return (lex->dir_lab - 1);
}

int	type_5(t_lexer *lex, t_token *current)
{
	while (current->next != NULL)
	{
		if (current->index > 2000 && current->index < 3001)
			if (ft_strcmp(current->name_token, lex->name_token) == 0)
				return (current->index);
		current = current->next;
	}
	(lex->dir_num)++;
	return (lex->dir_num - 1);
}

int	type_6(t_lexer *lex, t_token *current)
{
	while (current->next != NULL)
	{
		if (current->index > 3000 && current->index < 4001)
			if (ft_strcmp(current->name_token, lex->name_token) == 0)
				return (current->index);
		current = current->next;
	}
	(lex->ind_lab)++;
	return (lex->ind_lab - 1);
}

int	type_7(t_lexer *lex, t_token *current)
{
	while (current->next != NULL)
	{
		if (current->index > 4000 && current->index < 5001)
			if (ft_strcmp(current->name_token, lex->name_token) == 0)
				return (current->index);
		current = current->next;
	}
	(lex->ind_num)++;
	return (lex->ind_num - 1);
}
