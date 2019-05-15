/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agalayko <agalayko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 21:17:54 by agalayko          #+#    #+#             */
/*   Updated: 2019/03/14 21:17:55 by agalayko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

t_token	*operation_ldi_lldi(t_lexer *lex, t_token *cur)
{
	current_init(lex, cur, 2, 0);
	cur = cur->next;
	if (check_arguments(lex, cur, 1, 2) == 0
		&& check_arguments(lex, cur, 2, 2) == 0
		&& check_arguments(lex, cur, 3, 2) == 0)
		ft_test_error(cur);
	cur = cur->next;
	if (cur == NULL || cur->index != 44)
		ft_test_error(cur);
	cur = cur->next;
	if (check_arguments(lex, cur, 1, 2) == 0
		&& check_arguments(lex, cur, 2, 2) == 0)
		ft_test_error(cur);
	cur = cur->next;
	if (cur == NULL || cur->index != 44)
		ft_test_error(cur);
	cur = cur->next;
	if (check_arguments(lex, cur, 1, 2) == 0)
		ft_test_error(cur);
	cur = cur->next;
	if (cur->index != 17)
		ft_test_error(cur);
	while (cur != NULL && cur->index == 17)
		cur = cur->next;
	return (cur);
}

t_token	*operation_sti(t_lexer *lex, t_token *cur)
{
	current_init(lex, cur, 2, 0);
	cur = cur->next;
	if (check_arguments(lex, cur, 1, 2) == 0)
		ft_test_error(cur);
	cur = cur->next;
	if (cur == NULL || cur->index != 44)
		ft_test_error(cur);
	cur = cur->next;
	if (check_arguments(lex, cur, 1, 2) == 0
		&& check_arguments(lex, cur, 2, 2) == 0
		&& check_arguments(lex, cur, 3, 2) == 0)
		ft_test_error(cur);
	cur = cur->next;
	if (cur == NULL || cur->index != 44)
		ft_test_error(cur);
	cur = cur->next;
	if (check_arguments(lex, cur, 1, 2) == 0
		&& check_arguments(lex, cur, 2, 2) == 0)
		ft_test_error(cur);
	cur = cur->next;
	if (cur->index != 17)
		ft_test_error(cur);
	while (cur != NULL && cur->index == 17)
		cur = cur->next;
	return (cur);
}

t_token	*operation_aff(t_lexer *lex, t_token *current)
{
	current_init(lex, current, 2, 0);
	current = current->next;
	if (check_arguments(lex, current, 1, 2) == 0)
		ft_test_error(current);
	current = current->next;
	if (current->index != 17)
		ft_test_error(current);
	while (current != NULL && current->index == 17)
		current = current->next;
	return (current);
}
