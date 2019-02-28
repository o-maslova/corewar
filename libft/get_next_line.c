/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:45:13 by omaslova          #+#    #+#             */
/*   Updated: 2018/06/09 16:51:46 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_str	*find_fd(t_str **list, int fd)
{
	t_str *tmp;
	t_str *node;

	tmp = *list;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (fd)
	{
		tmp = *list;
		node = (t_str *)malloc(sizeof(t_str));
		node->content = ft_memalloc(BUFF_SIZE);
		read(fd, node->content, BUFF_SIZE);
		node->fd = fd;
		node->next = NULL;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
		return (node);
	}
	return (0);
}

t_str	*lstnew(t_str **list, int fd)
{
	t_str *node;

	node = NULL;
	if (!(*list))
	{
		(*list) = (t_str *)malloc(sizeof(t_str));
		(*list)->content = ft_memalloc(BUFF_SIZE);
		read(fd, (*list)->content, BUFF_SIZE);
		(*list)->fd = fd;
		(*list)->next = NULL;
		return (*list);
	}
	if ((node = find_fd(list, fd)))
		return (node);
	return (0);
}

char	*combine(char *str, char *buff)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	tmp = (char *)malloc(sizeof(char) * (len + BUFF_SIZE + 1));
	while (i < len)
		tmp[j++] = str[i++];
	i = 0;
	while (buff[i] != '\0')
		tmp[j++] = buff[i++];
	tmp[j] = '\0';
	free(str);
	return (tmp);
}

int		get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	int				var;
	char			*ptr;
	static t_str	*list;
	t_str			*node;

	if (fd < 0 || read(fd, 0, 0) == -1)
		return (-1);
	node = lstnew(&list, fd);
	while (!((ptr = ft_strchr(node->content, '\n'))))
	{
		ft_bzero(buff, BUFF_SIZE + 1);
		if ((read(fd, buff, BUFF_SIZE)) == 0)
			break ;
		node->content = combine(node->content, buff);
	}
	if ((var = ft_strlen(node->content)) == 0 && !ptr)
		return (0);
	if (ptr)
		var -= ft_strlen(ptr++);
	else
		ptr = "\0";
	*line = ft_strsub(node->content, 0, var);
	node->content = ft_strcpy(node->content, ptr);
	return (1);
}
