/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:09:56 by cobecque          #+#    #+#             */
/*   Updated: 2018/03/08 12:57:48 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void	s_message(t_process *cpy, int adv)
{
	ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", adv + 2, cpy->ins -
			cpy->inf.min_addr, cpy->ins - cpy->inf.min_addr + adv + 2);
	get_hexa(*cpy->ins, 0);
	ft_putchar(' ');
	get_hexa(cpy->ocp, 0);
}

t_process	*ocp_invalid(t_process *cpy, int *bol, int *len)
{
	int		adv;

	if (*bol == -1 || *bol == -2)
	{
		adv = adv_value(cpy->line, cpy->ocp);
		if (*bol == -2)
			s_message(cpy, adv);
		*len = 0;
		while (*len < adv)
		{
			if (*bol == -2)
			{
				ft_putchar(' ');
				get_hexa(*cpy->pc, 0);
			}
			cpy->pc++;
			if (cpy->pc == cpy->inf.min_addr + MEM_SIZE)
				cpy->pc = cpy->inf.min_addr;
			(*len)++;
		}
		if (*bol == -2)
			ft_printf(" \n");
		cpy->line = -1;
	}
	return (cpy);
}

t_process	*adv_printf(t_process *cpy, int len, int nb)
{
	int		p;
	int		i;

	i = 0;
	p = 0;
	while (i < len)
	{
		if ((cpy->ins + p + nb) >= cpy->inf.min_addr + MEM_SIZE)
		{
			nb = 0;
			p = 0;
			cpy->ins = cpy->inf.min_addr;
		}
		ft_putchar(' ');
		get_hexa(*(cpy->ins + p + nb), 0);
		p++;
		i++;
		if ((cpy->ins + p) >= cpy->inf.min_addr + MEM_SIZE)
		{
			p = 0;
			nb = 0;
			cpy->ins = cpy->inf.min_addr;
		}
	}
	return (cpy);
}

t_process	*move_pc(t_process *cpy, int len)
{
	int		i;

	i = 0;
	if (cpy->line != 8 || cpy->carry == 0)
	{
		while (i < len)
		{
			if (cpy->pc > cpy->inf.min_addr + MEM_SIZE)
				cpy->pc = (cpy->inf.min_addr + 1);
			cpy->pc++;
			i++;
		}
		if (cpy->pc > cpy->inf.min_addr + MEM_SIZE)
			cpy->pc = cpy->inf.min_addr + 1;
	}
	return (cpy);
}
