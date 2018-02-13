/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 00:55:32 by cobecque          #+#    #+#             */
/*   Updated: 2018/02/13 08:26:21 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			main(int argc, char **argv)
{
	char		*line;
	t_file		file;
	header_t	h;
	char		*name;
	int			fd;

	line = NULL;
	h.magic = 0xea83f3;
	file = init_file();
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while (get_next_line(fd, &line) > 0)
		{
			file = fill_file(file, line);
			free(line);
		}
		if (check_error(file) == -1)
			return (0);
		file.ins = find_label(file.ins);
		name = ft_strsub(argv[1], 0, ft_strlen(argv[1]) - 2);
		name = ft_strcat(name, ".cor");
		fd = open(name, O_CREAT | O_WRONLY | O_TRUNC);
		chmod(name, S_IRUSR | S_IWUSR);
		h.size = size_champ(file);
		fill_magic(fd, h);
		fill_champ(fd, file, h);
		write_binary(file, fd);
		close(fd);
	}
	return (0);
}
