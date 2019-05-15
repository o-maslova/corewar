/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agalayko <agalayko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 21:17:42 by agalayko          #+#    #+#             */
/*   Updated: 2019/03/14 21:17:43 by agalayko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

t_token	*operation_ld_lld(t_lexer *lex, t_token *current)
{
	current_init(lex, current, 2, 0);
	current = current->next;
	if (check_arguments(lex, current, 2, 4) == 0
		&& check_arguments(lex, current, 3, 4) == 0)
		ft_test_error(current);
	current = current->next;
	if (current == NULL || current->index != 44)
		ft_test_error(current);
	current = current->next;
	if (check_arguments(lex, current, 1, 4) == 0)
		ft_test_error(current);
	current = current->next;
	if (current->index != 17)
		ft_test_error(current);
	while (current != NULL && current->index == 17)
		current = current->next;
	return (current);
}

t_token	*operation_st(t_lexer *lex, t_token *current)
{
	current_init(lex, current, 2, 0);
	current = current->next;
	if (check_arguments(lex, current, 1, 4) == 0)
		ft_test_error(current);
	current = current->next;
	if (current == NULL || current->index != 44)
		ft_test_error(current);
	current = current->next;
	if (check_arguments(lex, current, 1, 4) == 0
		&& check_arguments(lex, current, 3, 4) == 0)
		ft_test_error(current);
	current = current->next;
	if (current->index != 17)
		ft_test_error(current);
	while (current != NULL && current->index == 17)
		current = current->next;
	return (current);
}

t_token	*operation_add_sub(t_lexer *lex, t_token *current)
{
	current_init(lex, current, 2, 0);
	current = current->next;
	if (check_arguments(lex, current, 1, 4) == 0)
		ft_test_error(current);
	current = current->next;
	if (current == NULL || current->index != 44)
		ft_test_error(current);
	current = current->next;
	if (check_arguments(lex, current, 1, 4) == 0)
		ft_test_error(current);
	current = current->next;
	if (current == NULL || current->index != 44)
		ft_test_error(current);
	current = current->next;
	if (check_arguments(lex, current, 1, 4) == 0)
		ft_test_error(current);
	current = current->next;
	if (current->index != 17)
		ft_test_error(current);
	while (current != NULL && current->index == 17)
		current = current->next;
	return (current);
}

t_token	*operation_and_or_xor(t_lexer *lex, t_token *cur)
{
	current_init(lex, cur, 2, 0);
	cur = cur->next;
	if (check_arguments(lex, cur, 1, 4) == 0 && check_arguments(lex, cur, 2, 4)
		== 0 && check_arguments(lex, cur, 3, 4) == 0)
		ft_test_error(cur);
	cur = cur->next;
	if (cur == NULL || cur->index != 44)
		ft_test_error(cur);
	cur = cur->next;
	if (check_arguments(lex, cur, 1, 4) == 0
		&& check_arguments(lex, cur, 2, 4) == 0
		&& check_arguments(lex, cur, 3, 4) == 0)
		ft_test_error(cur);
	cur = cur->next;
	if (cur == NULL || cur->index != 44)
		ft_test_error(cur);
	cur = cur->next;
	if (check_arguments(lex, cur, 1, 4) == 0)
		ft_test_error(cur);
	cur = cur->next;
	if (cur->index != 17)
		ft_test_error(cur);
	while (cur != NULL && cur->index == 17)
		cur = cur->next;
	return (cur);
}

t_token	*operation_zjmp_fork_lfork(t_lexer *lex, t_token *current)
{
	current_init(lex, current, 1, 0);
	current = current->next;
	if (check_arguments(lex, current, 2, 2) == 0)
		ft_test_error(current);
	current = current->next;
	if (current->index != 17)
		ft_test_error(current);
	while (current != NULL && current->index == 17)
		current = current->next;
	return (current);
}
