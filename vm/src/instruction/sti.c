/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:33:00 by rostroh           #+#    #+#             */
/*   Updated: 2017/12/17 09:23:31 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int			relative(int *adr, int val)
{
	int		ret;

	ret = (int)adr;
//	ft_printf("%d et %d\n", adr, ret);
	return (ret + val);
}

void		ft_sti(t_inf inf, t_process *pros)
{
	int			ret;
	int			*adr;

	ret = 0;
//	if (pros->start_cycle >= 3340)
//		ft_printf(C_BLU"Sti je t'envoie au combat, %d %d %d\n"FC_ALL, inf.val[0], inf.val[1], inf.val[2]);
	if (inf.typ[1] == 1)
	{
//		ft_putchar('a');
		ret += pros->val[inf.val[1]];
	}
	else
		ret += inf.val[1];
	if (inf.typ[2] == 1)
	{
//		ft_putchar('b');
		ret += pros->val[inf.val[2]];
//		if (pros->start_cycle >= 3340)
//			ft_printf("\tr2 = %d\t", pros->val[inf.val[2]]);
	}
	else
		ret += inf.val[2];
	if (ret < 0)
		ret /= 4;
	adr = pros->ins + (int)ret;
//	if (pros->start_cycle >= 3340)
//		ft_printf("\tret = %d\n", ret);
	if (adr < inf.min_addr)
	{
	//	ft_printf("LE CALCUL : %d pour %d %d et %d %d\n", (int)adr, pros->ins, (MEM_SIZE) + inf.min_addr, inf.min_addr, (int)adr % MEM_SIZE);
//		adr = inf.min_addr + MEM_SIZE / 4 + ((int)adr % MEM_SIZE - (int)inf.min_addr);
//		ft_putchar('c');
//		ft_printf("1: adr = %d, max_adr = %d, trop = %d\n", adr, inf.min_addr + MEM_SIZE, (int)adr % MEM_SIZE);
		adr = inf.min_addr + MEM_SIZE + (int)adr % MEM_SIZE;
//		ft_printf("2: adr = %d\n", adr);
		//adr = (int)adr % MEM_SIZE;
	}
	else if (adr > inf.min_addr + MEM_SIZE)
	{
//		ft_putchar('d');
		adr = inf.min_addr + (int)adr % MEM_SIZE;
	}
	if (pros->start_cycle >= 3340)
		ft_printf("\tadr = %d\n", adr);
//	relative(adr, MEM_SIZE);
	*(adr) = pros->reg[inf.val[0]][0]; //SEGF sur max adr
//	ft_printf("1 = %d\n", *(adr));
	*(adr + 1) = pros->reg[inf.val[0]][1];
//	ft_printf("2 = %d\n", *(adr + 1));
	*(adr + 2) = pros->reg[inf.val[0]][2];
//	ft_printf("3 = %d\n", *(adr + 2));
	*(adr + 3) = pros->reg[inf.val[0]][3];
//	ft_printf("4 = %d\n", *(adr + 3));
}
