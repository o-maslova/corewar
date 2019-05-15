/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agalayko <agalayko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 23:05:26 by agalayko          #+#    #+#             */
/*   Updated: 2019/03/14 23:05:27 by agalayko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

void		ft_error_asm(char *txt)
{
	ft_putstr("\033[91m");
	ft_putendl(txt);
	ft_putstr("\033[0m");
	exit(0);
}

static void	output_name(char *name)
{
	char	*str;
	int		i;

	i = 0;
	ft_putstr(MES_OUTPUT);
	str = (char*)malloc(sizeof(char) * (ft_strlen(name) - 2));
	while (name[i] && name[i] != '.')
	{
		str[i] = name[i];
		i++;
	}
	str[i] = '\0';
	ft_putstr("/");
	ft_putstr(str);
	ft_putendl(".cor\033[0m");
}

int			check_file_type(char *file)
{
	int	len;

	len = ft_strlen(file) - 2;
	if (len > 0 && file[len] == '.' && file[len + 1] == 's')
		return (0);
	else
		return (1);
}

void		open_and_read(char *file_name, int type)
{
	int		fd;
	t_lexer	*lex;
	char	*tmp;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		tmp = ft_strjoin(ERR_FILE_NAME, file_name);
		ft_error_asm(tmp);
	}
	else if (open(file_name, O_DIRECTORY) > 0
			|| check_file_type(file_name) == 1)
		ft_error_asm(ERR_USAGE);
	lex = lexer(fd, file_name);
	if (lex == NULL)
		return ;
	syntax(lex);
	codegen(lex);
	if (type == 3)
		write_tree_struct(lex);
	free_lexer(lex);
	free(lex);
	close(fd);
}

int			main(int argc, char **argv)
{
	if (argc != 2 && argc != 3)
	{
		ft_error_asm(ERR_USAGE);
		return (0);
	}
	if (argc == 3 && ft_strcmp(argv[1], "-a") != 0)
	{
		ft_error_asm(ERR_USAGE);
		return (0);
	}
	open_and_read(argv[argc - 1], argc);
	output_name(argv[argc - 1]);
	return (0);
}
