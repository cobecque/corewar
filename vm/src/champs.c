/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 00:38:02 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/21 18:13:51 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_champ		fill_name(int fd, t_champ play)
{
	char		str[8];

	ft_bzero(play.name, PROG_NAME_LENGTH);
	if (read(fd, play.name, PROG_NAME_LENGTH) <= 0)
		exit(-1);
	if (read(fd, str, 8) <= 0)
		exit(-1);
	return (play);
}

t_champ		fill_comment(int fd, t_champ play)
{
	char	str[4];

	if (read(fd, play.comment, COMMENT_LENGTH) <= 0)
		exit(-1);
	read(fd, str, 4);
	return (play);
}

t_champ		fill_code(int fd, t_champ play)
{
	if ((play.len = read(fd, play.code, CHAMP_MAX_SIZE)) < 0)
		return (play);
	return (play);
}

t_champ		fill_all(int fd, t_champ play)
{
	play = fill_name(fd, play);
	play = fill_comment(fd, play);
	play = fill_code(fd, play);
	return (play);
}

t_vm		fill_champ(int *fd)
{
	int			i;
	t_vm		data;

	data.nb_pros = fd[0] - 1;
	data.error = 0;
	i = 1;
	while (i < fd[0])
	{
		data.play[i - 1].addr = NULL;
		if (check_magic(fd[i]) == -1)
		{
			data.error = 2;
			return (data);
		}
		data.play[i - 1] = fill_all(fd[i], data.play[i - 1]);
		data.play[i - 1].nb = i;
		if (data.play[i - 1].len > CHAMP_MAX_SIZE)
			data.error = 1;
		close(fd[i]);
		i++;
	}
	return (data);
}
