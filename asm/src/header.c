/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:08:14 by cobecque          #+#    #+#             */
/*   Updated: 2017/11/20 19:34:41 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

header_t		init_header(char *name, char *com)
{
	header_t	header;
	int			i;
	int			j;

	i = 1;
	j = 0;
	header.magic = COREWAR_EXEC_MAGIC;
	header.prog_size = 0;
	while (name && i < PROG_NAME_LENGTH + 1 && i < (int)ft_strlen(name) - 1)
	{
		header.prog_name[j] = name[i];
		i++;
		j++;
	}
	i = 1;
	j = 0;
	while (com && i < COMMENT_LENGTH + 1 && i < (int)ft_strlen(com) - 1)
	{
		header.comment[j] = com[i];
		i++;
		j++;
	}
	return (header);
}

void			put_magic(header_t h, int fd)
{
	int		magic[4];
	int		i;

	i = 0;
	while (i < 4)
	{
		magic[i] = (unsigned char)h.magic;
		h.magic >>= 8;
		i++;
	}
	while (--i >= 0)
		ft_putchar_fd(magic[i], fd);
}

void			put_all(header_t h, int fd)
{
	int			size;
	unsigned	int p;

	put_magic(h, fd);
	size = ft_strlen(h.prog_name);
	p = h.prog_size;
	ft_putstr_fd(h.prog_name, fd);
	while (++size <= PROG_NAME_LENGTH)
		write(fd, "\0", 1);
	write(fd, "\0\0\0\0\0\0\0\0", 8);
	if (lseek(fd, PROG_NAME_LENGTH + 8, SEEK_SET) == -1)
		return ;
	ft_putchar_fd_size(p >> 24, p >> 16, p >> 8, fd);
	ft_putchar_fd((int)p, fd);
	size = ft_strlen(h.comment);
	ft_putstr_fd(h.comment, fd);
	while (++size <= COMMENT_LENGTH + 4)
		write(fd, "\0", 1);
}
