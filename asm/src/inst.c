/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 01:38:39 by cobecque          #+#    #+#             */
/*   Updated: 2018/02/13 08:22:47 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				have_ocp(int i)
{
	if (i == 0 || i == 8 || i == 11 || i == 14)
		return (-1);
	return (0);
}

unsigned int	find_val(char *par)
{
	unsigned int	nb;
	char			*tmp;
	int				i;

	if (par[0] == '%' && par[1] == ':')
		tmp = ft_strsub(par, 2, ft_strlen(par) - 2);
	else if (par[0] == '%' || par[0] == 'r')
		tmp = ft_strsub(par, 1, ft_strlen(par) - 1);
	else
		tmp = ft_strdup(par);
	i = ft_atoi(tmp);
	nb = (unsigned int)i;
	return (nb);
}

int				find_ocp(char *par)
{
	if (par[0] == '%')
		return (2);
	if (par[0] == 'r')
		return (1);
	return (3);
}

int				find_typ(char *par, int i)
{
	if (par[0] == '%' && g_op_tab[i].strange == 0)
		return (4);
	if (par[0] == '%')
		return (2);
	if (par[0] == 'r')
		return (1);
	return (2);
}
