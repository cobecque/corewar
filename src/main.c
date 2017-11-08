/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 15:23:10 by cobecque          #+#    #+#             */
/*   Updated: 2017/11/07 19:07:42 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int argc, char **argv)
{
	t_file		*file;
	int			fd;
	char		*line;
	char		*name;
	char		*comment;
	int			i;
	int			j;
	header_t	header;

	header.prog_name[0] = '\0';
	header.comment[0] = '\0';
	header.prog_size = 0;
	header.magic = 0xea83f3;
	file = NULL;
	name = NULL;
	comment = NULL;
	if (argc > 0)
	{
		fd = open(argv[1], O_RDONLY);
		while (get_next_line(fd, &line) > 0)
		{
			if (ft_strncmp(line, ".name", 5) == 0)
				name = ft_strsub(line, 6, ft_strlen(line) - 6);
			else if (ft_strncmp(line, ".comment", 8) == 0)
				comment = ft_strsub(line, 9, ft_strlen(line) - 9);
			else if (ft_strncmp(line, "#", 1) == 0)
				;
			else
				file = init_file(file, line);
			free(line);
		}
		close(fd);
	}
	j = 0;
	i = 1;
	while (i < PROG_NAME_LENGTH + 1 && i < (int)ft_strlen(name) - 1)
	{
		header.prog_name[j] = name[i];
		i++;
		j++;
	}
	i = 1;
	j = 0;
	while (i < COMMENT_LENGTH + 1 && i < (int)ft_strlen(comment) - 1)
	{
		header.comment[j] = comment[i];
		i++;
		j++;
	}
	name = get_name(argv[1]);
	fd = open(name, O_CREAT | O_WRONLY);
	chmod(name, S_IRUSR | S_IWUSR);
	ft_asm(file, fd, header);
	close(fd);
	return (0);
}

void	ft_asm(t_file *file, int fd, header_t header)
{
	t_file		*tmp;

	tmp = file;
	tmp = ft_encodage(tmp, fd, header);
}

t_file	*ft_encodage(t_file *file, int fd, header_t header)
{
	t_file	*tmp;

	tmp = file;
	tmp = ft_label(tmp);
	tmp = ft_instruction(tmp);
	tmp = ft_ocp(tmp);
	tmp = ft_parametre(tmp);
	tmp = file_param(tmp);
	tmp = ft_spec_param(tmp);
	tmp = fill_binair(tmp, fd, header);
	return (tmp);
}

t_file	*ft_label(t_file *file)
{
	t_file	*tmp;
	int		i;

	tmp = file;
	while (tmp != NULL)
	{
		i = 0;
		if (tmp->line != NULL)
		{
			while (tmp->line[i] != '\0' && tmp->line[i] != ':')
				i++;
			if (tmp->line[i] == ':')
			{
				tmp->label = ft_strsub(tmp->line, 0, i);
				if (ft_is_label(tmp->label) == 1)
					tmp->label = NULL;
			}
		}
		tmp = tmp->next;
	}
	return (file);
}

int		ft_is_label(char *str)
{
	char	*label;
	int		i;
	int		j;
	int		bol;

	label = ft_strdup(LABEL_CHARS);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		j = 0;
		bol = 0;
		while (label[j] != '\0' && bol == 0)
		{
			if (str[i] == label[j])
				bol++;
			else
				j++;
		}
		if (bol == 0)
			return (1);
		i++;
	}
	return (0);
}
