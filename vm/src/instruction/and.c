/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:22:19 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/21 18:27:41 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_and(t_inf inf, t_process *pros, t_pam arg)
{
	unsigned int		a;
	unsigned int		b;
	unsigned int		res;
	int					i;
	/*
	if (inf.typ[0] == 1)
		inf.val[0] = pros->reg[inf.val[0]][3];
	if (inf.typ[1] == 1)
		inf.val[1] = pros->reg[inf.val[1]][3];
	res = inf.val[0] & inf.val[1];
	pros->carry = (res == 0) ? 1 : 0;
	reg_write(pros, (unsigned int)res, inf.val[2], REG_SIZE);
*/
	arg.ver = arg.ver;
	a = 0x00;
	b = 0x00;
	if (inf.typ[0] == 1)
	{
		i = 0;
		while (i < 4)
		{
			a += pros->reg[inf.val[0]][i];
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
			b += pros->reg[inf.val[1]][i];
			i++;
		}
	}
	else
		b = inf.val[1];
	res = a & b;
	pros->val[inf.val[2]] = res;
	if (arg.ver_num.op == 1)
		ft_printf("P%5d | and %d %d r%d\n", pros->number, inf.val[0], inf.val[1], inf.val[2]);
	pros->carry = (res == 0) ? 1 : 0;
	reg_write(pros, res, inf.val[2], REG_SIZE);
}
