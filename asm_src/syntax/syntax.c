/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agalayko <agalayko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 21:15:33 by agalayko          #+#    #+#             */
/*   Updated: 2019/03/14 21:15:33 by agalayko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

static t_token	*line_with_lable(t_lexer *lex, t_token *current)
{
	current->dexpos = lex->dexpos;
	current->size = 0;
	current->codage = -1;
	current = current->next;
	while (current != NULL && current->index == 17)
		current = current->next;
	return (current);
}

int				check_arguments(t_lexer *lex, t_token *current, int type,
								int dir_size)
{
	if (type == 2)
	{
		if (current == NULL || current->index < 1001 || current->index > 3000)
			return (0);
		current_init(lex, current, dir_size, 2);
		return (1);
	}
	else if (type == 3)
	{
		if (current == NULL || current->index < 3001 || current->index > 5000)
			return (0);
		current_init(lex, current, 2, 3);
		return (1);
	}
	else if (type == 1)
	{
		if (current == NULL || current->index < 101 || current->index > 200)
			return (0);
		current_init(lex, current, 1, 1);
		return (1);
	}
	return (0);
}

static t_token	*operation_live(t_lexer *lex, t_token *current)
{
	current_init(lex, current, 1, 0);
	current = current->next;
	if (check_arguments(lex, current, 2, 4) == 0)
		ft_test_error(current);
	current = current->next;
	if (current->index != 17)
		ft_test_error(current);
	while (current != NULL && current->index == 17)
		current = current->next;
	return (current);
}

static t_token	*only_operation(t_lexer *lex, t_token *cur)
{
	if (cur->index == 1)
		cur = operation_live(lex, cur);
	else if (cur->index == 2 || cur->index == 13)
		cur = operation_ld_lld(lex, cur);
	else if (cur->index == 3)
		cur = operation_st(lex, cur);
	else if (cur->index == 4 || cur->index == 5)
		cur = operation_add_sub(lex, cur);
	else if (cur->index == 6 || cur->index == 7 || cur->index == 8)
		cur = operation_and_or_xor(lex, cur);
	else if (cur->index == 9 || cur->index == 12 || cur->index == 15)
		cur = operation_zjmp_fork_lfork(lex, cur);
	else if (cur->index == 10 || cur->index == 14)
		cur = operation_ldi_lldi(lex, cur);
	else if (cur->index == 11)
		cur = operation_sti(lex, cur);
	else if (cur->index == 16)
		cur = operation_aff(lex, cur);
	return (cur);
}

int				syntax(t_lexer *lex)
{
	t_token	*current;

	current = lex->b_tok;
	get_functions(lex);
	lex->dexpos = 0;
	while (current != NULL)
	{
		if (current->index > 200 && current->index < 1001)
			current = line_with_lable(lex, current);
		else if (current->index >= 1 && current->index < 17)
			current = only_operation(lex, current);
		else if (current->index == 18)
			break ;
		else
			ft_test_error(current);
	}
	return (0);
}
