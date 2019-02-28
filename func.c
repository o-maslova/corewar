#include "corelib.h"

int function_codage(t_core *arena, carriage_t *car)
{
	short arg[3];
	int i;
	int codage;
	int one;

	i = 0;
	one = 128;
	codage = ((int)arena->arena[car->pos + 1]);
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

int	ft_type_codeage(t_core *arena, carriage_t *car, short arg[3])
{
	int i;
	int error;

	i = 0;
	error = 1;
	while(i < arena->op_tab[car->f - 1].nb_args)
	{
		if (arg[i] == 0 || (arg[i] & arena->op_tab[car->f - 1].args[i]) != arg[i])
			error = 0;
		if (arg[i] == 2)
			arg[i] = arena->op_tab[car->f - 1].lable;
		else if (arg[i] == 4)
			arg[i] = 2;
	}
	return (error);
}