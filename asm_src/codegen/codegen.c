/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codegen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agalayko <agalayko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:39:56 by agalayko          #+#    #+#             */
/*   Updated: 2019/03/13 18:39:57 by agalayko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

static void	get_function_dex2(t_codegen *code, t_lexer *lex)
{
	int	i;

	if (code->have_cd == 1)
		write(lex->fd, &(code->codage), 1);
	i = 0;
	while (i < code->n_args)
	{
		get_argument(code, lex, i);
		i++;
	}
}

static void	get_function_dex(t_lexer *lex)
{
	t_codegen	code;
	int			i;

	code.oper = lex->l_tok->index;
	code.cur_dep = lex->l_tok->dexpos;
	code.have_cd = (lex->g_op_tab[code.oper - 1]).codage;
	code.n_args = (lex->g_op_tab[code.oper - 1]).nb_args;
	code.lable = (lex->g_op_tab[code.oper - 1]).lable;
	i = 0;
	while (i < code.n_args)
	{
		lex->l_tok = lex->l_tok->next;
		code.ar[i] = lex->l_tok->codage;
		code.arg_ind[i] = lex->l_tok->index;
		code.arg[i] = lex->l_tok->name_token;
		lex->l_tok = lex->l_tok->next;
		i++;
	}
	if (code.have_cd == 1)
		code.codage = create_codage(&code);
	get_function_dex2(&code, lex);
}

static void	write_commands(t_lexer *lex)
{
	while (lex->l_tok != NULL)
		if (lex->l_tok->index < 17)
		{
			write(lex->fd, &(lex->l_tok->index), 1);
			get_function_dex(lex);
		}
		else
			lex->l_tok = lex->l_tok->next;
}

int			codegen(t_lexer *lex)
{
	char	*zero;

	lex->l_tok = lex->b_tok;
	create_file(lex);
	zero = ft_memalloc(4);
	rotate_num((char *)&(lex->header->magic), 4);
	write(lex->fd, &(lex->header->magic), 4);
	write(lex->fd, lex->header->prog_name, PROG_NAME_LENGTH);
	write(lex->fd, zero, 4);
	rotate_num((char *)&(lex->dexpos), 4);
	write(lex->fd, &(lex->dexpos), 4);
	write(lex->fd, lex->header->comment, COMMENT_LENGTH);
	write(lex->fd, zero, 4);
	write_commands(lex);
	free(zero);
	return (0);
}
