/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 03:40:24 by cobecque          #+#    #+#             */
/*   Updated: 2018/03/08 06:35:52 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_error(t_file file)
{
	if (file.name == NULL)
	{
		ft_printf("Error:	No name\n");
		clear_file(file);
		return (-1);
	}
	if (file.comment == NULL)
	{
		ft_printf("Error:	No Comment\n");
		clear_file(file);
		return (-1);
	}
	if (error_len(file) == -1 || error_typ(file) == -1 || error_val(file) == -1)
	{
		clear_file(file);
		return (-1);
	}
	return (0);
}

int		error_val(t_file file)
{
	t_inst	*tmp;
	int		j;

	tmp = file.ins;
	while (tmp != NULL)
	{
		j = 0;
		while (j < tmp->len)
		{
			if (tmp->typ[j] == 1 && (tmp->val[j] <= 0 ||
					tmp->val[j] > REG_NUMBER))
			{
				ft_printf("Error:	Bad value\n");
				return (-1);
			}
			j++;
		}
		tmp = tmp->next;
	}
	return (0);
}

int		error_len(t_file file)
{
	t_inst	*tmp;

	tmp = file.ins;
	while (tmp != NULL)
	{
		if (tmp->len < g_op_tab[tmp->line].nb_arg)
		{
			ft_printf("Error:	Not enough parameters\n");
			return (-1);
		}
		if (tmp->len > g_op_tab[tmp->line].nb_arg)
		{
			ft_printf("Error:	Too much parameters\n");
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int		error_typ(t_file file)
{
	t_inst	*tmp;
	int		j;
	int		typ;

	tmp = file.ins;
	while (tmp != NULL)
	{
		j = 0;
		while (j < tmp->len)
		{
			typ = tmp->typ[j];
			if (tmp->typ[j] == 4)
				typ = 2;
			if (bad_typ(typ, tmp->line, j) == -1)
			{
				ft_printf("Error:	Bad type\n");
				return (-1);
			}
			j++;
		}
		tmp = tmp->next;
	}
	return (0);
}

int		bad_typ(int typ, int line, int j)
{
	int		val;
	int		bol;
	int		tab;

	bol = 0;
	tab = 0;
	val = g_op_tab[line].tab[j];
	if ((val & 0x01) != 0)
		tab = tab | 1;
	if ((val & 0x02) != 0)
		tab = (tab << 2) | 2;
	if ((val & 0x04) != 0)
		tab = (tab << 2) | 2;
	if ((typ ^ (tab >> 4)) == 0)
		bol = 1;
	if ((typ ^ (tab >> 2)) == 0 || (typ ^ (tab >> 2)) == 4)
		bol = 1;
	if ((typ ^ tab) == 0 || (typ ^ tab) == 24 || (typ ^ tab) == 4)
		bol = 1;
	if (bol == 0)
		return (-1);
	return (0);
}
