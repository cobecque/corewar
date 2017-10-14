/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 18:56:18 by cobecque          #+#    #+#             */
/*   Updated: 2017/10/14 03:23:02 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_file	*init_file(t_file *file, char *line)
{
	t_file	*tmp;
	t_file	*new;

	tmp = file;
	if (!(new = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	new->line = ft_strdup(line);
	new->next = NULL;
	if (!tmp)
		return (new);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (file);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	char	*name;
	char	*comment;
	t_file	*file;
	int		size;

	file = NULL;
	size = 0;
	if (argc > 0)
	{
		fd = open(argv[1], O_RDONLY);
		while (get_next_line(fd, &line) > 0)
		{
			if (ft_strncmp(line, ".name", 5) == 0)
				name = ft_strsub(line, 6, ft_strlen(line) - 6);
			else if (ft_strncmp(line, ".comment", 8) == 0)
				comment = ft_strsub(line, 9, ft_strlen(line) - 9);
			else
			{
				file = init_file(file, line);
				size += ft_strlen(line);
			}
			printf(C_BLU"%s\n"FC_ALL, line);
			free(line);
		}
		close(fd);
	}
//	ft_try_it(file, name, comment, size);
	return (0);
}
/*
char	*ft_calcul(char *line)
{
	char	*new;
	int		i;
	t_op	op_tab;

	i = 0;
	new = ft_look(line);

}

void	ft_try_it(t_file *file, char *name, char *comment, int size)
{
	header_t	header;
	t_file		*tmp;
	char		*octet;
	int			i;

	i = 0;
	header.magic = COREWAR_EXEC_MAGIC;
	header.prog_name = ft_strcpy(name);
	header.prog_size = size;
	header.comment = ft_strcpy(comment);
	tmp = file;
	while (tmp != NULL)
	{
		if (tmp->line != NULL)
			i++;
		tmp = tmp->next;
	}
	tmp = file;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->line != NULL)
		{
			octet = ft_calcul(tmp->line);
			printf(CN_RED, octet);
		}
		tmp = tmp->next;
	}
}*/
