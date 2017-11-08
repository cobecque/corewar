/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_binair.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:22:15 by cobecque          #+#    #+#             */
/*   Updated: 2017/11/08 13:50:32 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned char	*dec_to_bi(char *code)
{
	unsigned char	*res;
	char			*tmp;
	int				i;
	int				j;

	j = 0;
	i = octet_on_line(code);
	if (!(res = (unsigned char *)malloc(sizeof(unsigned char) * i + 1)))
		return (NULL);
	i = 0;
	while (code[i] != '\0')
	{
		if (code[i] == ' ')
			i++;
		tmp = ft_strsub(code, i, 4);
		res[j] = hex_dec(tmp);
		i += 4;
		j++;
	}
	res[j] = '\0';
	return (res);
}

unsigned char	hex_dec(char *code)
{
	unsigned char	res;
	char			*tmp;
	int				i;
	int				nb;
	int				j;
	int				hex;

	nb = 0;
	j = 0;
	i = 1;
	tmp = ft_strsub(code, 2, 2);
	while (i >= 0)
	{
		if (tmp[i] - '0' > 9)
			hex = tmp[i] - 'a' + 10;
		else
			hex = tmp[i] - '0';
		nb += (hex * ft_pow(16, j));
		i--;
		j++;
	}
	res = (unsigned char)nb;
	return (res);
}

void			ft_putchar_fd_size(char c, char c2, char c3, int fd)
{
	ft_putchar_fd(c, fd);
	ft_putchar_fd(c2, fd);
	ft_putchar_fd(c3, fd);
}
