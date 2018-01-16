/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reg_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:19:46 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/12 08:18:24 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		reg_write(t_process *pros, unsigned int val, int reg, int size)
{
	char		*pc;
	char		*ins;
	int			i;

	pc = pros->pc;
	i = 0;
	ins = pros->ins;
//		if (pros->number == 0 && reg == 2)
//		{
//			ft_printf(C_BLU"reg_write instruction numero %d a l'adresse %d"FC_ALL, (int)(*pros->ins), (int)pros->ins);
//			ft_printf(C_BLU"  val dans reg = %d\n"FC_ALL, val);
//		}
	while (i < size)
	{
		(pros->reg[reg][i]) = (val >> ((8 * (3 - i))) & 0xFF);
//		if (pros->number == 0 && reg == 2)
//		ft_printf(C_RED"reg[%d][%d] = %d ou plutot %x\n"FC_ALL, reg, i, pros->reg[reg][i], pros->reg[reg][i]);
	i++;
	}
/*	pros->reg[reg][0] = val >> 24 & 0xFF;
		if (pros->number == 0 && reg == 2)
	ft_printf(C_RED"reg[%d][%d] = %d ou plutot %x\n"FC_ALL, reg, i, pros->reg[reg][i], pros->reg[reg][i]);
	pros->reg[reg][1] = val >> 16 & 0xFF;
		if (pros->number == 0 && reg == 2)
	ft_printf(C_RED"reg[%d][%d] = %d ou plutot %x\n"FC_ALL, reg, i, pros->reg[reg][1], pros->reg[reg][1]);
	pros->reg[reg][2] = val >> 8 & 0xFF;
		if (pros->number == 0 && reg == 2)
	ft_printf(C_RED"reg[%d][%d] = %d ou plutot %x\n"FC_ALL, reg, i, pros->reg[reg][2], pros->reg[reg][2]);
	pros->reg[reg][3] = val & 0xFF;
		if (pros->number == 0 && reg == 2)
	ft_printf(C_RED"reg[%d][%d] = %d ou plutot %x\n"FC_ALL, reg, i, pros->reg[reg][3], pros->reg[reg][3]);
*/	//ft_printf("\n");
	pros->pc = pc;
	pros->ins = ins;
}
