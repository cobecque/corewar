/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 03:43:00 by cobecque          #+#    #+#             */
/*   Updated: 2018/02/13 08:28:21 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_putchar_fd_size(char c, char c2, char c3, int fd)
{
	ft_putchar_fd(c, fd);
	ft_putchar_fd(c2, fd);
	ft_putchar_fd(c3, fd);
}

void		write_binary(t_file file, int fd)
{
	t_inst	*tmp;
	int		i;

	tmp = file.ins;
	while (tmp != NULL)
	{
		i = 0;
		if (tmp->label == NULL)
		{
			ft_putchar_fd(tmp->line + 1, fd);
			if (tmp->ocp != 0)
				ft_putchar_fd(tmp->ocp, fd);
			while (++i < 4)
			{
				if (tmp->typ[i - 1] != 0)
				{
					if (tmp->typ[i - 1] == 4)
						ft_putchar_fd_size(tmp->val[i - 1] >> 24,
								tmp->val[i - 1] >> 16, tmp->val[i - 1] >> 8, fd);
					else if (tmp->typ[i - 1] == 2)
						ft_putchar_fd(tmp->val[i - 1] >> 8, fd);
					ft_putchar_fd(tmp->val[i - 1], fd);
				}
			}
		}
		tmp = tmp->next;
	}
}

void		fill_magic(int fd, header_t h)
{
	int			magic[4];
	int			i;

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

void		fill_champ(int fd, t_file file, header_t h)
{
	int		size;

	size = ft_strlen(file.name);
	ft_putstr_fd(file.name, fd);
	while (++size <= PROG_NAME_LENGTH)
		write(fd, "\0", 1);
	write(fd, "\0\0\0\0\0\0\0\0", 8);
	if (lseek(fd, PROG_NAME_LENGTH + 8, SEEK_SET) == -1)
		exit (-1);
	ft_putchar_fd_size(h.size >> 24, h.size >> 16, h.size >> 8, fd);
	ft_putchar_fd((int)h.size, fd);
	size = ft_strlen(file.comment);
	ft_putstr_fd(file.comment, fd);
	while (++size <= COMMENT_LENGTH + 4)
		write(fd, "\0", 1);
}

int			size_champ(t_file file)
{
	t_inst	*tmp;
	int		i;
	int		nb;

	nb = 0;
	tmp = file.ins;
	while (tmp != NULL)
	{
		if (tmp->label == NULL)
		{
			i = 0;
			while (i < 3)
			{
				nb += tmp->typ[i];
				i++;
			}
			nb += 1;
			if (tmp->ocp != 0)
				nb += 1;
		}
		tmp = tmp->next;
	}
	return (nb);
}
