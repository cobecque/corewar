/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:02:39 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/11 05:33:32 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_lldi(t_inf inf, t_process *pros, t_vm vm)
{
	int				res;
	char			*adr;
	int				i;
	int				r1;
	int				r2;
	int				j;
	int				bol;
	int				lol;

	res = 0;
	bol = 0;
	r1 = 0;
	if (inf.val[2] <= 0 || inf.val[2] > REG_NUMBER)
		bol = 1;
	if ((inf.typ[0] == 1 && (inf.val[0] <= 0 || inf.val[0] > REG_NUMBER)) || (inf.typ[1] == 1 && (inf.val[1] <= 0 || inf.val[1] > REG_NUMBER)))
		bol = 1;
	if (bol == 0)
	{
		if (inf.typ[0] == 1)
		{
			i = 0;
			while (i < 4)
			{
				r1 = (r1 << 8) | (pros->reg[inf.val[0]][i]);
				i++;
			}
		}
		else
			r1 += inf.val[0];
		r2 = 0;
		if (inf.typ[1] == 1)
		{
			i = 0;
			while (i < 4)
			{
				r2 = (r2 << 8) | (pros->reg[inf.val[1]][i]);
				i++;
			}
		}
		else
			r2 += inf.val[1];
		res = r1 + r2;
		adr = pros->ins + res;
		lol = (int)adr;
		if (adr < inf.min_addr)
		{
			if ((int)adr > 0)
				adr = inf.min_addr + MEM_SIZE - ((int)inf.min_addr - ((int)adr % MEM_SIZE));
			else
				adr = inf.min_addr + MEM_SIZE + (int)adr % MEM_SIZE;
		}
		else if (adr >= (inf.min_addr + MEM_SIZE))
		{
			bol = (int)adr;
			if (bol >= (int)inf.min_addr + MEM_SIZE)
			{
				while (bol > (MEM_SIZE + (int)inf.min_addr))
				{
					adr = adr - MEM_SIZE;
					bol = bol - MEM_SIZE;
				}
				if (adr < inf.min_addr)
				{
					if (adr < 0)
					{
						adr = (int)inf.min_addr + MEM_SIZE + adr;
					}
					else
						adr = (inf.min_addr + MEM_SIZE) - (int)adr;
				}
			}
		}
		if (lol > 4456 || lol < -80)
			lol = (int)adr;
		if (lol < 0 && lol > -80)
			lol = lol + 256;
		j = 0;
		i = 0;
		if (vm.arg.ver_num.op == 1)
			ft_printf("P%5d | lldi %d %d r%d\n       | -> load from %d + %d = %d (with pc and mod %d)\n", pros->number, r1, r2, inf.val[2], r1, r2, res, lol - 256);
		while (j < 4)
		{
			if ((adr + j) >= inf.min_addr + MEM_SIZE)
			{
				adr = inf.min_addr;
				i = 0;
			}
			pros->reg[inf.val[2]][j] = *(adr + i);
			i++;
			j++;
		}
	}
}
