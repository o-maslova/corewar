/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agalayko <agalayko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 22:57:16 by agalayko          #+#    #+#             */
/*   Updated: 2019/03/14 22:57:17 by agalayko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

void		lexer_error(t_lexer *lex, int i)
{
	int		len;
	int		j;
	char	*str;

	lex->error = 1;
	len = length_of_int(i) + length_of_int(lex->posy) + 4;
	lex->error_str = (char *)malloc(sizeof(char) * len);
	lex->error_str[len - 1] = '\0';
	str = ft_itoa(lex->posy + 1);
	j = -1;
	len = 0;
	lex->error_str[len] = '[';
	while (str[++j])
		lex->error_str[++len] = str[j];
	lex->error_str[++len] = '.';
	free(str);
	str = ft_itoa(i + 1);
	j = -1;
	while (str[++j])
		lex->error_str[++len] = str[j];
	lex->error_str[++len] = ']';
	lex->error_str = join_with_free(ft_strdup(ERR_LEX), lex->error_str);
	free(str);
	ft_error_asm(lex->error_str);
}

static void	create_eo_token(t_lexer *lex, int posx, char *name, int index)
{
	lex->l_tok->next = (t_token *)malloc(sizeof(t_token));
	lex->l_tok = lex->l_tok->next;
	lex->l_tok->codage = -2;
	lex->l_tok->dexpos = -2;
	lex->l_tok->name_token = ft_strdup(name);
	lex->l_tok->index = index;
	lex->l_tok->next = NULL;
	lex->l_tok->posy = lex->posy;
	lex->l_tok->posx = posx;
}

static void	get_tokens_from_line(char *line, t_lexer *lex)
{
	int	i;

	i = 0;
	while (line[i])
	{
		i = no_whitespace(line, i);
		if (line[i] != '\0' && ft_strchr(LABEL_CHARS, line[i]))
			i = get_token_lorn(line, i, lex);
		else if (line[i] == LABEL_CHAR)
			i = get_token_ind_lable(line, i, lex);
		else if (line[i] == DIRECT_CHAR)
			i = get_token_dir(line, i, lex);
		else if (line[i] == '-' || line[i] == ',')
			i = get_token_chars(line, i, lex);
		else if (line[i] == COMMENT_CHAR_1 || line[i] == COMMENT_CHAR_2)
			break ;
		else if (line[i] != '\0')
			lexer_error(lex, i);
	}
	if (lex->l_tok != NULL)
		create_eo_token(lex, i, "EOL", 17);
	(lex->posy)++;
}

int			get_line_of_tokens(int fd, t_lexer *lex)
{
	char	*line;

	while (1)
	{
		line = no_comments(fd, &(lex->posy));
		if (line == NULL)
			break ;
		get_tokens_from_line(line, lex);
		free(line);
	}
	create_eo_token(lex, 0, "EOF", 18);
	return (0);
}
