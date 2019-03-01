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

int	ft_type_codeage(t_core *arena, carriage_t *car, short *arg)
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

int function_codage(t_core *arena, carriage_t *car, short *arg)
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

void	free_p(player_t *p)
{
	player_t	*p2;
	while (p)
	{
		p2 = p->next;
		free(p);
		p = p2;
	}
}

void	ft_error(player_t *p, int t, char *s)
{
	player_t	*n;

	free_p(p);
	if (t == 0)
		printf("Error: file %s must have .cor type\n", s);
	if (t == 1)
		printf("Error: file %s not valide\n", s);
	if (t == 2)
		printf("Error: file %s has too large a code. Max size: %i bytes\n", s, CHAMP_MAX_SIZE);
	if (t == 3)
		printf("Error: exec code file %s not valide\n", s);
	if (t == 4)
		printf("Error: %s\n", s);
	if (t < 0)
		printf("Error: can't find file %s, or access is denied\n", s);
	exit(0);
}

void	free_c(player_t *p, carriage_t *c, char *s)
{
	carriage_t *h;

	while (c)
	{
		h = c->next;
		printf("%s\n", p->prog_name);
		free(c);
		c = h;
	}
	ft_error(p, 4, s);
}

void	free_all(t_core *a, char *s)
{
	carriage_t	*c;
	player_t	*p;

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

player_t	*make_p2(player_t *p, int t, char *s)
{
	player_t	*n;
	player_t	*b;

	if (!(n = malloc(sizeof(player_t) * 1)))
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

int		make_p3(int *t, player_t *pl, unsigned char *buff, uint32_t p)
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

int		make_p(char *s, int *t, int o, player_t *pl)
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

int		check_p2(char *s, int *t, int o, player_t *pl)
{
	int	i;
	int	p;

	i = -1;
	if (ft_strcmp(s, "-n") == 0 && o == -1)
		return (2);
	if (ft_strcmp(s, "-d") == 0 && o == -1)
		return (4);
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

int		flag_n(char **m, int o, int *t, player_t *p)
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

int			move_p(player_t *m, player_t *n, int t, player_t *p)
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

player_t	*move_p2(player_t *o, int *c)
{
	int		y;
	int		l;
	player_t *p;

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

player_t	*player_numb(player_t *p, int *c, int t)
{
	player_t	*n;
	player_t	*m;
	player_t	*o;

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

void		write_player(player_t *p, unsigned char *a, int t)
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

carriage_t *make_carret2(player_t *p, int i, int l)
{
	carriage_t	*c;

	c = malloc(sizeof(carriage_t) * 1);
	c->player = (0xffffffff ^ p->number) + 1;
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

carriage_t *make_carret(unsigned char *a, player_t *p, carriage_t *c, int t)
{
	carriage_t *o;
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
	printf("%i", i % 2);
}

int		byte_cal(short *a, int i, short *s)
{
	int	p;
	int	t;

	p = 0;
	t = 0;
	while (p < 3)
	{
		if (a[p] == 1)
			t += 1;
		if (s && a[p] == 1)
			s[p] = 1;
		if (a[p] == 2)
			t += i;
		if (s && a[p] == 2)
			s[p] = i;
		if (a[p] == 4)
			t += 2;
		if (s && a[p] == 4)
			s[p] = 4;
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

void	f1(t_core *a, carriage_t *c)
{
	int	i;

	c->live = a->n_cycles;
	i = 0;
	read_byte2(a->arena, 0, c->pos + 1, (unsigned char *)&i);
	if (i <= a->num_pl && i > 0)
		a->last_say_live = i;
	c->jump = 3;
}

void	f2(t_core *a, carriage_t *c, int i, int h)
{
	short	arg[3];

	i = function_codage(a, c, arg); //если верно - нулюет i//
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, NULL) + 2;
	h = a->arena[(c->pos + 6) % MEM_SIZE] - 1;
	if (arg[1] == 3)
		h = a->arena[(c->pos + 4) % MEM_SIZE] - 1;
	if (i == 1 || h >= REG_NUMBER)
		return ;
	if (arg[0] == 4)
	{
		write_reg(c->r[h], a->arena, 0, c->pos + 2);
		return ;
	}
	read_byte2(a->arena, 0, c->pos + 2, (unsigned char *)&i);
	if (i % IDX_MOD != i)
	{
		i %= IDX_MOD;
		read_byte2((unsigned char *)&i, c->pos + 2, 0, a->arena);
	}
	write_reg(c->r[h], a->arena, 0, c->pos + i);
	c->carry = 0;
	if (i == 0)
		c->carry = 1;
}

void	f3(t_core *a, carriage_t *c)
{
	short	arg[3];
	int		i;
	int		h;
	int		p;

	i = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, NULL) + 2;
	h = a->arena[(c->pos + 3) % MEM_SIZE] - 1;
	p = a->arena[(c->pos + 2) % MEM_SIZE] - 1;
	if (i == 1 || p >= REG_NUMBER || (arg[1] == 1 && h >= REG_NUMBER ))
		return ;
	if (arg[1] == 1)
	{
		write_reg(c->r[h], c->r[p], 0, 0);
		return ;
	}
	read_byte2(a->arena, 0, c->pos + 3, (unsigned char *)&i);
	i %= IDX_MOD;
	write_reg(a->arena, c->r[p], c->pos + i, -1);
}

void	f4(t_core *a, carriage_t *c)
{
	short			arg[3];
	int				g;
	unsigned int	i;
	unsigned int	h;
	int				p;

	p = 0;
	g = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, NULL) + 2;
	i = a->arena[(c->pos + 2) % MEM_SIZE] - 1;
	p = a->arena[(c->pos + 3) % MEM_SIZE] - 1;
	h = a->arena[(c->pos + 4) % MEM_SIZE] - 1;
	if (g == 1 || h >= REG_NUMBER || i >= REG_NUMBER || p >= REG_NUMBER)
		return ;
	read_byte4(c->r[i], 0, 0, (unsigned char *)&i);
	read_byte4(c->r[p], 0, 0, (unsigned char *)&p);
	i = i + p;
	p = 0;
	while (p < REG_SIZE)
		c->r[h][p++] = 0;
	read_byte4(c->r[h], 0, 0, (unsigned char *)&i);
	c->carry = 0;
	if (i == 0)
		c->carry = 1;
}

void	f5(t_core *a, carriage_t *c)
{
	short			arg[3];
	int				g;
	unsigned int	i;
	unsigned int	h;
	int				p;

	p = 0;
	g = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, NULL) + 2;
	i = a->arena[(c->pos + 2) % MEM_SIZE] - 1;
	p = a->arena[(c->pos + 3) % MEM_SIZE] - 1;
	h = a->arena[(c->pos + 4) % MEM_SIZE] - 1;
	if (g == 1 || h >= REG_NUMBER || i >= REG_NUMBER || p >= REG_NUMBER)
		return ;
	read_byte4(c->r[i], 0, 0, (unsigned char *)&i);
	read_byte4(c->r[p], 0, 0, (unsigned char *)&p);
	i = i - p;
	p = 0;
	while (p < REG_SIZE)
		c->r[h][p++] = 0;
	read_byte4(c->r[h], 0, 0, (unsigned char *)&i);
	c->carry = 0;
	if (i == 0)
		c->carry = 1;
}

void	f9(t_core *a, carriage_t *c)
{
	int		i;

	if (c->pos + 2 >= MEM_SIZE) //если это край карты, и невозможно считать два байта для Т_ДИР - ошибка//
	{
		c->jump = 3;
		return ;
	}
	if (c->carry == 0)   //если каретка на false - не прыгаем//
		c->jump = 3;
	else
	{

		read_byte2(a->arena, 0, c->pos + 1, (unsigned char *)&i);
		c->jump = i % IDX_MOD;
	}
}

void	f10(t_core *a, carriage_t *c)
{
	short	arg[3];
	short	size[3];
	int		p;
	int		i;
	int		h;

	i = function_codage(a, c, arg);
	p = 0;
	c->jump = byte_cal(arg, a->op_tab[c->f - 1]. lable, size) + 2;
	h = a->arena[(c->pos + 2 + size[0] + size[1]) % MEM_SIZE] - 1;
	if (i == 1 || h >= REG_NUMBER)
		return ;
	if (arg[0] == 1 && a->arena[(c->pos + 2) % MEM_SIZE] - 1 >= REG_NUMBER)
		read_byte4(c->r[a->arena[(c->pos + 2) % MEM_SIZE]], 0, 0, (unsigned char *)&i);
	else if (arg[0] == 1)
		return ;
	else
		read_byte2(a->arena, 0, c->pos + 2, (unsigned char *)&i);
	if (arg[1] == 1 && a->arena[(c->pos + 2 + size[0]) % MEM_SIZE] - 1 >= REG_NUMBER)
		read_byte4(c->r[a->arena[(c->pos + 2 + size[0]) % MEM_SIZE]], 0, 0, (unsigned char *)&p);
	else if (arg[1] == 1)
		return ;
	else
		read_byte2(a->arena, 0, c->pos + 2 + size[0], (unsigned char *)&p);
	if (arg[0] == 4)
		read_byte4(a->arena, 0, c->pos + (i % IDX_MOD), (unsigned char *)&i);
	i = (i + p) % IDX_MOD;
	write_reg(c->r[h], a->arena, 0, c->pos + i);
}

void	f11(t_core *a, carriage_t *c)
{
	short	arg[3];
	short	size[3];
	int		p;
	int		i;
	int		h;

	i = function_codage(a, c, arg);
	p = 0;
	c->jump = byte_cal(arg, a->op_tab[c->f - 1]. lable, size) + 2;
	h = a->arena[(c->pos + 2) % MEM_SIZE] - 1;
	if (i == 1 || h >= REG_NUMBER)
		return ;
	if (arg[1] == 1 && a->arena[(c->pos + 3) % MEM_SIZE] - 1 >= REG_NUMBER)
		read_byte4(c->r[a->arena[(c->pos + 3) % MEM_SIZE]], 0, 0, (unsigned char *)&i);
	else if (arg[1] == 1)
		return ;
	else
		read_byte2(a->arena, 0, c->pos + 3, (unsigned char *)&i);
	if (arg[2] == 1  && a->arena[(c->pos + 3 + size[1]) % MEM_SIZE] - 1 >= REG_NUMBER)
		read_byte4(c->r[a->arena[(c->pos + 3 + size[1]) % MEM_SIZE]], 0, 0, (unsigned char *)&p);
	else if (arg[2] == 1)
		return ;
	else
		read_byte2(a->arena, 0, c->pos + 3 + size[1], (unsigned char *)&p);
	if (arg[1] == 4)
		read_byte4(a->arena, 0, c->pos + (i % IDX_MOD), (unsigned char *)&i);
	i = (i + p) % IDX_MOD;
	p = 0;
	read_byte4(c->r[h], c->pos + i, 0, a->arena);
}

void	f12_15_duplicate_carret(carriage_t *c, t_core *a, int pos)
{
	carriage_t	*new;
	int			i;
	int			p;

	if (!(new = malloc(sizeof(carriage_t))))
		free_all(a, "malloc error");
	new->player = c->player;
	new->f = 0;
	new->jump = 0;
	new->live = c->live;
	new->cast = 0;
	new->number = a->carrs->number + 1;
	new->pos = (c->pos + pos) % MEM_SIZE;
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

void	f12_15(t_core *a, carriage_t *c, int p)
{
	int		i;

	c->jump = 3;
	i = 0;
	read_byte2(a->arena, 0, c->pos + 1, (unsigned char *)&i);
	if (p == 1)
		f12_15_duplicate_carret(c, a, i % IDX_MOD);
	else
		f12_15_duplicate_carret(c, a, i);
}

void	f13(t_core *a, carriage_t *c)
{
	short	arg[3];
	short	size[3];
	int		i;
	int		h;

	i = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1]. lable, size) + 2;
	h = a->arena[(c->pos + size[0] + 2) % MEM_SIZE] - 1;
	if (i == 1 || h >= REG_NUMBER)
		return ;
	if (arg[0] == 4)
	{
		write_reg(c->r[h], a->arena, 0, c->pos + 2);
		return ;
	}
	read_byte2(a->arena, 0, c->pos + 2, (unsigned char *)&i);
	write_reg(c->r[h], a->arena, 0, c->pos + i);
	c->carry = 0;
	if (i == 0)
		c->carry = 1;
}

void	f14(t_core *a, carriage_t *c)
{
	short	arg[3];
	short	size[3];
	int		i;
	int		p;
	int		h;

	i = function_codage(a, c, arg);
	p = 0;
	c->jump = byte_cal(arg, a->op_tab[c->f - 1]. lable, size) + 2;
	h = a->arena[(c->pos + 2 + size[0] + size[1]) % MEM_SIZE] - 1;
	if (i == 1 || h >= REG_NUMBER)
		return ;
	if (arg[0] == 1 && a->arena[(c->pos + 2) % MEM_SIZE] - 1 >= REG_NUMBER)
		read_byte4(c->r[a->arena[(c->pos + 2) % MEM_SIZE]], 0, 0, (unsigned char *)&i);
	else if (arg[0] == 1)
		return ;
	else
		read_byte2(a->arena, 0, c->pos + 2, (unsigned char *)&i);
	if (arg[1] == 1 && a->arena[(c->pos + 2 + size[0]) % MEM_SIZE] - 1 >= REG_NUMBER)
		read_byte4(c->r[a->arena[(c->pos + 2 + size[0] % MEM_SIZE)]], 0, 0, (unsigned char *)&p);
	else if (arg[1] == 1)
		return ;
	else
		read_byte2(a->arena, 0, c->pos + 2 + size[0], (unsigned char *)&p);
	if (arg[0] == 4)
		read_byte4(a->arena, 0, c->pos + (i % IDX_MOD), (unsigned char *)&i);
	i = i + p;
	write_reg(c->r[h], a->arena, 0, c->pos + i);
}

////////////////////////////////

short get_pos_arg(t_core *a, carriage_t *c, short arg[3], short num) /// считает позицию на арене аргумента num
{
	unsigned int ar;
	short	pos;

	ar = 0;
	pos = c->pos + 2;
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

unsigned int get_args(t_core *a, carriage_t *c, short arg[3], short num)//// в зависимости от типа аргумента считывает его байты с арены/регистра
{
	unsigned int ar;
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
		if (a->op_tab[c->f - 1]. lable == 4)
			read_byte4(a->arena, 0, pos, (unsigned char *)&ar);
		else
			read_byte2(a->arena, 0, pos, (unsigned char *)&ar);
	}
	else if (arg[num] == 4)
		read_byte2(a->arena, 0, pos, (unsigned char *)&ar);
	return (ar);
}

void	f6(t_core *a, carriage_t *c)
{
	short			arg[3];
	unsigned int	i;
	unsigned int	h;
	int				p;

	p = 0;
	c->error = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, NULL) + 2;
	i = get_args(a, c, arg, 0);
	p = get_args(a, c, arg, 1);
	h = a->arena[(get_pos_arg(a, c, arg, 2)) % MEM_SIZE] - 1;
	if (c->error != 0 || h >= REG_NUMBER)
		return ;
	i = i & p;
	p = 0;
	while (p < REG_SIZE)
		c->r[h][p++] = 0;
	read_byte4(c->r[h], 0, 0, (unsigned char *)&i);
	c->carry = 0;
	if (i == 0)
		c->carry = 1;
}


void	f7(t_core *a, carriage_t *c)
{
	short			arg[3];
	unsigned int	i;
	unsigned int	h;
	int				p;

	p = 0;
	c->error = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, NULL) + 2;
	i = get_args(a, c, arg, 0);
	p = get_args(a, c, arg, 1);
	h = a->arena[(get_pos_arg(a, c, arg, 2)) % MEM_SIZE] - 1;
	if (c->error != 0 || h >= REG_NUMBER)
		return ;
	i = i | p;
	p = 0;
	while (p < REG_SIZE)
		c->r[h][p++] = 0;
	read_byte4(c->r[h], 0, 0, (unsigned char *)&i);
	c->carry = 0;
	if (i == 0)
		c->carry = 1;
}


void	f8(t_core *a, carriage_t *c)
{
	short			arg[3];
	unsigned int	i;
	unsigned int	h;
	int				p;

	p = 0;
	c->error = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1].lable, NULL) + 2;
	i = get_args(a, c, arg, 0);
	p = get_args(a, c, arg, 1);
	h = a->arena[(get_pos_arg(a, c, arg, 2)) % MEM_SIZE] - 1;
	if (c->error != 0 || h >= REG_NUMBER)
		return ;
	i = i ^ p;
	p = 0;
	while (p < REG_SIZE)
		c->r[h][p++] = 0;
	read_byte4(c->r[h], 0, 0, (unsigned char *)&i);
	c->carry = 0;
	if (i == 0)
		c->carry = 1;
}


//////////////bulakh

void	f16(t_core *a, carriage_t *c)
{
	short	arg[3];
	int		h;
	int		i;

	i = function_codage(a, c, arg);
	c->jump = byte_cal(arg, a->op_tab[c->f - 1]. lable, NULL) + 2;
	h = a->arena[(c->pos + 2) % MEM_SIZE] - 1;
	if (i == 1 || h >= REG_NUMBER)
		return ;
	read_byte4(c->r[h], 0, 0, (unsigned char *)&i);
	i %= 256;
	write(1, &i, 1);
}

void	functions2(carriage_t *c, t_core *a, int f, int i)
{
	printf("%i\n", f);
	if (f == 12)
		f12_15(a, c, 1);
	if (f == 13)
		f13(a, c);
	if (f == 14)
		f14(a, c);
	if (f == 15)
		f12_15(a, c, 0);
	if (f == 16)
		f16(a, c);
}

void	functions(carriage_t *c, t_core *a, int f, int i)
{
	if (f == 1)
		f1(a, c);
	if (f == 2)
		f2(a, c, 0, 0);
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

int		carret(carriage_t *c, t_core *a, unsigned char *s, int i)
{
	if (c->f == 0 && c->cast == 0)
	{
		if (s[c->pos] <= 16 && s[c->pos] > 0)
		{
			c->f = s[c->pos];
			c->cast = a->op_tab[c->f - 1].cycle - 1;
		}
		else
			c->pos = (c->pos + 1) % MEM_SIZE;	//сдвигаемся на 1 
		// printf("function #%i  >  %i\n", c->f, c->cast + 1);
		return (0);
	}
	if (c->f > 0 && c->cast == 0)
	{
		functions(c, a, c->f, -1);
		c->pos = (c->pos + c->jump) % MEM_SIZE;
		c->f = 0;
		c->jump = 0;
		return (1);
	}
	if (c->cast > 0)
	{
		c->cast--;
		// printf("function #%i  >  %i\n", c->f, c->cast + 1);
	}
	return (0);
}

void	check_cycles_carret(t_core *a, carriage_t *c, carriage_t *c2)
{
	while (c)
	{
		if (c->live < a->last_check + a->cycle_to_die)
		{
			if (c == a->carrs)
			{
				a->carrs = c->next;
				free(c);
				c = a->carrs;
			}
			else
			{
				c2->next = c->next;
				free(c);
			}
		}
		if (c && c != a->carrs)
		{
			c2 = c;
			c = c->next;
		}
	}
}

void	check_cycles(t_core *a)
{
	a->n_cycles++;
	if (a->n_cycles - a->last_check == a->cycle_to_die)
	{
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

WINDOW		*print_arena(t_core *a)
{
	WINDOW			*win;
	int				i;
	unsigned char	*s;

	i = 0;
	s = a->arena;
	system("clear");
	start_color();
	win = newwin(200, 150, 0, 0); //need to be changed
	wprintw(win, "..%i..\n", a->n_cycles);
	init_pair(FRAME, COLOR_YELLOW, COLOR_YELLOW);
	while (i < MEM_SIZE)
	{
		make_frame(win);
		if (a->carrs->pos == i)
			wprintw(win, PFC_RED "%.2X" PFC_RESET, s[i++]);
		else if (a->carrs->next->pos == i)
			wprintw(win, PFC_GREEN "%.2X" PFC_RESET, s[i++]);
		else
			wprintw(win, "%.2x", s[i++]);
		if (i % 4 == 0 && i % 64 != 0)
			wprintw(win, " ");
		if (i % 64 == 0)
			wprintw(win, "\n");
		wrefresh(win);
	}
	wprintw(win, "\n\n\n\n");
	wrefresh(win);
	return (win);
}

void	fight(t_core *a, carriage_t *c)
{
	// char	buff[5];
	WINDOW	*win;
	int		ch; //added
	int		k;
	int		o;

	k = 0;
	initscr();
	noecho();
	cbreak();
	keypad(win, TRUE);
	while (a->cycle_to_die > 0 && a->carrs && (a->dump == -1 || a->dump > a->n_cycles))
	{
		win = print_arena(a);
		c = a->carrs;
		while(c)
		{
			o = carret(c, a, a->arena, 0);
			if (o == 1)
				carret(c, a, a->arena, 0);
			c = c->next;
		}
		if (a->n_cycles == k)
			k = 0;
		if (k == 0)
		{
			ch = wgetch(win); // read(0, buff, 5);
			k = ch;
			// if (buff[0] == '+')
			// 	k = a->n_cycles + atoi(buff + 1);
			// buff[0] = 0;
			// buff[1] = 0;
			// buff[2] = 0;
			// buff[3] = 0;
			// buff[4] = 0;
		}
		check_cycles(a);
	}
	wprintw(win, "WINNER - PLAYER №%i\n", a->last_say_live);
	endwin();
}

t_core	*make_core(carriage_t *c, unsigned char *s, player_t *p, int d)
{
	t_core	*a;

	if (!(a = malloc(sizeof(t_core))))
		free_c(p, c, "malloc error");
	a->arena = s;
	a->dump = d;
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

void	do_this(player_t *p, int t, int d)
{
	carriage_t		*c;
	t_core			*arena;
	unsigned char	a[MEM_SIZE];

	null_arena(a);
	c = make_carret(a, p, NULL, t);
	arena = make_core(c, a, p, d);
	arena->num_pl = t;
	arena->last_say_live = t;
	fight(arena, NULL);
}

void	check_p(int i, char **m, player_t *p, int d)
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
		if (h == 4 && o + 1 < i)
			d = flag_d(m, ++o, &t);
		if (h == 5 || (h == 4 && o >= i))
			ft_error(p, 4, "flag -d not valide");
		if (h == 3 || (h == 2 && o + 2 >= i))
			ft_error(p, 4, "flag -n not valide");
		if (h == -1)
			ft_error(p, t, m[o]);
	}
	p = player_numb(p, &t, 1);
	do_this(p, t, d);
}

int		main(int ac, char **av)
{

	// int i;
	// int y;
	// char *num;

	// i = 8193;
	// printf("%.8x\n", i);
	// num = (char *)&i;
	// printf("%.2x%.2x%.2x%.2x\n", num[3], num[2], num[1], num[0]);
	// y = *((int *)num);
	// printf("%.8x\n", y);
	// exit(0);
	if (ac < 2)
		printf("Error: no arguments\n");
	else if (ac > MAX_ARGS_NUMBER + 1)
		printf("Error: tomach arguments\n");
	else
		check_p(ac, av, NULL, -1);


	return 0;
}