/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 00:38:02 by rostroh           #+#    #+#             */
/*   Updated: 2017/10/29 06:06:44 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_champ			init_play(int nb)
{
	t_champ		new;

	new.nb = nb;
	return (new);
}

t_vm			init_vm(int nb_pros)
{
	int			i;
	t_vm		data;

	i = 0;
	data.nb_pros = nb_pros;
	data.error = 0;
	while (i < MAX_PLAYERS)
	{
		data.play[i] = init_play(i + 1);
		i++;
	}
	return (data);
}

int			fill_name(int fd, t_champ *play)
{
	char		str[6];

	if (read(fd, play->name, PROG_NAME_LENGTH) < 0)
		return (0);
	if (read(fd, str, 6) <= 0)
		return (0);
	return (1);
}

int			fill_comment(int fd, t_champ *play)
{
	char	str[6];

	if (read(fd, play->comment, COMMENT_LENGTH) < 0)
		return (0);
	if (read(fd, str, 6) <= 0)
		return (0);
	return (1);
}

int			fill_code(int fd, t_champ *play)
{
	if ((play->len = read(fd, play->code, CHAMP_MAX_SIZE)) < 0)
		return (0);
	return (1);
}

int			check_magic(int fd)
{
	char		a;
	char		b;
	char		c;
	char		d;
	char		str[4];

	a = 0x0;
	b = 0xea;
	c = 0x83;
	d = 0xf3;
	if (COREWAR_EXEC_MAGIC != 15369203)
	{
		ft_printf("Not a 42 exec, sorry\n");
		return (-1);
	}
	if ((read(fd, str, 4) < 0))
		return (-1);
	if (a != str[0] || b != str[1] || c != str[2] || d != str[3])
	{
		ft_printf("Not a 42 exec, sorry\n");
		return (-1);
	}
	return (1);
}

t_champ		fill_all(int fd, t_champ *play)
{
	if (check_magic(fd) == -1)
		exit (-1);
	if (fill_name(fd, play) == 0)
		exit (-1);
	if (fill_comment(fd, play) == 0)
		exit (-1);
	if (fill_code(fd, play) == 0)
		exit (-1);
	return (*play);
}

t_vm		fill_champ(int *fd)
{
	int			i;
	t_vm		data;

	data = init_vm(fd[0] - 1);
	i = 1;
	while (i < fd[0])
	{
		data.play[i - 1] = fill_all(fd[i], &data.play[i]);
		if (data.play[i - 1].len > CHAMP_MAX_SIZE)
			data.error = 1;
		//ft_printf("at fd %d, len = %d\n", i - 1, data.play[i - 1].len);
		close (fd[i]);
		i++;
	}
	return (data);
}
