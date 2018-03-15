/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 00:55:32 by cobecque          #+#    #+#             */
/*   Updated: 2018/03/15 20:48:59 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			ft_putchar_fd_size(char c, char c2, char c3, int fd)
{
	ft_putchar_fd(c, fd);
	ft_putchar_fd(c2, fd);
	ft_putchar_fd(c3, fd);
}

void			clear_file(t_file file)
{
	t_inst	*tmp;
	t_inst	*keep;

	tmp = file.ins;
	while (tmp != NULL)
	{
		keep = tmp;
		if (tmp->label != NULL)
			free(tmp->label);
		if (tmp->label1 != NULL)
			free(tmp->label1);
		if (tmp->label2 != NULL)
			free(tmp->label2);
		if (tmp->label3 != NULL)
			free(tmp->label3);
		tmp = tmp->next;
		free(keep);
	}
	if (file.name != NULL)
		free(file.name);
	if (file.comment != NULL)
		free(file.comment);
}

int				main(int argc, char **argv)
{
	char		*line;
	t_file		file;
	int			fd;

	line = NULL;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			return (error_open(fd));
		file = init_file();
		while (get_next_line(fd, &line) > 0)
		{
			file = fill_file(file, line);
			free(line);
		}
		free(line);
		if (check_error(file) == -1)
			return (0);
		file.ins = find_label(file.ins, file);
		create_file(argv[1], file);
		ft_close_error(fd);
		clear_file(file);
	}
	return (0);
}

int				error_open(int fd)
{
	if (fd == -1)
		ft_putstr("Error : Open file\n");
	return (0);
}

void			create_file(char *argv, t_file file)
{
	t_header	h;
	char		*name;
	int			fd;

	h.size = size_champ(file);
	if (!(name = (char *)malloc(sizeof(char) * ft_strlen(argv) + 3)))
		exit(-1);
	name = ft_strcpy(name, argv);
	name[ft_strlen(argv) - 2] = '\0';
	name = ft_strcat(name, ".cor");
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC);
	if (fd == -1)
		ft_printf("open error\n");
	chmod(name, S_IRUSR | S_IWUSR);
	fill_magic(fd, h);
	fill_champ(fd, file, h);
	write_binary(file, fd);
	ft_printf("Writting ouptut program to %s\n", name);
	free(name);
	if (close(fd) == -1)
		ft_printf("close error\n");
}
