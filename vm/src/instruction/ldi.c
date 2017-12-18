/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:28:23 by rostroh           #+#    #+#             */
/*   Updated: 2017/12/18 10:22:16 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_ldi(t_inf inf, t_process *pros)
{
	char	*adr;
	int		i;
	int		res;

	i = 0;
	res = 0;
	//ft_printf(C_RED"Ldi je t'envoie au combat\n"FC_ALL);
	if (inf.typ[0] != 1)
	{
		if (*(pros->ins + 2) == -1)
			res = *(pros->ins + 3);
		else
			res = inf.val[0];
	}
/*	if (inf.typ[1] != 1)
	{
		if (*(pros->ins + 2) == -1)
			res = *(pros->ins + 3);
		else
			res = inf.val[0];
	}*/
	if (inf.typ[0] == 1)
		res += pros->val[inf.val[0]];
		//inf.val[0] = pros->reg[inf.val[0]][3];
	if (inf.typ[1] == 1)
		//inf.val[1] = pros->reg[inf.val[1]][3];
		res += pros->val[inf.val[1]];
	adr = pros->ins + res;
//	ft_printf("%d\n", inf.val[0] + inf.val[1]);
	pros->carry = (adr == 0) ? 1 : 0;
	//reg_write(pros, (unsigned int)(*adr), inf.val[2], REG_SIZE);
	while (i < 4)
	{
		pros->reg[inf.val[2]][i] = *(adr + i);
		pros->val[inf.val[2]] += *(adr + i);
		i++;
	}
	//	ft_printf("%d\n", pros->val);
}
