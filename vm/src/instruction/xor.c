/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:25:27 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/21 17:44:36 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_xor(t_inf inf, t_process *pros, t_pam arg)
{
	unsigned int	res;
	unsigned int	a;
	unsigned int	b;
	int				i;

	arg.ver = arg.ver;
/*
//	ft_printf(C_BLU"xor je t'envois au combat\t"FC_ALL);
	if (inf.typ[0] == 1)
		inf.val[0] = pros->reg[inf.val[0]][3];
	if (inf.typ[1] == 1)
		inf.val[1] = pros->reg[inf.val[1]][3];
	res = inf.val[0] ^ inf.val[1];
	pros->carry = (res == 0) ? 1 : 0;
	reg_write(pros, (unsigned int)res, inf.val[2], REG_SIZE);
	pros->val[inf.val[2]] = res;
	//inf.val[2] = (int)res;
*/
	a = 0x00;
	b = 0x00;
	i = 0;
	if (inf.typ[0] == 1)
	{
		while (i < 4)
		{
			a = (a << 8) | (pros->reg[inf.val[0]][i]);
			i++;
		}
		i = 0;
	}
	else
		a = inf.val[0];
	if (inf.typ[1] == 1)
	{
		while (i < 4)
		{
			b = (b << 8) | (pros->reg[inf.val[1]][i]);
			i++;
		}
	}
	else
		b = inf.val[1];
	res = a ^ b;
	if (arg.ver_num.op == 1)
		ft_printf("P%5d | xor %d %d r%d\n", pros->number, a, b, inf.val[2]);
	pros->val[inf.val[2]] = pros->val[inf.val[0]] ^ pros->val[inf.val[1]];
	pros->carry = (res == 0) ? 1 : 0;
	reg_write(pros, res, inf.val[2], REG_SIZE);
}
