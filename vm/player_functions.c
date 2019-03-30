/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 22:19:00 by omaslova          #+#    #+#             */
/*   Updated: 2019/03/30 22:19:05 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corelib.h"

static int	com_player(int *fd, t_player *pl, unsigned char *buff, int size)
{
	int	i;

	i = read(*fd, buff, COMMENT_LENGTH + 4);
	if (i != COMMENT_LENGTH + 4 || buff[i - 4] != 0 ||
	buff[i - 1] != 0 || buff[i - 2] != 0 || buff[i - 3] != 0)
		return (check_ret(fd, 1));
	ft_strncpy(pl->comment, (char *)buff, COMMENT_LENGTH + 1);
	i = read(*fd, buff, CHAMP_MAX_SIZE + 1);
	if (i != size)
		return (check_ret(fd, 3));
	ft_strncpy2(pl->code, buff, size + 1);
	close(*fd);
	*fd = pl->pos;
	return (1);
}

void		rotate_num(char *str, char *buff)
{
	str[0] = buff[3];
	str[1] = buff[2];
	str[2] = buff[1];
	str[3] = buff[0];
}

t_player	*creat_player(t_player *player, int t, char *s)
{
	t_player	*new_player;

	if (!(new_player = ft_memalloc(sizeof(t_player))))
		ft_error(player, 4, "malloc error");
	if (s)
		ft_strncpy(new_player->prog_name, s, PROG_NAME_LENGTH + 1);
	new_player->number = t;
	if (!player)
		return (new_player);
	while (player->next)
		player = player->next;
	new_player->pos = player->pos + 1;
	player->next = new_player;
	return (new_player);
}

int			parse_player(char *name, int *fd, int o, t_player *pl)
{
	int				i;
	unsigned int	*p;
	int				size;
	unsigned char	buff[COMMENT_LENGTH + 1];

	if ((*fd = open(name, O_RDONLY)) < 0)
		return (-1);
	i = read(*fd, buff, 4);
	p = (unsigned int *)buff;
	if (i < 4 || revers(p[0]) != COREWAR_EXEC_MAGIC)
		return (check_ret(fd, 1));
	i = read(*fd, buff, PROG_NAME_LENGTH + 4);
	if (i != PROG_NAME_LENGTH + 4 || buff[i - 4] != 0 ||
	buff[i - 1] != 0 || buff[i - 2] != 0 || buff[i - 3] != 0)
		return (check_ret(fd, 1));
	pl = creat_player(pl, o, (char *)buff);
	i = read(*fd, buff, 4);
	rotate_num((char *)&size, (char *)&(buff[0]));
	if (i < 4 || size > CHAMP_MAX_SIZE)
		return (check_ret(fd, 2));
	pl->length = size;
	return (com_player(fd, pl, buff, size));
}

T_P			*move_p(T_P *def, T_P *cur, short pos[MAX_PLAYERS], int num)
{
	T_P	*new_order;
	T_P	*new_cur;
	int	i;

	i = -1;
	new_order = ft_memcpy(ft_memalloc(sizeof(T_P)), def, sizeof(T_P));
	new_cur = new_order;
	while (++i < num)
		new_cur = find_place(def->next, new_cur, pos, i);
	new_cur->next = NULL;
	while (def)
	{
		cur = def->next;
		free(def);
		def = cur;
	}
	new_cur = new_order->next;
	free(new_order);
	return (new_cur);
}
