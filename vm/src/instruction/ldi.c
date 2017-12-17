/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:28:23 by rostroh           #+#    #+#             */
/*   Updated: 2017/12/16 06:44:57 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_ldi(t_inf inf, t_process *pros)
{
	int		*adr;
	int		i;

	i = 0;
	//ft_printf(C_RED"Ldi je t'envoie au combat\n"FC_ALL);
	if (inf.typ[0] == 1)
		inf.val[0] = pros->reg[inf.val[0]][3];
	if (inf.typ[1] == 1)
		inf.val[1] = pros->reg[inf.val[1]][3];
	adr = pros->ins + ((inf.val[0]) + (inf.val[1]));
//	ft_printf("%d\n", inf.val[0] + inf.val[1]);
	pros->carry = (adr == 0) ? 1 : 0;
	//reg_write(pros, (unsigned int)(*adr), inf.val[2], REG_SIZE);
	while (i < 4)
	{
		pros->reg[inf.val[2]][i] = *(adr + i);
		pros->val[inf.val[2]] += *(adr + i);
		i++;
	}
}
