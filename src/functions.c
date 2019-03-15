#include "corelib.h"

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
		if (a->visual_flag == 1)
			a->visual->paint_arena[c->pos].i_live = 50;
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
	if (a->n_cycles == 7218)
		dprintf(g_fd, ">>c_%d | pos = %d | c_f = %d|wr to %d |reg - |%x|%x|%x|%x|\n", c->number, c->pos, c->f, (MEM_SIZE + (c->pos + h) % MEM_SIZE) % MEM_SIZE, c->r[i][0], c->r[i][1], c->r[i][2], c->r[i][3]);
	write_reg(a->arena, c->r[i], (MEM_SIZE + (c->pos + h) % MEM_SIZE) % MEM_SIZE, 0);
	while (a->visual_flag == 1 && ++tmp < 4)
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
	if (a->n_cycles == 7218)
		dprintf(g_fd, ">>c_%d | pos = %d | c_f = %d| write to %d |\n", c->number, c->pos, c->f, (MEM_SIZE + (c->pos + h) % MEM_SIZE) % MEM_SIZE);
	write_reg(a->arena, c->r[i], (MEM_SIZE + (c->pos + h) % MEM_SIZE) % MEM_SIZE, 0);
	while (a->visual_flag == 1 && ++tmp < 4)
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
	{
		new->f = 0;
		new->cast = 0;
	}
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
	}
	else
	{
		f12_f15_duplicate_carret(c, a, i);
	}
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
	//write(1, &h, 1);
}