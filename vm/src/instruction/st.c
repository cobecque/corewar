/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:10:39 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/21 17:42:28 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_st(t_inf inf, t_process *pros, t_pam arg)
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
	if (inf.val[0] > 0 && inf.val[0] <= REG_NUMBER)
	{
		i = 0;
		res = 0;
//		ft_printf(C_GRN"Arrive de st a l'adresse %d et la val = %d et pros %d\n"FC_ALL, (int)pros->ins, inf.val[1], pros->number);
		if (inf.typ[1] == 1)
		{
			while (i < 4)
			{
				res = (res << 8) | (pros->reg[inf.val[1]][i]);
//				ft_printf(C_RED"yolo res tu fais quoi %d\n"FC_ALL, res);
				i++;
			}
		}
		else
			res = inf.val[1];
//		ft_printf(C_RED"inf.val[1] = %d\n yolo res tu fais quoi %d\n"FC_ALL, inf.val[1], res);
		adr = pros->ins + ((int)res % IDX_MOD);
//		ft_printf(C_RED"yolo adr tu fais quoi %d\n"FC_ALL, adr);
		if (adr < inf.min_addr)
		{
			if ((int)adr > 0)
				adr = inf.min_addr + MEM_SIZE - ((int)inf.min_addr - ((int)adr % MEM_SIZE));
			else
				adr = inf.min_addr + MEM_SIZE + (int)adr % MEM_SIZE;
		}
		else if (adr >= inf.min_addr + MEM_SIZE)
			adr = adr - (inf.min_addr + MEM_SIZE) + inf.min_addr;
		i = 0;
		j = 0;
		arg.ver = arg.ver;
		if (arg.ver_num.op == 1)
			ft_printf("P%5d | st r%d %d\n", pros->number, inf.val[0], res);
			//ft_printf("st du process %d sur r%d avec pour valeur %d et pour pc %d et adr min = %d\n", pros->number, inf.val[0], res, pros->ins, inf.min_addr);
//		if (arg.ver == 14 && pros->number == 12)
//			ft_printf(C_RED"st du process %d sur r%d avec pour valeur %d et pour pc %d et adr min = %d\n"FC_ALL, pros->number, inf.val[0], res, pros->ins, inf.min_addr);
//		ft_printf(C_RED"yolo adr tu fais quoi %d\n"FC_ALL, adr);
//			ft_printf(C_BLU"inst = %d adr = %d\n"FC_ALL, pros->ins, inf.val[0]);
//		ft_printf("----------------cancer en approche--------------\n");
		while (j < 4)
		{
			if ((adr + j) >= inf.min_addr + MEM_SIZE)
			{
				adr = inf.min_addr;
				i = 0;
			}
			*(adr + i) = pros->reg[inf.val[0]][j]; //SEGF sur max adr
			//ft_printf(C_BLU"inst = %d adr = %d et valeur = %d\n"FC_ALL, pros->ins, (adr + i), pros->reg[inf.val[0]][j]);
			j++;
			i++;
		}
	}
}
