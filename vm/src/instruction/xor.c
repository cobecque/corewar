/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:25:27 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/24 18:16:26 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_xor(t_inf inf, t_process *pros, t_vm *vm)
{
	int	res;
	int	a;
	int	b;
	int	i;

	a = 0;
	b = 0;
	if (check_r(inf) == 0)
	{
		if (inf.typ[0] == 1)
		{
			i = 0;
			while (i < 4)
			{
				a = (a << 8) | (pros->reg[inf.val[0]][i]);
				i++;
			}
		}
		else
			a = inf.val[0];
		if (inf.typ[1] == 1)
		{
			i = 0;
			while (i < 4)
			{
				b = (b << 8) | (pros->reg[inf.val[1]][i]);
				i++;
			}
		}
		else
			b = inf.val[1];
		res = a ^ b;
		if (vm->arg.ver_num.op == 1)
			ft_printf("P%5d | xor %d %d r%d\n", pros->number, a, b, inf.val[2]);
		pros->val[inf.val[2]] = pros->val[inf.val[0]] ^ pros->val[inf.val[1]];
		pros->carry = (res == 0) ? 1 : 0;
		reg_write(pros, res, inf.val[2], REG_SIZE);
	}
}
