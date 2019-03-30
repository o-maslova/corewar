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

# include <wchar.h>
# include "op.h"
# include "libft.h"
# include "ft_printf/ft_printf.h"
# include "typedef.h"
# include "visualization.h"

# define US_CHAR			unsigned char
# define T_P				t_player
# define S_T_P				sizeof(t_player)
# define PLAYER				t_player
# define VIS				a->visual
# define MOD(p, i, tmp)	((MEM_SIZE + (p + i + tmp) % MEM_SIZE) % MEM_SIZE)

struct					s_carriage
{
	int					player;
	int					len_of_player;
	int					f;
	int					jump;
	int					live;
	int					cast;
	int					number;
	int					pos;
	US_CHAR				r[REG_NUMBER][REG_SIZE];
	int					carry;
	int					error;
	short				color;
	t_carriage			*next;
};

struct					s_op
{
	char				*name;
	US_CHAR				nb_args;
	t_arg_type			args[3];
	US_CHAR				opcode;
	unsigned int		cycle;
	char				*description;
	US_CHAR				codage;
	US_CHAR				lable;
};

struct					s_core
{
	US_CHAR				*arena;
	US_CHAR				color[MEM_SIZE];
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
	T_P					*players;
	t_carriage			*carrs;
	t_win				*visual;
};

struct					s_player
{
	int					number;
	int					pos;
	char				prog_name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	US_CHAR				code[CHAMP_MAX_SIZE + 1];
	unsigned int		length;
	T_P					*next;
};

/*
** Functions for creating players
*/

int						parse_player(char *name, int *fd, int o, T_P *pl);
int						flag_n(char **argv, int n_arg, int *t, T_P *p);
int						flag_d(char **argv, int n_arg);
int						typeofarg(char *argv, int *t, int o, T_P *pl);
int						check_ret(int *t, int i);
T_P						*find_place(T_P *cur, T_P *new_cur,
									short pos[MAX_PLAYERS], int num);
T_P						*player_numb(T_P *player, int *shitty, int t);
T_P						*creat_player(T_P *player, int t, char *s);
T_P						*move_p(T_P *def, T_P *cur, short pos[MAX_PLAYERS], int num);
void					functions(t_carriage *c, t_core *a, int f);
void					check_args(int argc, char **argv, T_P *pl, int *d);
void					ft_error(T_P *p, int t, char *s);
void					do_this(T_P *p, int t, int *d);
uint32_t				revers(uint32_t n);
US_CHAR					*ft_strncpy2(US_CHAR *dst, const US_CHAR *src,
							size_t len);

int						carret(t_carriage *c, t_core *a, US_CHAR *s);
int						get_args(t_core *a, t_carriage *c, short arg[3],
							short num);
int						fun_codage(t_core *arena, t_carriage *car, short *arg);
int						byte_cal(short *a, int i, t_core *s, t_carriage *c);
short					get_pos_arg(t_core *a, t_carriage *c, short arg[3],
							short num);
void					make_core2(t_core *a);
void					write_player(T_P *p, US_CHAR *a, int t);
void					print_arena(t_core *a, int color);
void					fight(t_core *a, t_carriage *c);
void					visual_fight(t_core *a, t_carriage *c);
void					pass_cycle(t_core *a);
void					check_cycles(t_core *a);
void					read_byte2(US_CHAR *a, int pos, int pos2, US_CHAR *num);
void					read_byte4(US_CHAR *a, int pos, int pos2, US_CHAR *num);
void					write_reg(US_CHAR *r, US_CHAR *c, int p, int t);
void					free_all(t_core *a, char *s);
void					free_c(T_P *p, t_carriage *c, char *s);
void					free_p(T_P *p);

t_carriage				*make_carret(US_CHAR *a, T_P *p, t_carriage *c, int t);

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
void					f12_f15_dp_carret(t_carriage *c, t_core *a, int pos);
void					f12_f15(t_core *a, t_carriage *c, int p);
void					f14(t_core *a, t_carriage *c);
void					f16(t_core *a, t_carriage *c);

#endif
