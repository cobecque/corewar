/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:28:23 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/26 04:33:39 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_ldi(t_inf inf, t_process *pros, t_pam arg)
{
	int	res;
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
		adr = pros->ins + (int)res;
		if (adr < inf.min_addr)
		{
			if ((int)adr > 0)
				adr = inf.min_addr + MEM_SIZE - ((int)inf.min_addr - ((int)adr % MEM_SIZE));
			else
				adr = inf.min_addr + MEM_SIZE + (int)adr % MEM_SIZE;
		}
		else if (adr >= inf.min_addr + MEM_SIZE)
		{
			bol = (int)adr % MEM_SIZE;
			adr = (bol + inf.min_addr);
		}
		lol = (int)pros->ins + (int)res;
		if (lol > 4456 || lol < 0)
			lol = (int)adr - (int)inf.min_addr;
		lol = lol - (int)inf.min_addr;
		pros->carry = (adr == 0) ? 1 : 0;
		j = 0;
		i = 0;
		if (arg.ver_num.op == 1)
			ft_printf("P%5d | ldi %d %d r%d\n       | -> load from %d + %d = %d (with pc and mod %d)\n", pros->number, r1, r2, inf.val[2], r1, r2, res, lol);
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
