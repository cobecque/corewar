/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:44:43 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/14 09:18:30 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

char			*get_hexa(int val)
{
	char	*str;

	if (val == 0)
		return ("00");
	str = (char *)malloc(sizeof(char) * 3);
	str[2] = '\0';
	if (val < 0)
	{
		val = 256 + val;
	}
	if (val % 16 >= 10)
		str[1] = val % 16 + 'a' - 10;
	if (val % 16 < 10)
		str[1] = val % 16 + '0';
	if (val / 16 >= 10)
		str[0] = val / 16 + 'a' - 10;
	if (val / 16 < 10)
		str[0] = val / 16 + '0';
	return (str);
}

void			dump(char *ptr)
{
	int		i;
	int		p;

	i = 0;
	p = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0 && i != 0)
			ft_putchar('\n');
		if (i % 64 == 0)
		{
			ft_putstr("0x0");
			if (p < 16)
				ft_putchar('0');
			ft_printf("%x0 : ", p);
			p += 4;
		}
		ft_printf("%s ", get_hexa(ptr[i]));
		i++;
	}
	ft_putchar('\n');
}

t_ver			get_verbose(int nu)
{
	t_ver		ver;

	ver.li = 0;
	ver.cy = 0;
	ver.de = 0;
	ver.pc = 0;
	if (nu == 0)
		return (ver);
	if ((nu & 0x01) != 0)
		ver.li = 1;
	if ((nu & 0x02) != 0)
		ver.cy = 1;
	if ((nu & 0x04) != 0)
		ver.op = 1;
	if ((nu & 0x08) != 0)
		ver.de = 1;
	if ((nu & 0x010) != 0)
		ver.pc = 1;
	return (ver);
}
