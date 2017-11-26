/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reg_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:19:46 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/24 05:05:04 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		reg_write(t_process *pros, unsigned int val, int reg, int size)
{
	int			i;

	i = 0;
	size = 0;
	//while (i < size)
	//i	
	//{
//		(unsigned char)pros->reg[reg][3] = (val >> ((size - (i + 1)) * 8)) & 0xFF;
//		i++;
//	}
		ft_printf("val = %d\n", val);
		/*(unsigned char)*/(pros->reg[reg][0]) = (val >> 24) & 0xFF;
		/*(unsigned char)*/(pros->reg[reg][1]) = (val >> 16) & 0xFF;
		/*(unsigned char)*/(pros->reg[reg][2]) = (val >> 8) & 0xFF;
		/*(unsigned char)*/(pros->reg[reg][3]) = val & 0xFF;
		ft_printf("REG[%d]  = %d\t", reg, (pros->reg[reg][0]));
		ft_printf("REG[%d]  = %d\t", reg, (pros->reg[reg][1]));
		ft_printf("REG[%d]  = %d\t", reg, (pros->reg[reg][2]));
		ft_printf("REG[%d]  = %d\n", reg, (pros->reg[reg][3]));
}
