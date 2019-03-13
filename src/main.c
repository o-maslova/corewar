/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmediany <bmediany@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 10:38:35 by bmediany          #+#    #+#             */
/*   Updated: 2019/02/01 10:38:36 by bmediany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>
#include "libft.h"
#include "op.h"
#include "corelib.h"
#include "visualization.h"

void	read_byte4(unsigned char *a, int pos, int pos2, unsigned char *num);

uint32_t	revers(uint32_t n)
{
	uint32_t	b;

	b = (n >> 24) | ((n & 0xff0000) >> 8) |
		((n & 0xff00) << 8) | (n << 24);
	return (b);
}

int	ft_type_codeage(t_core *arena, t_carriage *car, short *arg)
{
	int i;
	int error;

	i = 0;
	error = 0;
	while(i < arena->op_tab[car->f - 1].nb_args)
	{
		if (arg[i] == 0 || (arg[i] & arena->op_tab[car->f - 1].args[i]) != arg[i])
			error = 1;
		// if (arg[i] == 2)
		// 	arg[i] = arena->op_tab[car->f - 1].lable;
		// else if (arg[i] == 4)
		// 	arg[i] = 2;
		i++;
	}
	return (error);
}

int function_codage(t_core *arena, t_carriage *car, short *arg)
{
	int i;
	int codage;
	int one;

	i = 0;
	one = 128;
	codage = ((int)arena->arena[(car->pos + 1) % MEM_SIZE]);
	while(i < arena->op_tab[car->f - 1].nb_args)
	{
		if (codage >= one + (one / 2))
			arg[i] = 3;
		else if (codage >= one)
			arg[i] = 2;
		else if (codage >= (one / 2))
			arg[i] = 1;
		else
			arg[i] = 0;
		codage -= (arg[i] * (one / 2));
		if (arg[i] == 3)
			arg[i]++;
		i++;
		one /= 4;
	}
	return (ft_type_codeage(arena, car, arg));
}

unsigned char	*ft_strncpy2(unsigned char *dst, const unsigned char *src, size_t len)
{
	int l;

	l = -1;
	while (++l < (int)len)
	{
		if (l < (int)len)
			dst[l] = src[l];
	}
	return (dst);
}

void	free_p(t_player *p)
{
	t_player	*p2;
	while (p)
	{
		p2 = p->next;
		free(p);
		p = p2;
	}
}

void	ft_error(t_player *p, int t, char *s)
{
	t_player	*n;

	free_p(p);
	if (t == 0)
		//printf("Error: file %s must have .cor type\n", s);
	if (t == 1)
		//printf("Error: file %s not valide\n", s);
	if (t == 2)
		//printf("Error: file %s has too large a code. Max size: %i bytes\n", s, CHAMP_MAX_SIZE);
	if (t == 3)
		//printf("Error: exec code file %s not valide\n", s);
	if (t == 4)
		//printf("Error: %s\n", s);
	if (t < 0)
		//printf("Error: can't find file %s, or access is denied\n", s);
	exit(0);
}

void	free_c(t_player *p, t_carriage *c, char *s)
{
	t_carriage *h;

	while (c)
	{
		h = c->next;
		//printf("%s\n", p->prog_name);
		free(c);
		c = h;
	}
	ft_error(p, 4, s);
}

void	free_all(t_core *a, char *s)
{
	t_carriage	*c;
	t_player	*p;

	c = a->carrs;
	p = a->players;
	free(a);
	free_c(p, c, s);
}

int		check_ret(int *t, int i)
{
	close (*t);
	*t = i;
	return (-1);
}

t_player	*make_p2(t_player *p, int t, char *s)
{
	t_player	*n;
	t_player	*b;

	if (!(n = malloc(sizeof(t_player) * 1)))
		ft_error(p, 4, "malloc error");
	if (s)
		ft_strncpy(n->prog_name, s, PROG_NAME_LENGTH + 1);
	n->number = t;
	n->next = NULL;
	if (!p)
		return (n);
	while (p->next)
		p = p->next;
	p->next = n;
	return (n);
}

int		make_p3(int *t, t_player *pl, unsigned char *buff, uint32_t p)
{
	int i;

	i = read(*t, buff, COMMENT_LENGTH + 4);
	if (i != COMMENT_LENGTH + 4)
		return(check_ret(t, 1));
	ft_strncpy(pl->comment, (char *)buff, COMMENT_LENGTH + 1);
	i = read(*t, buff, CHAMP_MAX_SIZE);
	if (i != p)
		return(check_ret(t, 3));
	ft_strncpy2(pl->code, buff, p + 1);
	close (*t);
	*t = 0;
	return (1);
}

int		make_p(char *s, int *t, int o, t_player *pl)
{
	size_t			i;
	uint32_t		*p;
	unsigned char	buff[(PROG_NAME_LENGTH + COMMENT_LENGTH)];

	if ((*t = open(s, O_RDONLY)) < 0)
		return (-1);
	i = read(*t, buff, 4);
	p = (unsigned int *)buff;
	if (i < 4 || revers(p[0]) != COREWAR_EXEC_MAGIC)
		return (check_ret(t, 1));
	i = read(*t, buff, PROG_NAME_LENGTH + 4);
	if (i != PROG_NAME_LENGTH + 4)
		return (check_ret(t, 1));
	pl = make_p2(pl, o, (char *) buff);
	i = read(*t, buff, 4);
	p = (unsigned int *)buff;
	p[0] = revers(p[0]);
	if (i < 4 || p[0] > CHAMP_MAX_SIZE)
		return (check_ret(t, 2));
	pl->length = p[0];
	return (make_p3(t, pl, buff, p[0]));
}

int		check_p2(char *s, int *t, int o, t_player *pl)
{
	int	i;
	int	p;

	i = -1;
	if (ft_strcmp(s, "-n") == 0 && o == -1)
		return (2);
	if (ft_strcmp(s, "-d") == 0 && o == -1)
		return (4);
	if (ft_strcmp(s, "-v") == 0 && o == -1)
		return (8);
	p = -1;
	while (s[++i] && p == -1)
	{
		if (s[i] == '.' && ft_strcmp(s + i, ".cor") == 0 && s[i + 4] == '\0')
			p = 1;
	}
	if (p == -1)
		*t = 0;
	else
		p = make_p(s, t, o, pl);
	return (p);
}

int		flag_n(char **m, int o, int *t, t_player *p)
{
	int	i;

	i = -1;
	while (m[o] && m[o][++i])
		if (m[o][i] < '0' || m[o][i] > '9')
			return (3);
	i = atoi(m[o]);
	return (check_p2(m[++o], t, i, p));
}

int		flag_d(char **m, int o, int *t)
{
	int	i;

	i = -1;
	while (m[o] && m[o][++i])
		if (m[o][i] < '0' || m[o][i] > '9')
			return (5);
	i = atoi(m[o]);
	if (i < 0)
		i = 0;
	return (i);
}

int			move_p(t_player *m, t_player *n, int t, t_player *p)
{
	int			y;
	int			u;

	u = 0;
	y = 0;
	while(m->next && u != 2)
	{
		if (m == n)
			u++;
		if (++y == t)
			{
				if (u == 1)
					m = m->next;
				if (n == m->next)
					return (1);
				if (m->next && t == m->next->number)
				{
					n->number = -1;
					return (0);
				}
				p->next = n->next;
				n->next = m->next;
				m->next = n;
				u = 2;
			}
		else if (u != 2)
			m = m->next;
	}
	return (1);
}

t_player	*move_p2(t_player *o, int *c)
{
	int		y;
	int		l;
	t_player *p;

	y = 1;
	l = -1;
	p = o->next;
	while (p)
	{
		if (l == -1 || p->length > l)
			l = p->length;
		p->number = y;
		y++;
		p = p->next;
	}
	if (MEM_SIZE / (y - 1) < l)
		*c = -1;
	else
		*c = y - 1;
	p = o->next;
	free(o);
	return (p);
}

t_player	*player_numb(t_player *p, int *c, int t)
{
	t_player	*n;
	t_player	*m;
	t_player	*o;

	n = p->next;
	o = p;
	m = n;
	while (t != 0 && n != NULL)
	{
		if (n == NULL && t > 0)
		{
			t = 0;
			n = m;
			o = p;
		}
		if (n->number != -1)
			t += move_p(p, n, n->number, o);
		o = n;
		n = n->next;
	}
	o = move_p2(p, c);
	if (*c == -1)
		ft_error(o, 4, "malloc error 2");
	if (*c > MAX_PLAYERS)
		ft_error(o, 4, "Error: too many players");
	return (o);
}

void	null_arena(unsigned char *a)
{
	size_t	i;

	i = 0;
	while(i < MEM_SIZE)
	{
		a[i] = '\0';
		i++;
	}
}

void		write_player(t_player *p, unsigned char *a, int t)
{
	int	i;

	i = 0;
	while (i < p->length)
	{
		a[t] = p->code[i];
		t++;
		i++;
	}
}

t_carriage *make_carret2(t_player *p, int i, int l)
{
	t_carriage	*c;

	c = ft_memalloc(sizeof(t_carriage) * 1);
	c->player = (0xffffffff ^ p->number) + 1;
	c->len_of_player = p->length;
	read_byte4((unsigned char *)&c->player, 0, 0, c->r[0]);
	c->pos = l;
	c->jump = 0;
	c->carry = 0;
	c->cast = 0;
	c->live = 0;
	c->number = i;
	c->f = 0;
	return (c);
}

t_carriage *make_carret(unsigned char *a, t_player *p, t_carriage *c, int t)
{
	t_carriage *o;
	int			i;
	int			l;

	l = MEM_SIZE / t;
	i = 0;
	while(p)
	{
		o = make_carret2(p, i++, l * (p->number - 1));
		o->next = c;
		write_player(p, a, l * (p->number - 1));
		c = o;
		p = p->next;
	}
	return (c);
}

void	bit_print(int i)
{
	if (i < 1)
		return ;
	bit_print(i / 2);
	//printf("%i", i % 2);
}

int		byte_cal(short *a, int i, t_core *s, t_carriage *c)
{
	int	p;
	int	t;

	p = 0;
	t = 0;
	while (p < s->op_tab[c->f - 1].nb_args)
	{
		if (a[p] == 1)
		{
			t += 1;
			if (s->arena[(c->pos + t + 1) % MEM_SIZE] - 1 > 15)
				c->error++;
		}
		if (a[p] == 2)
			t += i;
		if (a[p] == 4)
			t += 2;
		p++;
	}
	return (t);
}

void	arg_size(short *a, short *s, int l)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (a[i] == 1)
			s[i] = 1;
		if (a[i] == 2)
			s[i] = l;
		if (a[i] == 4)
			s[i] = 2;
		i++;
	}
}

void	read_byte2(unsigned char *a, int pos, int pos2, unsigned char *num)
{
	int i;

	i = 0;

	while (i < 2)
	{
		num[(1 - i + pos) % MEM_SIZE] = a[pos2 % MEM_SIZE];
		i++;
		pos2++;
	}
}

void	read_byte4(unsigned char *a, int pos, int pos2, unsigned char *num)
{
		int i;

	i = 0;

	while (i < REG_SIZE)
	{
		num[(REG_SIZE - 1 - i + pos) % MEM_SIZE] = a[pos2 % MEM_SIZE];
		i++;
		pos2++;
	}
}

void	write_reg(unsigned char *r, unsigned char *c, int p, int t)
{
	int	i;

	i = 0;
	while (i < 4 && t > 0)
		r[i++] = 0;
	i = 0;
	if (t == -1)
		t = 0;
	while (i < REG_SIZE)
	{
		r[(p + i) % MEM_SIZE] = c[(t + i) % MEM_SIZE];
		i++;
	}
}

short get_pos_arg(t_core *a, t_carriage *c, short arg[3], short num) /// считает позицию на арене аргумента num
{
	unsigned int ar;
	short	pos;

	ar = 0;
	pos = c->pos + 1 + a->op_tab[c->f - 1].codage;
	while (ar < num)
	{
		if (arg[ar] == 1)
			pos += 1;
		else if (arg[ar] == 2)
			pos += a->op_tab[c->f - 1]. lable;
		else
			pos += 2;
		ar++;
	}
	return (pos);
}

int get_args(t_core *a, t_carriage *c, short arg[3], short num)//// в зависимости от типа аргумента считывает его байты с арены/регистара
{
	int ar;
	short	pos;

	ar = 0;
	pos = get_pos_arg(a, c, arg, num);
	if (arg[num] == 1)
	{
		ar = a->arena[pos % MEM_SIZE] - 1;
		if (ar > 16)
		{
			c->error += 1;
			return (0);
		}
		read_byte4(c->r[ar], 0, 0, (unsigned char *)&ar);
	}
	else if (arg[num] == 2)
	{
		if (a->op_tab[c->f - 1].lable == 4)
			read_byte4(a->arena, 0, pos, (unsigned char *)&ar);
		else{
			read_byte2(a->arena, 0, pos, (unsigned char *)&ar);
			if (ar > 0x8000)
				ar = ar - 0xffff - 1;
		}
	}
	else if (arg[num] == 4)
	{
		read_byte2(a->arena, 0, pos, (unsigned char *)&ar);
		if (ar > 0x8000)
			ar = ar - 0xffff - 1;
	}
	return (ar);
}

void	f1(t_core *a, t_carriage *c)
{
	int		i;
	short	p[1];

	c->live = a->n_cycles;
	p[0] = 2;
	i = get_args(a, c, p, 0);
	i *= -1;
	if (i <= a->num_pl && i > 0)
	{
		VIS->paint_arena[c->pos].i_live = 50;
		VIS->paint_arena[c->pos].color = VIS->clr[i - 1].st_clr;
		if (VIS->paint_arena[c->pos].color != VIS->paint_arena[c->pos].default_clr)
			VIS->paint_arena[c->pos].not_in_field = 1;
		a->live_in_p[i - 1] += 1;
		// printf("f1: player #%i\n", i);
		a->last_say_live = i;
		a->n[i - 1] = a->n_cycles;
		a->num_lives++;
	}
	//else
		//printf("f1: %i - error\n", i);
	c->jump = 5;
}

void	f2_f13(t_core *a, t_carriage *c, int f)
{
	short	arg[3];
	int		i;
	int		h;

	c->error = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, a, c) + 2;
	h = a->arena[get_pos_arg(a, c, arg, 1) % MEM_SIZE] - 1;
	if (c->error != 0)
		return ;
	i = get_args(a, c, arg, 0);
	if (arg[0] == 4)
	{
		if (f == 0 && i % IDX_MOD != i)
		{
			i %= IDX_MOD;
			read_byte4((unsigned char *)&i, c->pos + 2, 0, a->arena);
		}
		read_byte4(a->arena, 0, (MEM_SIZE + (c->pos + i) % MEM_SIZE) % MEM_SIZE, (unsigned char *)&i);
	}
	read_byte4((unsigned char *)&i, 0, 0, c->r[h]);
	c->carry = 0;
	if (i == 0)
		c->carry = 1;
	//printf("f2: r%i = %i\n", h + 1, i);
}

void	f3(t_core *a, t_carriage *c)
{
	short	arg[3];
	int		tmp;
	int		i;
	int		h;

	tmp = -1;
	c->error = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, a, c) + 2;
	if (c->error != 0)
		return ;
	i = a->arena[get_pos_arg(a, c, arg, 0) % MEM_SIZE] - 1;
	if (arg[1] == 1)
	{
		h = a->arena[get_pos_arg(a, c, arg, 1) % MEM_SIZE] - 1;
		write_reg(c->r[h], c->r[i], 0, 0);
		// printf("f3: with r%i to r%i write '%.2x%.2x%.2x%.2x'\n", i, h, c->r[i][0], c->r[i][1], c->r[i][2], c->r[i][3]);
		return ;
	}
	h = get_args(a, c, arg, 1);
	h %= IDX_MOD;
	write_reg(a->arena, c->r[i], (MEM_SIZE + (c->pos + h) % MEM_SIZE) % MEM_SIZE, 0);
	while (++tmp < 4)
	{
		VIS->paint_arena[(MEM_SIZE + (c->pos + h + tmp) % MEM_SIZE) % MEM_SIZE].is_st = 50;
		VIS->paint_arena[(MEM_SIZE + (c->pos + h + tmp) % MEM_SIZE) % MEM_SIZE].default_clr =
		VIS->clr[-(c->player) - 1].st_clr;;
	}
	//printf("f3: with r%i to a[%i] write '%.2x%.2x%.2x%.2x'\n", i, c->pos + h, c->r[i][0], c->r[i][1], c->r[i][2], c->r[i][3]);
}

void	f4(t_core *a, t_carriage *c)
{
	short			arg[3];
	unsigned int	i;
	unsigned int	h;
	int				p;

	c->error = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, a, c) + 2;
	p = a->arena[get_pos_arg(a, c, arg, 2) % MEM_SIZE] - 1;
	if (c->error != 0)
		return ;
	i = get_args(a, c, arg, 0);
	h = get_args(a, c, arg, 1);
	i = i + h;
	//printf("f4: %i + %i = %i to r[%i]\n", i - h, h, i, p);
	h = 0;
	while (h < REG_SIZE)
		c->r[p][h++] = 0;
	read_byte4((unsigned char *)&i, 0, 0, c->r[p]);
	c->carry = 0;
	if (i == 0)
		c->carry = 1;
}

void	f5(t_core *a, t_carriage *c)
{
	short			arg[3];
	unsigned int	i;
	unsigned int	h;
	int				p;

	c->error = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, a, c) + 2;
	p = a->arena[get_pos_arg(a, c, arg, 2) % MEM_SIZE] - 1;
	if (c->error != 0)
		return ;
	i = get_args(a, c, arg, 0);
	h = get_args(a, c, arg, 1);
	i = i - h;
	//printf("f5: %i - %i = %i to r[%i]\n", i + h, h, i, p);
	h = 0;
	while (h < REG_SIZE)
		c->r[p][h++] = 0;
	read_byte4((unsigned char *)&i, 0, 0, c->r[p]);
	c->carry = 0;
	if (i == 0)
		c->carry = 1;
}

void	f6(t_core *a, t_carriage *c)
{
	short			arg[3];
	unsigned int	i;
	unsigned int	h;
	int				p;

	p = 0;
	c->error = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, a, c) + 2;
	i = get_args(a, c, arg, 0);
	p = get_args(a, c, arg, 1);
	h = a->arena[(get_pos_arg(a, c, arg, 2)) % MEM_SIZE] - 1;
	if (c->error != 0 || h >= REG_NUMBER)
		return ;
	//printf("f6: %i & %i = %i to r[%i]\n", i, p, i & p, h);
	i = i & p;
	p = 0;
	while (p < REG_SIZE)
		c->r[h][p++] = 0;
	read_byte4((unsigned char *)&i, 0, 0, c->r[h]);
	c->carry = 0;
	if (i == 0)
		c->carry = 1;
}


void	f7(t_core *a, t_carriage *c)    ///3820
{
	short			arg[3];
	unsigned int	i;
	unsigned int	h;
	int				p;

	p = 0;
	c->error = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, a, c) + 2;
	i = get_args(a, c, arg, 0);
	p = get_args(a, c, arg, 1);
	h = a->arena[(get_pos_arg(a, c, arg, 2)) % MEM_SIZE] - 1;
	if (c->error != 0 || h >= REG_NUMBER)
		return ;
	//printf("f7: %i | %i = %i to r[%i]\n", i, p, i | p, h);
	i = i | p;
	p = 0;
	while (p < REG_SIZE)
		c->r[h][p++] = 0;
	read_byte4((unsigned char *)&i, 0, 0, c->r[h]);
	c->carry = 0;
	if (i == 0)
		c->carry = 1;
}


void	f8(t_core *a, t_carriage *c)
{
	short			arg[3];
	unsigned int	i;
	unsigned int	h;
	int				p;

	p = 0;
	c->error = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, a, c) + 2;
	i = get_args(a, c, arg, 0);
	p = get_args(a, c, arg, 1);
	h = a->arena[(get_pos_arg(a, c, arg, 2)) % MEM_SIZE] - 1;
	if (c->error != 0 || h >= REG_NUMBER)
		return ;
	//printf("f7: %i ^ %i = %i to r[%i]\n", i, p, i ^ p, h);
	i = i ^ p;
	p = 0;
	while (p < REG_SIZE)
		c->r[h][p++] = 0;
	read_byte4((unsigned char *)&i, 0, 0, c->r[h]);
	c->carry = 0;
	if (i == 0)
		c->carry = 1;
}

void	f9(t_core *a, t_carriage *c)
{
	int		i;
	short	p[1];

	c->jump = 3;
	i = 0;
	p[0] = 2;
	if (c->carry != 0)
	{
		i = get_args(a, c, p, 0);
		c->jump = i % IDX_MOD;
		//printf("f9: jump = %i\n", c->jump);
	}
	//else
		//printf("f9: carry = 0\n");
}

void	f10(t_core *a, t_carriage *c)
{
	short	arg[3];
	int		p;
	int		i;
	int		h;

	c->error = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1]. lable, a, c) + 2;
	p = a->arena[get_pos_arg(a, c, arg, 2) % MEM_SIZE] - 1;
	if (c->error != 0)
		return ;
	i = get_args(a, c, arg, 0);
	h = get_args(a, c, arg, 1);
	if (arg[0] == 4)
		read_byte4(a->arena, 0, (MEM_SIZE + c->pos + (i % IDX_MOD)) % MEM_SIZE, (unsigned char *)&i);
	//printf("f10: with a[%i] (%i + %i) to r[%i] write ", i + h, i, h, p);
	i = (i + h) % IDX_MOD;
	write_reg(c->r[p], a->arena, 0, (MEM_SIZE + c->pos + i) % MEM_SIZE);
	//printf("'%.2x%.2x%.2x%.2x'\n", c->r[p][0], c->r[p][1], c->r[p][2], c->r[p][3]);
}

void	f11(t_core *a, t_carriage *c)
{
	short	arg[3];
	int		tmp;
	int		i;
	int		h;
	int		p;

	tmp = -1;
	c->error = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1]. lable, a, c) + 2;
	if (c->error != 0)
		return ;
	i = a->arena[get_pos_arg(a, c, arg, 0) % MEM_SIZE] - 1;
	h = get_args(a, c, arg, 1);
	p = get_args(a, c, arg, 2);
	if (arg[1] == 4)
		read_byte4(a->arena, 0, c->pos + (h % IDX_MOD), (unsigned char *)&h);
	h = (h + p) % IDX_MOD;
	write_reg(a->arena, c->r[i], (MEM_SIZE + c->pos + h) % MEM_SIZE, 0);
	while (++tmp < 4)
	{
		VIS->paint_arena[(MEM_SIZE + (c->pos + h + tmp) % MEM_SIZE) % MEM_SIZE].is_st = 50;
		VIS->paint_arena[(MEM_SIZE + (c->pos + h + tmp) % MEM_SIZE) % MEM_SIZE].default_clr = 
		VIS->clr[-(c->player) - 1].st_clr;
		// dprintf(g_fd, "POSITION	 %d, player = %d\n", (MEM_SIZE + (c->pos + h + tmp) % MEM_SIZE) % MEM_SIZE, c->player);
	}
	//printf("f11: with r%i write '%.2x%.2x%.2x%.2x' to a[%i]\n", i + 1, c->r[i][0], c->r[i][1], c->r[i][2], c->r[i][3], c->pos + h);
}

void	f12_f15_duplicate_carret(t_carriage *c, t_core *a, int pos)
{
	t_carriage	*new;
	int			i;
	int			p;

	if (!(new = malloc(sizeof(t_carriage))))
		free_all(a, "malloc error");
	new->player = c->player;
	new->len_of_player = c->len_of_player;
	//new->f = 0;
	new->jump = 0;
	new->live = c->live;
	new->cast = 0;
	new->number = a->carrs->number + 1;
	new->pos = (MEM_SIZE + (c->pos + pos) % MEM_SIZE) % MEM_SIZE;
	new->f = a->arena[new->pos];
	if (new->f < 17 && new->f > 0)
		new->cast = a->op_tab[new->f - 1].cycle - 1;
	else
		new->cast = 0;
	////printf("new pos = %i\n", new->pos);
	new->carry = c->carry;
	i = 0;
	while (i < REG_NUMBER)
	{
		p = 0;
		while (++p <= REG_SIZE)
			new->r[i][p -1] = c->r[i][p - 1];
		i++;
	}
	new->next = a->carrs;
	a->carrs = new;
}

void	f12_f15(t_core *a, t_carriage *c, int p)
{
	int		i;
	short	g[1];
	t_carriage *c2;

	c->jump = 3;
	g[0] = 2;
	i = get_args(a, c, g, 0);
	if (p == 1)
	{
		f12_f15_duplicate_carret(c, a, i % IDX_MOD);
		//printf("f:12 new carret with pos = %i\n", i % IDX_MOD);
	}
	else
	{
		f12_f15_duplicate_carret(c, a, i);
		//printf("f:15 new carret with pos = %i + %i\n", c->pos, i);
		//printf("n_cycles = %i\n", a->n_cycles);
		//sleep(10);
	}
// 	c2 = a->carrs;
// 	while (c2)
// 	{
// 		//printf("carret #%i stay in a[%i]. f:%i cast = %d\n", c2->number, c2->pos, a->arena[c2->pos], c2->cast);
// 		c2 = c2->next;
// 	}
// 	sleep(5);
}

void	f14(t_core *a, t_carriage *c)
{
	short	arg[3];
	int		p;
	int		i;
	int		h;

	c->error = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1]. lable, a, c) + 2;
	//printf(">>>>>>>>%i\n", c->jump);
	p = a->arena[get_pos_arg(a, c, arg, 2) % MEM_SIZE] - 1;
	if (c->error != 0)
		return ;
	i = get_args(a, c, arg, 0);
	h = get_args(a, c, arg, 1);
	if (arg[0] == 4)
		read_byte4(a->arena, 0, c->pos + (i % IDX_MOD), (unsigned char *)&i);
	//printf("f10: with a[%i] (%i + %i) to r[%i] write ", i + h, i, h, p);
	i = i + h;
	write_reg(c->r[p], a->arena, 0, (MEM_SIZE + ((c->pos + i) % MEM_SIZE)) % MEM_SIZE);
	//printf("'%.2x%.2x%.2x%.2x'\n", c->r[p][0], c->r[p][1], c->r[p][2], c->r[p][3]);
}

void	f16(t_core *a, t_carriage *c)
{
	short	arg[3];
	int		h;

	c->error = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1]. lable, a, c) + 2;
	if (c->error != 0)
		return ;
	h = get_args(a, c, arg, 0);
	h %= 256;
	write(1, &h, 1);
}

void	functions2(t_carriage *c, t_core *a, int f, int i)
{
	if (f == 12)
		f12_f15(a, c, 1);
	if (f == 13)
		f2_f13(a, c, 1);
	if (f == 14)
		f14(a, c);
	if (f == 15)
		f12_f15(a, c, 0);
	if (f == 16)
		f16(a, c);
}

void	functions(t_carriage *c, t_core *a, int f, int i)
{
	if (f == 1)
		f1(a, c);
	if (f == 2)
		f2_f13(a, c, 0);
	if (f == 3)
		f3(a, c);
	if (f == 4)
		f4(a, c);
	if (f == 5)
		f5(a, c);
	if (f == 6)
		f6(a, c);
	if (f == 7)
		f7(a, c);
	if (f == 8)
		f8(a, c);
	if (f == 9)
		f9(a, c);
	if (f == 10)
		f10(a, c);
	if (f == 11)
		f11(a, c);
	if (f > 11)
		functions2(c, a, f, i);
}

int		carret(t_carriage *c, t_core *a, unsigned char *s, int i)
{
	////printf("carret #%i stay in a[%i]. f:%i cast = %d\n", c->number, c->pos, a->arena[c->pos], c->cast);
	if (c->f == 0 && c->cast == 0)
	{
		if (s[c->pos] <= 16 && s[c->pos] > 0)
		{
			c->f = s[c->pos];
			c->cast = a->op_tab[c->f - 1].cycle - 1;
		}
		else
		{
			c->pos = (c->pos + 1) % MEM_SIZE;//сдвигаемся на 1 
			if (s[c->pos] <= 16 && s[c->pos] > 0)
			{
				c->f = s[c->pos];
				c->cast = a->op_tab[c->f - 1].cycle - 1;
			}
		}
		// //printf("function #%i  >  %i\n", c->f, c->cast + 1);
		return (0);
	}
	if (c->f != 0 && c->cast == 0)
	{
		//if (c->f == 15)
			//printf("c->number = %i\n", c->number);
		// if (c->number == 1)
		// {
		// 	//printf("carret #%i stay in a[%i]. f:%i cast = %d cycle = %d\n", c->number, c->pos, a->arena[c->pos], c->cast, a->n_cycles);
		// }
		functions(c, a, c->f, -1);
		c->pos = (MEM_SIZE + (c->pos + c->jump) % MEM_SIZE) % MEM_SIZE;
		c->f = 0;
		c->jump = 0;
		if (s[c->pos] <= 16 && s[c->pos] > 0)
		{
			c->f = s[c->pos];
			c->cast = a->op_tab[c->f - 1].cycle - 1;
		}
		// if (c->error != 0)
		// {
		// 	c->error = 0;
		// 	return (0);
		// }
		// else
		return (1);		
	}
	if (c->cast > 0)
	{
		c->cast--;
		// //printf("function #%i  >  %i\n", c->f, c->cast + 1);
	}
	return (0);
}

void	check_cycles_carret(t_core *a, t_carriage *c, t_carriage *c2)
{
	char	buff[1];
	int		i;

	i = 0;
	while (c)
	{
		if (c->live < a->last_check)
		{
			i++;
			////printf("carret a[%i] die\n", c->pos);
			//sleep(5);
			if (c == a->carrs)
			{
				a->carrs = c->next;
				free(c);
				c = a->carrs;
				c2 = a->carrs;
			}
			else
			{
				c2->next = c->next;
				free(c);
				c = c2->next;
			}
		}
		else if (c2 == c)
			c = c->next;
		else
		{
			c = c->next;
			c2 = c2->next;
		}
	}
	// printf("del | %d | carrets\n", i);
	// read(0, buff, 1);
}

void	check_cycles(t_core *a)
{
	// a->n_cycles++;
	//printf("n_c = %d | l_c = %d | c_t_d = %d | n_c-l_c = %d\n", a->n_cycles, a->last_check, a->cycle_to_die, a->n_cycles - a->last_check);
	if (a->n_cycles - a->last_check == a->cycle_to_die)
	{
		ft_bzero(a->live_in_p, (sizeof(int) * 4));
		//printf("cycle_check\nnb_l = %d\n", a->num_lives);
		//sleep(5);
		if (a->num_lives >= NBR_LIVE)
		{
			a->cycle_to_die -= CYCLE_DELTA;
			a->max_checks = 0;
		}
		else
			a->max_checks++;
		if (a->max_checks == MAX_CHECKS)
		{
			a->cycle_to_die -= CYCLE_DELTA;
			a->max_checks = 0;
		}
		check_cycles_carret(a, a->carrs, a->carrs);
		a->last_check = a->n_cycles;
	}
}

//omaslova изменила функцию ниже для визуализации

void	print_arena(t_core *a)
{
	int		i;
	int		row;
	int		that_color;

	i = -1;
	row = START_ROW - 1;
	while (++i < MEM_SIZE)
	{
		if ((i % MAINW_ROWS) == 0)
			wmove(VIS->main_win, ++row, 4);
		make_frame(VIS->main_win, COLOR_PAIR(FRAME));
		make_frame(VIS->info_win, COLOR_PAIR(FRAME));
		that_color = VIS->paint_arena[i].is_st ? COLOR_PAIR(VIS->paint_arena[i].color)
		| A_BOLD | A_UNDERLINE : COLOR_PAIR(VIS->paint_arena[i].color);
		wattron(VIS->main_win, that_color);
		wprintw(VIS->main_win, "%.2x", a->arena[i]);
		wattroff(VIS->main_win, that_color);
		waddch(VIS->main_win, ' ');
		if (VIS->paint_arena[i].is_st > 0)
			VIS->paint_arena[i].is_st--;
		if (VIS->paint_arena[i].i_live > 0)
			VIS->paint_arena[i].i_live--;
	}
	wrefresh(VIS->main_win);
	// wprintw(a->visual_flag->main_win, "\n\n\n\n");
}

void	print_cycle(t_core *a, t_carriage *c)
{
	static int	v_time;
	int		o;

	if (v_time == 0)
		VIS->start = clock();
	a->carrs_num = 0;
	c = a->carrs;
	while(c)
	{
		o = carret(c, a, a->arena, 0);
		// if (o == 1)
		// 	carret(c, a, a->arena, 0);
		c = c->next;
		a->carrs_num++;
	}
	check_cycles(a);
	if (a->n_cycles == a->dump)
	{
		put_colors(a);
		print_arena(a);
		print_info_frame(a);
		VIS->if_run = false;
	}
	a->n_cycles++;
	if (v_time == 0)
		VIS->end = clock();
	v_time++;
	// dprintf(g_fd, "\ntime_1 = %lu\n", (a->visual->end - a->visual->start));
	// dprintf(g_fd, "time_2 = %f\n\n", (double)((a->visual->end - a->visual->start) / CLOCKS_PER_SEC));
}

void	check_cyc_per_sec(t_core *a, char ch)
{
	if (ch == MINUS_BIG)
		VIS->c_per_s -= BIG_STEP;
	if (ch == PLUS_BIG)
		VIS->c_per_s += BIG_STEP;
	if (ch == MINUS_SMALL)
		VIS->c_per_s -= SMALL_STEP;
	if (ch == PLUS_SMALL)
		VIS->c_per_s += SMALL_STEP;
	if (VIS->c_per_s < 0)
		VIS->c_per_s = 0;
	if (VIS->c_per_s > 1000)
		VIS->c_per_s = 1000;
}

void	fight(t_core *a, t_carriage *c)
{
	int		ch;
	int		k;
	int		o;

	k = 1;
	system("clear");
	initialize(a);
	print_cycle(a, c);
	VIS->if_run = 1;
	while (a->cycle_to_die > 0 && a->carrs)
	{
		ch = getch();
		check_cyc_per_sec(a, ch);
		if (ch == RUN)
		{
			VIS->if_run = !VIS->if_run;
			print_cycle(a, c);
		}
		if (ch == ONE_CYCLE_PASS)
		{
			print_cycle(a, c);
			VIS->if_run = false;
		}
		if (VIS->if_run)
			print_cycle(a, c);
		// print_info_frame(a);
	}
	dprintf(g_fd, "WINNER - PLAYER №%i\n", a->last_say_live);
}

t_core	*make_core(t_carriage *c, unsigned char *s, t_player *p, int *d)
{
	t_core	*a;

	if (!(a = malloc(sizeof(t_core))))
		free_c(p, c, "malloc error");
	a->arena = s;
	a->visual_flag = d[1];
	a->dump = d[0];
	a->n_cycles = 0;
	a->num_lives = 0;
	a->max_checks = 0;
	a->cycle_to_die = CYCLE_TO_DIE;
	a->n_check = 0;
	a->last_check = 0;
	make_core2(a);
	a->players = p;
	a->carrs = c;
	return (a);
}

void	do_this(t_player *p, int t, int *d)
{
	t_carriage		*c;
	t_core			*arena;
	unsigned char	a[MEM_SIZE];

	null_arena(a);
	c = make_carret(a, p, NULL, t);
	arena = make_core(c, a, p, d);
	arena->num_pl = t;
	arena->last_say_live = t;
	fight(arena, NULL);
}

void	check_p(int i, char **m, t_player *p, int *d)
{
	int	o;
	int	h;
	int t;

	o = 0;
	t = 0;
	h = 1;
	p = make_p2(NULL, -1, NULL);
	while (++o < i && h != -1)
	{
		h = check_p2(m[o], &t, -1, p);
		if (h == 2 && o + 2 < i)
		{
			h = flag_n(m, ++o, &t, p);
			o++;
		}
		if (h == 8)
			d[1] = 1;
		if (h == 4 && o + 1 < i)
			d[0] = flag_d(m, ++o, &t);
		if (h == 5 || (h == 4 && o >= i))
			ft_error(p, 4, "flag -d not valid");
		if (h == 3 || (h == 2 && o + 2 >= i))
			ft_error(p, 4, "flag -n not valid");
		if (h == -1)
			ft_error(p, t, m[o]);
	}
	if (!p->next)
		ft_error(p, 4, "Hey, where are the fighters?");
	p = player_numb(p, &t, 1);
	do_this(p, t, d);
}

int		main(int ac, char **av)
{
	int	d[2];

	d[0] = -1;
	d[1] = -1;

	g_fd = open("log", O_RDWR | O_TRUNC | O_CREAT);
	if (ac < 2)
		printf("Error: no arguments\n");
	else if (ac > MAX_ARGS_NUMBER + 1)
		printf("Error: tomach arguments\n");
	else
		check_p(ac, av, NULL, d);
	return 0;
}