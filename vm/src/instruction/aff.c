/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:10:27 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/06 09:19:17 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_aff(t_inf inf, t_process *pros, t_vm *vm)
{
	int		res;
	int		i;
	int		bol;

	i = 0;
	res = 0;
	bol = 0;
	if (inf.val[0] <= 0 || inf.val[0] > REG_NUMBER)
		bol = 1;
	if (bol == 0)
	{
		while (i < 4)
		{
			res = (res << 8) | pros->reg[inf.val[0]][i];
			i++;
		}
		res = res % 256;
		if (vm->arg.a == 1)
			ft_printf("Aff : %c\n", res);
	}
}
