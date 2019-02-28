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

unsigned int get_args(t_core *a, carriage_t *c, short arg[3], short num)//// в зависимости от типа аргумента считывает его байты с арены/регистара
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
		read_byte4(c->r[ar], 0, 0, ar);
	}
	else if (arg[num] == 2)
	{
		if (a->op_tab[c->f - 1]. lable == 4)
			read_byte4(a->arena, 0, pos, ar);
		else
			read_byte2(a->arena, 0, pos, ar);
	}
	else if (arg[num] == 4)
		read_byte2(a->arena, 0, pos, ar);
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