/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agalayko <agalayko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:39:49 by agalayko          #+#    #+#             */
/*   Updated: 2019/03/13 18:39:49 by agalayko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

void		get_num_arg(char *arg, int type, int size, t_lexer *lex)
{
	int num;

	num = ft_atoi(&(arg[type]));
	if (arg[type] != '-' || num == 0)
	{
		rotate_num((char *)&num, size);
		write(lex->fd, &(num), size);
	}
	else
	{
		num *= -1;
		if (size == 4)
		{
			num = (0xffffffff ^ num) + 1;
			rotate_num((char *)&num, size);
			write(lex->fd, &(num), size);
		}
		else
		{
			num = (0xffff ^ num) + 1;
			rotate_num((char *)&num, size);
			write(lex->fd, &(num), size);
		}
	}
}

static void	get_lable_arg_2(t_codegen *code, t_lexer *lex, int i)
{
	if (i >= 0)
	{
		rotate_num((char *)&i, code->lable);
		write(lex->fd, &(i), code->lable);
	}
	else
	{
		i *= -1;
		if (code->lable == 4)
		{
			i = (0xffffffff ^ i) + 1;
			rotate_num((char *)&i, code->lable);
			write(lex->fd, &(i), code->lable);
		}
		else
		{
			i = (0xffff ^ i) + 1;
			rotate_num((char *)&i, code->lable);
			write(lex->fd, &(i), code->lable);
		}
	}
}

void		get_lable_arg(t_codegen *code, int type, t_lexer *lex, int j)
{
	t_token	*cur;
	int		i;

	cur = lex->b_tok;
	while (cur != NULL)
	{
		if (cur->index > 200 && cur->index < 1001)
		{
			i = 0;
			while (cur->name_token[i] == code->arg[j][type + i])
				i++;
			if (code->arg[j][type + i] == '\0' && cur->name_token[i] == ':')
				break ;
		}
		cur = cur->next;
	}
	if (cur == NULL)
		ft_error_asm(ERR_LABEL);
	i = cur->dexpos - code->cur_dep;
	get_lable_arg_2(code, lex, i);
}

void		get_argument(t_codegen *code, t_lexer *lex, int i)
{
	if (code->ar[i] == 1)
	{
		code->arg_ind[i] -= 100;
		write(lex->fd, &(code->arg_ind[i]), 1);
	}
	else if (code->ar[i] == 2)
	{
		if (code->arg_ind[i] > 2000 && code->arg_ind[i] < 3001)
			get_num_arg(code->arg[i], 1, code->lable, lex);
		else
			get_lable_arg(code, 2, lex, i);
	}
	else
	{
		code->lable = 2;
		if (code->arg_ind[i] > 4000 && code->arg_ind[i] < 5001)
			get_num_arg(code->arg[i], 0, 2, lex);
		else
			get_lable_arg(code, 1, lex, i);
	}
}
