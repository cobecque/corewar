/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:33:00 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/30 04:33:36 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int			relative(int *adr, int val)
{
	int		ret;

	ret = (int)adr;
	return (ret + val);
}

void		ft_sti(t_inf inf, t_process *pros, t_pam arg)
{
	char			*adr;
	int				res;
	int				i;
	int				j;
	int				r1;
	int				r2;
	int				bol;
	int				lol;

	bol = 0;
	if (inf.val[0] <= 0 || inf.val[0] > REG_NUMBER)
		bol = 1;
	if (inf.typ[1] == 1 && (inf.val[1] <= 0 || inf.val[1] > REG_NUMBER))
		bol = 1;
	if (inf.typ[2] == 1 && (inf.val[2] <= 0 || inf.val[2] > REG_NUMBER))
		bol = 1;
	res = 0;
	r2 = 0;
	r1 = 0;
	if (bol == 0)
	{
		if (inf.typ[1] == 1)
		{
			i = 0;
			while (i < 4)
			{
				r1 = (r1 << 8) | (pros->reg[inf.val[1]][i]);
				i++;
			}
		}
		else
			r1 += inf.val[1];
		if (inf.typ[2] == 1)
		{
			i = 0;
			while (i < 4)
			{
				r2 = (r2 << 8) | (pros->reg[inf.val[2]][i]);
				i++;
			}
		}
		else
			r2 += inf.val[2];
		res = r1 + r2;
		adr = pros->ins + ((int)res % IDX_MOD);
		if (adr < inf.min_addr)
		{
			if ((int)adr > 0)
				adr = inf.min_addr + MEM_SIZE - ((int)inf.min_addr - ((int)adr % MEM_SIZE));
			else
				adr = inf.min_addr + MEM_SIZE + (int)adr % MEM_SIZE;
		}
		else if (adr >= inf.min_addr + MEM_SIZE)
		{
			bol = ((int)adr % MEM_SIZE);
			adr = (char *)((long)bol - (long)inf.min_addr);
		}
		lol = (int)pros->ins + (int)res;
		if (lol > 4456 || lol < 0)
			lol = (int)adr;
		lol = lol - (int)inf.min_addr;
		i = 0;
		j = 0;
		if (arg.ver_num.op == 1)
			ft_printf("P%5d | sti r%d %d %d\n       | -> store to %d + %d = %d (with pc and mod %d)\n", pros->number, inf.val[0], r1, r2, r1, r2, res, lol);// + inf.min_addr);
		while (j < 4)
		{
			if ((adr + j) >= inf.min_addr + MEM_SIZE)
			{
				adr = inf.min_addr;
				i = 0;
			}
			*(adr + i) = pros->reg[inf.val[0]][j]; //SEGF sur max adr
//			if (pros->start_cycle == 8648)
//				ft_printf("val %d a l'adresse %d\n", pros->reg[inf.val[0]][j], (adr + i));
			j++;
			i++;
		}
	}
}
