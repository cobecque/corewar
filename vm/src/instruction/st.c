/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:10:39 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/06 09:59:09 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_st(t_inf inf, t_process *pros)
{
	char			*adr;
	int				i;
	int				j;
	unsigned int	res;

//	ft_printf("st = %d %d\n", inf.val[0], inf.val[1]);
/*	if (inf.typ[1] == 1)
	{
		reg_write(pros, inf.val[0], inf.val[1], REG_SIZE);
		pros->val[inf.val[1]] = (unsigned int)inf.val[0];
	}
	else
	{
		adr = pros->ins + (inf.val[1] % IDX_MOD);
		if (adr < inf.min_addr)
		{
			adr = inf.min_addr + MEM_SIZE - (inf.min_addr - adr);
		}
		else if (adr > inf.min_addr + MEM_SIZE)
			adr = inf.min_addr + MEM_SIZE - (adr - inf.min_addr + MEM_SIZE);
//		ft_printf("dans st val = %d  r = %d\n", inf.val[1], inf.val[0]);
		*(adr) = (pros->reg[inf.val[0]][0] % IDX_MOD);
		*(adr + 1) = (pros->reg[inf.val[0]][1] % IDX_MOD);
		*(adr + 2) = (pros->reg[inf.val[0]][2] % IDX_MOD);
		*(adr + 3) = (pros->reg[inf.val[0]][3] % IDX_MOD);
	}*/
	i = 0;
	res = 0;
	//ft_printf(C_GRN"Arrive de st a l'adresse %d et la val = %d\n"FC_ALL, (int)pros->ins, inf.val[1]);
	if (inf.typ[1] == 1)
	{
		while (i < 4)
		{
			res += pros->reg[inf.val[1]][i];
//			ft_printf(C_RED"yolo res tu fais quoi %d\n"FC_ALL, res);
			i++;
		}
	}
	else
		res = inf.val[1];
//	ft_printf(C_RED"yolo res tu fais quoi %d\n"FC_ALL, res);
	adr = pros->ins + ((int)res % IDX_MOD);
//	ft_printf(C_RED"yolo adr tu fais quoi %d\n"FC_ALL, adr);
	if (adr < inf.min_addr)
	{
		if ((int)adr > 0)
			adr = inf.min_addr + MEM_SIZE - ((int)inf.min_addr - ((int)adr % MEM_SIZE));
		else
			adr = inf.min_addr + MEM_SIZE + (int)adr % MEM_SIZE;
	}
	else if (adr > inf.min_addr + MEM_SIZE)
		adr = inf.min_addr + MEM_SIZE - (adr - inf.min_addr + MEM_SIZE);
	i = 0;
	j = 0;
	//ft_printf("----------------cancer en approche--------------\n");
//	ft_printf("inst du st bug = %d\n", pros->ins);
	while (j < 4)
	{
		if ((adr + j) >= inf.min_addr + MEM_SIZE)
		{
			adr = inf.min_addr;
			i = 0;
		}
		*(adr + i) = pros->reg[inf.val[0]][j]; //SEGF sur max adr
	//	ft_printf(C_RED"inst = %d adr = %d et valeur = %d\n"FC_ALL, inf.min_addr, (adr + i), pros->reg[inf.val[0]][j]);
		j++;
		i++;
	}
}
