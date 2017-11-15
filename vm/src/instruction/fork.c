/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:34:49 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/14 14:07:18 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_process	dup_pros(t_process src)
{
	t_process	new;
	int			i;

	i = 0;
	while (i < REG_NUMBER)
	{
		new.reg[i] = cpy_reg(src.reg[i]);
		i++;
	}
	new.pc = NULL;
	new.carry = src.carry;
	new.live = src.live;
	new.number = src.number;
	new.next = NULL;
	return (new);
}

int			*cpy_reg(int *tab)
{
	int		i;
	int		*res;

	i = -1;
	if (!(res = (int *)malloc(sizeof(int) * REG_SIZE)))
		return (NULL);
	while (++i < REG_SIZE)
		res[i] = tab[i];
	return (res);
}

t_process	ft_fork(t_inf inf, t_process pros)
{
	t_process	*cpy;

	cpy = dup_pros(pros);
	cpy.pc = *(pros.pc + (inf.val[0] % IDX_MOD));
	return (cpy);
}
