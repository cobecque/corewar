/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:21:06 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/23 20:55:07 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_sub(t_inf inf, t_process *pros, t_pam arg)
{
	int					res;
	int					i;
	int					a;
	int					b;

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
		res = a - b;
		if (arg.ver_num.op == 1)
			ft_printf("P%5d | sub r%d r%d r%d\n", pros->number, inf.val[0], inf.val[1], inf.val[2]);
		pros->carry = (res == 0) ? 1 : 0;
		pros->val[inf.val[2]] = (int)res;
		reg_write(pros, res, inf.val[2], REG_SIZE);
	}
}
