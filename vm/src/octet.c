/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octet.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 01:43:42 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/08 06:51:53 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int			*init_tab(void)
{
	int		*tab;

	if (!(tab = (int *)malloc(sizeof(int) * 3)))
		return (NULL);
	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	return (tab);
}

t_inf		other_param(t_inf srt, int line, int *tab, int ocp)
{
	int		i;

	i = 0;
	while (i < g_op_tab[line].nb_arg)
	{
		srt.l[i] = type_param(ocp, i, line, &tab[i]);
		i++;
	}
	return (srt);
}

t_inf		nb_oct(t_inf srt, int line, int ocp)
{
	int		*tab;

	tab = init_tab();
	if (ft_strcmp(g_op_tab[line].name, "live") == 0)
	{
		tab[0] = 3;
		srt.l[0] = 4;
	}
	else if (ft_strcmp(g_op_tab[line].name, "lfork") == 0 ||
			ft_strcmp(g_op_tab[line].name, "fork") == 0 ||
			ft_strcmp(g_op_tab[line].name, "zjmp") == 0)
	{
		tab[0] = 2;
		srt.l[0] = 2;
	}
	else if (line == 15)
	{
		tab[0] = 1;
		srt.l[0] = 1;
	}
	else
		srt = other_param(srt, line, tab, ocp);
	srt.typ = tab;
	return (srt);
}

t_inf		add_elem(int line, int opc)
{
	t_inf	new;

	new.length = 0;
	if (!(new.l = (int *)malloc(sizeof(int) * 3)))
		exit(-1);
	new.l[0] = 0;
	new.l[1] = 0;
	new.l[2] = 0;
	new.arg = g_op_tab[line].nb_arg;
	new = nb_oct(new, line, opc);
	return (new);
}
