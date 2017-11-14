/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:40:35 by cobecque          #+#    #+#             */
/*   Updated: 2017/11/08 14:15:14 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char		*get_name(char *str)
{
	char	*name;
	int		i;

	name = ft_strdup(str);
	i = 0;
	while (name[i] != '\0')
	{
		if (name[i] == '.')
			break;
		i++;
	}
	i = ft_strlen(name) - i;
	name = ft_strsub(name, 0, ft_strlen(name) - i);
	name = ft_strcat(name, ".cor");
	return (name);
}

t_file		*fill_binair(t_file *file, int fd, header_t h)
{
	t_file	*tmp;
	int		i;
	char	*new;
	int		size;
	int		nb;
	int		all;
	char	c;
	int		magic[4];

	i = 0;
	while (i < 4)
	{
		magic[i] = (unsigned char)h.magic;
		h.magic >>= 8;
		i++;
	}
	while (--i >= 0)
		ft_putchar_fd(magic[i], fd);
	nb = 0;
	c = '\0';
	all = all_octet(file);
	tmp = file;
	h.prog_size = all;//+ sizeof(unsigned int) + PROG_NAME_LENGTH + COMMENT_LENGTH;
/*	write(fd, &header.magic, sizeof(unsigned int));
	write(fd, header.prog_name, PROG_NAME_LENGTH+ sizeof(unsigned char) + sizeof(unsigned int));
	write(fd, &header.prog_size, sizeof(unsigned char) - sizeof(unsigned int));
	write(fd, header.comment, COMMENT_LENGTH - sizeof(unsigned char) - sizeof(unsigned int));*/
	size = ft_strlen(h.prog_name);
	ft_putstr_fd(h.prog_name, fd);
	while (++size <= PROG_NAME_LENGTH)
		write(fd, "\0", 1);
	write(fd, "\0\0\0\0\0\0\0\0", 8);
	if (lseek(fd, PROG_NAME_LENGTH + 8, SEEK_SET) == -1)
		return (NULL);
	ft_putchar_fd_size(h.prog_size >> 24, h.prog_size >> 16, h.prog_size >> 8, fd);
	ft_putchar_fd((int)h.prog_size, fd);
	size = ft_strlen(h.comment);
	ft_putstr_fd(h.comment, fd);
	while (++size <= COMMENT_LENGTH + 4)
		write(fd, "\0", 1);
	while (tmp != NULL)
	{
		if (tmp->code != NULL)
		{
			i = 0;
			new = ft_strdup(tmp->code);
			tmp->binair = dec_to_bi(new);
			size = octet_on_line(new);
			while (i < size && nb < all)
			{
				write(fd, &tmp->binair[i], sizeof(unsigned char));
				i++;
				nb += 1;
			}
		}
		tmp = tmp->next;
	}
	return (file);
}

int		all_octet(t_file *file)
{
	t_file	*tmp;
	int		i;
	char	*new;

	i = 0;
	tmp = file;
	while (tmp != NULL)
	{
		if (tmp->code != NULL)
		{
			new = ft_strdup(tmp->code);
			i += octet_on_line(new);
		}
		tmp = tmp->next;
	}
	return (i);
}
