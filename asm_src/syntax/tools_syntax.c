/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agalayko <agalayko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 21:18:02 by agalayko          #+#    #+#             */
/*   Updated: 2019/03/14 21:18:02 by agalayko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

inline void	current_init(t_lexer *lex, t_token *current, int size, int codage)
{
	current->size = size;
	current->codage = codage;
	current->dexpos = lex->dexpos;
	lex->dexpos += current->size;
}
