/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 00:55:32 by cobecque          #+#    #+#             */
/*   Updated: 2018/02/12 04:03:31 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			main(int argc, char **argv)
{
	char	*line;
	t_file	file;
	int		fd;

	line = NULL;
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
	}
	return (0);
}
