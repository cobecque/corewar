/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 00:55:32 by cobecque          #+#    #+#             */
/*   Updated: 2018/02/14 10:18:46 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				main(int argc, char **argv)
{
	char		*line;
	t_file		file;
	int			fd;

	line = NULL;
	file = init_file();
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			return (error_open(fd));
		while (get_next_line(fd, &line) > 0)
		{
			file = fill_file(file, line);
			free(line);
		}
		if (check_error(file) == -1)
			return (0);
		file.ins = find_label(file.ins);
		create_file(argv[1], file);
		if (close(fd) == -1)
			ft_printf("Error : Close file\n");
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

	h.magic = 0xea83f3;
	if (!(name = (char *)malloc(sizeof(char) * ft_strlen(argv) + 3)))
		exit(-1);
	name = ft_strcpy(name, argv);
	name[ft_strlen(argv) - 2] = '\0';
	name = ft_strcat(name, ".cor");
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC);
	if (fd == -1)
		ft_printf("open error\n");
	chmod(name, S_IRUSR | S_IWUSR);
	h.size = size_champ(file);
	fill_magic(fd, h);
	fill_champ(fd, file, h);
	write_binary(file, fd);
	free(name);
	if (close(fd) == -1)
		ft_printf("close error\n");
}
