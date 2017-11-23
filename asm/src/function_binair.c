/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_binair.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:22:15 by cobecque          #+#    #+#             */
/*   Updated: 2017/11/20 19:38:17 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

unsigned char	*dec_to_bi(char *code)
{
	unsigned char	*res;
	char			*tmp;
	int				i;
	int				j;
	int				len;

	j = 0;
	len = octet_on_line(code);
	if (!(res = (unsigned char *)malloc(sizeof(unsigned char) * len + 1)))
		return (NULL);
	i = 0;
	while (code && i < (int)ft_strlen(code) && code[i] != '\0')
	{
		if (code[i] == ' ')
			i++;
		tmp = ft_strsub(code, i, 4);
		res[j] = hex_dec(tmp);
		i += 4;
		j++;
	}
	res[len] = '\0';
	return (res);
}

unsigned char	hex_dec(char *code)
{
	unsigned char	res;
	char			*tmp;
	int				nb;
	int				hex;

	tmp = ft_strsub(code, 2, 2);
	if (tmp[1] - '0' > 9)
		hex = (tmp[1] - 'a' + 10);
	else
		hex = (tmp[1] - '0');
	nb = hex;
	if (tmp[0] - '0' > 9)
		hex = (tmp[0] - 'a' + 10);
	else
		hex = (tmp[0] - '0');
	nb += hex * 16;
	res = (unsigned char)nb;
	return (res);
}

void			ft_putchar_fd_size(char c, char c2, char c3, int fd)
{
	ft_putchar_fd(c, fd);
	ft_putchar_fd(c2, fd);
	ft_putchar_fd(c3, fd);
}
