/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 22:18:15 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/30 22:18:19 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corelib.h"

int			flag_n(char **argv, int n_arg, int *t, t_player *p)
{
	int	i;

	i = -1;
	while (argv[n_arg] && argv[n_arg][++i])
		if (argv[n_arg][i] < '0' || argv[n_arg][i] > '9')
			return (3);
	i = atoi(argv[n_arg]);
	return (typeofarg(argv[++n_arg], t, i, p));
}

int			flag_d(char **argv, int n_arg)
{
	int	i;

	i = -1;
	if (argv[n_arg] && argv[n_arg][0] == '-')
		i++;
	while (argv[n_arg] && argv[n_arg][++i])
		if (argv[n_arg][i] < '0' || argv[n_arg][i] > '9')
			return (-1);
	i = atoi(argv[n_arg]);
	return (i);
}

int			typeofarg(char *argv, int *t, int o, t_player *pl)
{
	int	i;
	int	p;

	i = -1;
	if (ft_strcmp(argv, "-n") == 0 && o == -1)
		return (2);
	if (ft_strcmp(argv, "-dump") == 0 && o == -1)
		return (4);
	if (ft_strcmp(argv, "-v") == 0 && o == -1)
		return (8);
	p = -1;
	while (argv[++i] && p == -1)
	{
		if (argv[i] == '.' &&
		ft_strcmp(argv + i, ".cor") == 0 && argv[i + 4] == '\0')
			p = 1;
	}
	if (p == -1)
		*t = 0;
	else
		p = parse_player(argv, t, o, pl);
	return (p);
}
