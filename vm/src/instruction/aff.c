/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:10:27 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/26 15:17:52 by rostroh          ###   ########.fr       */
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
	vm->arg.ver = vm->arg.ver;
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
		ft_printf("Aff : %c\n", res);
	}
}
