/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 06:44:27 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/08 13:37:00 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

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
