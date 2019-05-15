/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 15:31:43 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/31 15:31:46 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"
#define TOK_N		token->name_token

void	print_underline(int i)
{
	int	k;

	k = -1;
	while (++k < i)
		ft_printf("---");
}

void	write_args_eol(t_token *token, int *i, int flag)
{
	if (token->index != ',' && token->index != 17 && token->index != 18)
	{
		print_underline(*i);
		(*i)++;
		ft_printf("| %s | - (size %d)\n", TOK_N, token->size);
	}
	else if (token->index != ',' && flag == 0)
	{
		*i = 0;
		ft_printf("}\n");
	}
}

void	write_tree_struct(t_lexer *lex)
{
	t_token	*token;
	int		i;
	int		flag;

	token = lex->b_tok;
	i = 0;
	flag = 0;
	while (token)
	{
		if (token->index > 200 && token->index < 1001)
		{
			ft_printf("| %s | - (dexpos %d)\n", TOK_N, token->dexpos);
			i += 1;
			flag = 1;
		}
		else if (token->index > 0 && token->index < 17)
		{
			print_underline(i++);
			flag = 0;
			ft_printf("| %s | - (dexpos %d)\n{\n", TOK_N, token->dexpos);
		}
		else
			write_args_eol(token, &i, flag);
		token = token->next;
	}
}
