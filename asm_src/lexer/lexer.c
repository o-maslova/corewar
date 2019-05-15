/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agalayko <agalayko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 22:56:20 by agalayko          #+#    #+#             */
/*   Updated: 2019/03/14 22:56:20 by agalayko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

static int			check_head_part2(int fd, t_header *header, int *posy,
									int type)
{
	char	*line;
	int		res;

	line = no_comments(fd, posy);
	if (line && type == 1 && line == ft_strstr(line, COMMENT_CMD_STRING))
		res = get_header_comment(header, posy, line);
	else if (line && type == 2 && line == ft_strstr(line, NAME_CMD_STRING))
		res = get_header_name(header, posy, line);
	else
		res = 1;
	if (line)
		free(line);
	return (res);
}

static int			check_head_part1(int fd, t_header *header, int *posy)
{
	char	*line;
	int		res;

	line = no_comments(fd, posy);
	if (line && line == ft_strstr(line, NAME_CMD_STRING))
	{
		res = get_header_name(header, posy, line);
		if (res == 0)
			res = check_head_part2(fd, header, posy, 1);
	}
	else if (line && line == ft_strstr(line, COMMENT_CMD_STRING))
	{
		res = get_header_comment(header, posy, line);
		if (res == 0)
			res = check_head_part2(fd, header, posy, 2);
	}
	else
		res = 1;
	if (line)
		free(line);
	return (res);
}

static void			create_reg_string(t_lexer *lex)
{
	int		i;
	char	*str;

	lex->names_regs = (char **)malloc(100 * sizeof(char *));
	lex->names_regs[99] = NULL;
	i = 0;
	while (i < 99)
	{
		str = ft_itoa(i + 1);
		lex->names_regs[i] = ft_strjoin("r", str);
		i++;
		free(str);
	}
}

inline static void	init_lexer(t_lexer *lex)
{
	lex->b_tok = NULL;
	lex->l_tok = NULL;
	lex->lbl = 201;
	lex->dir_lab = 1001;
	lex->dir_num = 2001;
	lex->ind_lab = 3001;
	lex->ind_num = 4001;
	lex->posy = 0;
	lex->error = 0;
	lex->names_oper = ft_strsplit(OP, ' ');
}

t_lexer				*lexer(int fd, char *file_name)
{
	t_lexer	*lex;

	lex = (t_lexer *)malloc(sizeof(t_lexer));
	lex->file_name = file_name;
	init_lexer(lex);
	lex->header = (t_header *)malloc(sizeof(t_header));
	create_reg_string(lex);
	lex->header->magic = COREWAR_EXEC_MAGIC;
	if (check_head_part1(fd, lex->header, &(lex->posy)))
		lexer_error(lex, 0);
	get_line_of_tokens(fd, lex);
	return (lex);
}
