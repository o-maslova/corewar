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

# include "op.h"
# include "libft.h"
# include "ft_printf/ft_printf.h"
# include "typedef.h"
# include "visualization.h"

# define PLAYER				t_player
# define VIS				a->visual
# define MOD(p, i, tmp)	((MEM_SIZE + (p + i + tmp) % MEM_SIZE) % MEM_SIZE)
struct					s_carriage
{
	int					player;			//номер игрока, породившего каретку//
	int					len_of_player;
	int					f;				//номер функции, которую будет выполнять//
	int					jump;			//количество байт, которые нужно будет «перешагнуть», чтобы оказаться на следующей операции//
	int					live;			//цикл, в котором в последний раз была выполнена операция live//
	int					cast;			//сколько циклов до выполнения действия//
	int					number;			//номер каретки//
	int					pos;			//позиция//
	unsigned char		r[REG_NUMBER][REG_SIZE];
	int					carry;			//0 = false; 1 = true//
	int					error;
	short				color;
	t_carriage			*next;
};

struct	 				s_op
{
	char				*name;
	unsigned char		nb_args;
	t_arg_type			args[3];
	unsigned char		opcode;
	unsigned int		cycle;
	char				*description;
	unsigned char		codage;
	unsigned char		lable;
};

struct					s_core
{
	unsigned char		*arena;
	unsigned char		color[MEM_SIZE];
	int					carrs_num;
	int					last_check;
	int					num_pl;
	int					dump;
	int					n[MAX_PLAYERS];
	int					live_in_p[MAX_PLAYERS];
	int					last_say_live;
	int					n_cycles;
	int					max_checks;
	int					num_lives;
	int					cycle_to_die;
	int					n_check;
	int					visual_flag;
	t_op				op_tab[17];
	t_player			*players;
	t_carriage			*carrs;
	t_win				*visual;
};

struct					s_player
{
	int					number;
	char				prog_name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	unsigned char		code[CHAMP_MAX_SIZE + 1];
	unsigned int		length;			//длина исполняемого кода//
	t_player			*next;
};

void					make_core2(t_core *a);
int						carret(t_carriage *c, t_core *a, unsigned char *s);
void					print_arena(t_core *a, int color);
void					fight(t_core *a, t_carriage *c);
int						check_cycles(t_core *a);
int						get_args(t_core *a, t_carriage *c, short arg[3], short num);
void					read_byte2(unsigned char *a, int pos, int pos2, unsigned char *num);
void					read_byte4(unsigned char *a, int pos, int pos2, unsigned char *num);
void					write_reg(unsigned char *r, unsigned char *c, int p, int t);
int						function_codage(t_core *arena, t_carriage *car, short *arg);
int						byte_cal(short *a, int i, t_core *s, t_carriage *c);
short					get_pos_arg(t_core *a, t_carriage *c, short arg[3], short num); /// считает позицию на арене аргумента num
void					free_all(t_core *a, char *s);
void					pass_cycle(t_core *a);

void					f1(t_core *a, t_carriage *c);
void					f2_f13(t_core *a, t_carriage *c, int f);
void					f3(t_core *a, t_carriage *c);
void					f4(t_core *a, t_carriage *c);
void					f5(t_core *a, t_carriage *c);
void					f6(t_core *a, t_carriage *c);
void					f7(t_core *a, t_carriage *c);
void					f8(t_core *a, t_carriage *c);
void					f9(t_core *a, t_carriage *c);
void					f10(t_core *a, t_carriage *c);
void					f11(t_core *a, t_carriage *c);
void					f12_f15_duplicate_carret(t_carriage *c, t_core *a, int pos);
void					f12_f15(t_core *a, t_carriage *c, int p);
void					f14(t_core *a, t_carriage *c);
void					f16(t_core *a, t_carriage *c);

#endif