/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corelib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmediany <bmediany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 11:18:12 by bmediany          #+#    #+#             */
/*   Updated: 2019/02/01 11:18:12 by bmediany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORELIB_H
# define CORELIB_H

#include "op.h"

#define PFC_RED			"\x1b[31m"
#define PFC_RESET		"\x1b[0m"
#define PFC_GREEN		"\x1b[32m"

typedef struct			carriage_s
{
	unsigned int		player;			//номер игрока, породившего каретку//
	int					f;				//номер функции, которую будет выполнять//
	int					jump;			//количество байт, которые нужно будет «перешагнуть», чтобы оказаться на следующей операции//
	int					live;			//цикл, в котором в последний раз была выполнена операция live//
	int					cast;			//сколько циклов до выполнения действия//
	int					number;			//номер каретки//
	int					pos;			//позиция//
	unsigned char		r[REG_NUMBER][REG_SIZE];
	int					carry;			//0 = false; 1 = true//
	int					error;
	struct carriage_s	*next;
}						carriage_t;

typedef struct  		s_op
{
	char				*name;
	unsigned char		nb_args;
	t_arg_type			args[3];
	unsigned char		opcode;
	unsigned int		cycle;
	char				*description;
	unsigned char		codage;
	unsigned char		lable;
}						t_op;

typedef struct			s_core
{
	unsigned char		*arena;
	int					last_check;
	int					num_pl;
	int					dump;
	int					n[MAX_PLAYERS];
	int					last_say_live;
	int					n_cycles;
	int					max_checks;
	int					num_lives;
	int					cycle_to_die;
	int					n_check;
	struct s_op			op_tab[17];
	struct player_s		*players;
	struct carriage_s	*carrs;
}						t_core;

typedef struct			player_s
{
	int					number;
	char				prog_name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	unsigned char		code[CHAMP_MAX_SIZE];
	unsigned int		length;			//длина исполняемого кода//
	struct player_s		*next;
}						player_t;

void	make_core2(t_core *a);

#endif