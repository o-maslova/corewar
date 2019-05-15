/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_lexer_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agalayko <agalayko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 22:56:57 by agalayko          #+#    #+#             */
/*   Updated: 2019/03/14 22:56:59 by agalayko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

int	get_header_comment(t_header *header, int *posy, char *line)
{
	int	i;
	int	k;

	i = ft_strlen(COMMENT_CMD_STRING);
	i = no_whitespace(line, i);
	if (line[i] != '"')
		return (1);
	k = 0;
	while (line[++i] != '"' && k < COMMENT_LENGTH)
		header->comment[k++] = line[i];
	while (k < COMMENT_LENGTH)
		header->comment[k++] = 0;
	header->comment[k] = '\0';
	if (line[i] != '"')
		return (1);
	i = no_whitespace(line, i + 1);
	if (line[i] != '\0' && line[i] != '#')
		return (1);
	(*posy)++;
	return (0);
}

int	get_header_name(t_header *header, int *posy, char *line)
{
	int	i;
	int	k;

	i = ft_strlen(NAME_CMD_STRING);
	i = no_whitespace(line, i);
	if (line[i] != '"')
		return (1);
	k = 0;
	while (line[++i] != '"' && k < PROG_NAME_LENGTH)
		header->prog_name[k++] = line[i];
	while (k < PROG_NAME_LENGTH)
		header->prog_name[k++] = 0;
	header->prog_name[k] = '\0';
	if (line[i] != '"')
		return (1);
	i = no_whitespace(line, i + 1);
	if (line[i] != '\0' && line[i] != '#')
		return (1);
	(*posy)++;
	return (0);
}
