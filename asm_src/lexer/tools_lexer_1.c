/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_lexer_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agalayko <agalayko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 23:02:39 by agalayko          #+#    #+#             */
/*   Updated: 2019/03/14 23:02:40 by agalayko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

int		find_str_in_spl(char **spl, char *str)
{
	int	i;

	i = 0;
	while (spl[i])
	{
		if (ft_strcmp(spl[i], str) == 0)
			break ;
		else
			i++;
	}
	if (spl[i] == NULL)
		return (0);
	else
		return (i + 1);
}

int		is_number(char *name)
{
	int	i;

	i = 0;
	while (name[i] && name[i] >= '0' && name[i] <= '9')
		i++;
	if (name[i] == '\0')
		return (1);
	else
		return (0);
}

char	*no_comments(int fd, int *posy)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line) && (line[0] == COMMENT_CHAR_1
			|| line[0] == COMMENT_CHAR_2 || line[0] == '\0'))
	{
		(*posy)++;
		free(line);
	}
	return (line);
}

int		no_whitespace(char *line, int i)
{
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

void	free_lexer(t_lexer *lex)
{
	t_token	*del;
	t_token	*current;

	del = lex->b_tok;
	while (del != NULL)
	{
		free(del->name_token);
		current = del->next;
		free(del);
		del = current;
	}
	free(lex->header);
	ft_free_split(lex->names_oper);
	ft_free_split(lex->names_regs);
}
