/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 03:43:00 by cobecque          #+#    #+#             */
/*   Updated: 2018/03/08 07:24:52 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		write_spec(t_inst *tmp, int fd)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (tmp->typ[i] != 0)
		{
			if (tmp->typ[i] == 4)
				ft_putchar_fd_size(tmp->val[i] >> 24, tmp->val[i] >> 16,
						tmp->val[i] >> 8, fd);
			else if (tmp->typ[i] == 2)
				ft_putchar_fd(tmp->val[i] >> 8, fd);
			ft_putchar_fd(tmp->val[i], fd);
		}
		i++;
	}
}

void		write_binary(t_file file, int fd)
{
	t_inst	*tmp;

	tmp = file.ins;
	while (tmp != NULL)
	{
		if (tmp->label == NULL)
		{
			ft_putchar_fd(tmp->line + 1, fd);
			if (tmp->ocp != 0)
				ft_putchar_fd(tmp->ocp, fd);
			write_spec(tmp, fd);
		}
		tmp = tmp->next;
	}
}

void		fill_magic(int fd, t_header h)
{
	int			magic[4];
	int			i;

	h.magic = 0xea83f3;
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

void		fill_champ(int fd, t_file file, t_header h)
{
	int		size;

	size = ft_strlen(file.name);
	ft_putstr_fd(file.name, fd);
	while (++size <= PROG_NAME_LENGTH)
		write(fd, "\0", 1);
	write(fd, "\0\0\0\0\0\0\0\0", 8);
	if (lseek(fd, PROG_NAME_LENGTH + 8, SEEK_SET) == -1)
		exit(-1);
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
