/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 01:54:32 by cobecque          #+#    #+#             */
/*   Updated: 2018/02/14 09:30:15 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_putchar_fd_size(char c, char c2, char c3, int fd)
{
	ft_putchar_fd(c, fd);
	ft_putchar_fd(c2, fd);
	ft_putchar_fd(c3, fd);
}

int			ft_sep(char *s, int i, int *count)
{
	if (s[i] == ' ' || s[i] == '\t')
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (s[i] != '\0')
			*count += 1;
		i--;
	}
	return (i);
}

int			line_size(char *line, int i)
{
	int			j;

	j = 0;
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && line[i] != '"')
		{
			if (line[i] != ' ' && line[i] != '\t')
				j++;
			i++;
		}
		if (line[i] == '"')
		{
			i++;
			j++;
			while (line[i] != '\0' && line[i] != '"')
			{
				i++;
				j++;
			}
		}
		if (line != '\0')
			i++;
	}
	return (j);
}
