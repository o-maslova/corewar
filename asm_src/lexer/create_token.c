/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agalayko <agalayko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 22:57:06 by agalayko          #+#    #+#             */
/*   Updated: 2019/03/14 22:57:07 by agalayko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

inline static void	set_ltok(t_lexer *lex, int index)
{
	lex->l_tok->name_token = lex->name_token;
	lex->l_tok->index = index;
}

inline static void	set_btok(t_lexer *lex, int index)
{
	lex->b_tok->name_token = lex->name_token;
	lex->b_tok->index = index;
}

void				create_first_token(t_lexer *lx, int posx, int type)
{
	lx->b_tok = (t_token *)malloc(sizeof(t_token));
	if (type == 1)
		set_btok(lx, (lx->lbl)++);
	else if (type == 2)
		set_btok(lx, find_str_in_spl(lx->names_oper, lx->name_token));
	else if (type == 3)
		set_btok(lx, find_str_in_spl(lx->names_regs, lx->name_token) + 100);
	else if (type == 4)
		set_btok(lx, (lx->dir_lab)++);
	else if (type == 5)
		set_btok(lx, (lx->dir_num)++);
	else if (type == 6)
		set_btok(lx, (lx->ind_lab)++);
	else if (type == 7)
		set_btok(lx, (lx->ind_num)++);
	else
	{
		lx->l_tok->name_token = ft_strdup(",");
		lx->l_tok->index = (int)SEPARATOR_CHAR;
	}
	lx->b_tok->next = NULL;
	lx->b_tok->posy = lx->posy;
	lx->b_tok->posx = posx;
	lx->l_tok = lx->b_tok;
}

int					get_index_token(t_lexer *lex, int type)
{
	t_token	*current;

	current = lex->b_tok;
	if (type == 1)
		return (type_1(lex, current));
	else if (type == 4)
		return (type_4(lex, current));
	else if (type == 5)
		return (type_5(lex, current));
	else if (type == 6)
		return (type_6(lex, current));
	else if (type == 7)
		return (type_7(lex, current));
	return (0);
}

void				create_new_token(t_lexer *lx, int posx, int type)
{
	lx->l_tok->next = (t_token *)malloc(sizeof(t_token));
	lx->l_tok = lx->l_tok->next;
	lx->l_tok->next = NULL;
	if (type == 1)
		set_ltok(lx, get_index_token(lx, 1));
	else if (type == 2)
		set_ltok(lx, find_str_in_spl(lx->names_oper, lx->name_token));
	else if (type == 3)
		set_ltok(lx, find_str_in_spl(lx->names_regs, lx->name_token) + 100);
	else if (type == 4)
		set_ltok(lx, get_index_token(lx, 4));
	else if (type == 5)
		set_ltok(lx, get_index_token(lx, 5));
	else if (type == 6)
		set_ltok(lx, get_index_token(lx, 6));
	else if (type == 7)
		set_ltok(lx, get_index_token(lx, 7));
	else
	{
		lx->l_tok->name_token = ft_strdup(",");
		lx->l_tok->index = (int)SEPARATOR_CHAR;
	}
	lx->l_tok->next = NULL;
	lx->l_tok->posy = lx->posy;
	lx->l_tok->posx = posx;
}
