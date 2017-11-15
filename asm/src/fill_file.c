/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:40:35 by cobecque          #+#    #+#             */
/*   Updated: 2017/11/15 15:03:54 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*get_name(char *str)
{
	char	*name;
	int		i;

	name = ft_strdup(str);
	i = 0;
	while (name[i] != '\0')
	{
		if (name[i] == '.')
			break ;
		i++;
	}
	i = ft_strlen(name) - i;
	name = ft_strsub(name, 0, ft_strlen(name) - i);
	name = ft_strcat(name, ".cor");
	return (name);
}

int			write_in(int size, int all, int fd, unsigned char *bin)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (i < size && nb < all)
	{
		write(fd, &bin[i], sizeof(unsigned char));
		i++;
		nb++;
	}
	return (all - nb);
}

t_file		*fill_binair(t_file *file, int fd, header_t h)
{
	t_file	*tmp;
	char	*new;
	int		size;
	int		all;

	tmp = file;
	all = all_octet(file);
	h.prog_size = all;
	put_all(h, fd);
	while (tmp != NULL)
	{
		if (tmp->code != NULL)
		{
			new = ft_strdup(tmp->code);
			tmp->binair = dec_to_bi(new);
			size = octet_on_line(new);
			all = write_in(size, all, fd, tmp->binair);
		}
		tmp = tmp->next;
	}
	return (file);
}

int			all_octet(t_file *file)
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
