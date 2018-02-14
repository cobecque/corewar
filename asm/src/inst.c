/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 01:38:39 by cobecque          #+#    #+#             */
/*   Updated: 2018/02/14 09:02:38 by cobecque         ###   ########.fr       */
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

int				find_ocp(char *par, int i)
{
	if (have_ocp(i) == -1)
		return (0);
	if (par[0] == '%')
		return (2);
	if (par[0] == 'r')
		return (1);
	return (3);
}

int				find_typ(char *par, int i)
{
	if (par[0] == '%' && (g_op_tab[i].strange == 0 || i == 0))
		return (4);
	if (par[0] == '%')
		return (2);
	if (par[0] == 'r')
		return (1);
	return (2);
}

t_inst			*label_param(char **par, t_inst *ins)
{
	int		j;

	j = 0;
	ins->label1 = NULL;
	ins->label2 = NULL;
	ins->label3 = NULL;
	while (par[j] != NULL)
	{
		if (j > 0)
		{
			if (j == 1)
				ins->label1 = have_label(par[j]);
			if (j == 2)
				ins->label2 = have_label(par[j]);
			if (j == 3)
				ins->label3 = have_label(par[j]);
		}
		j++;
	}
	if (ins->label1 != NULL || ins->label2 != NULL || ins->label3 != NULL)
		ins->bol = 1;
	return (ins);
}
