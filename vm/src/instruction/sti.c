/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:33:00 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/16 20:18:12 by rostroh          ###   ########.fr       */
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
	int				bug;
	int				i;
	int				j;
	int				ff;

	ff = 0;
//	if (inf.val[0] != 1)
	res = 0;
	bug = 0;
	if (inf.typ[1] == 1)
	{
		i = 0;
		while (i < 4)
		{
			res += pros->reg[inf.val[1]][i];
			i++;
		}
	}
	else
		res += inf.val[1];
	//ft_printf("res avant le r2 %d\n", res);
	if (inf.typ[2] == 1)
	{
		i = 0;
		while (i < 4)
		{
			if (ff == 0 && pros->reg[inf.val[2]][i] == 255)
				;
			else
			{
				if (ff == 0 && i > 0)
				{
					bug += (-256 + pros->reg[inf.val[2]][i]);
				}
				else
					bug += pros->reg[inf.val[2]][i];
	//			ft_printf("res apres le r2 %d && pros>reg = %d\n", bug, pros->reg[inf.val[2]][i]);
				ff = 1;
			}
			i++;
		}
	}
	else
		res += inf.val[2];
	//if (inf.val[0] != 1)
	res = (int)res + (int)bug;
	adr = pros->ins + ((int)res % IDX_MOD);
	if (adr < inf.min_addr)
	{
		if ((int)adr > 0)
			adr = inf.min_addr + MEM_SIZE - ((int)inf.min_addr - ((int)adr % MEM_SIZE));
		else
			adr = inf.min_addr + MEM_SIZE + (int)adr % MEM_SIZE;
	}
	else if (adr > inf.min_addr + MEM_SIZE)
		adr = adr - (inf.min_addr + MEM_SIZE) + inf.min_addr;
	i = 0;
	j = 0;
	if (arg.ver == 14)
		ft_printf("P%5d | sti r%d %d %d\n       | -> store to %d + %d = %d (with pc and mod %d)\n", pros->number, inf.val[0], inf.val[1], inf.val[2], inf.val[1], inf.val[2], res, pros->ins - inf.min_addr + res);
//	ft_printf(C_RED"%d\n"FC_ALL, inf.min_addr);
	while (j < 4)
	{
		if ((adr + j) >= inf.min_addr + MEM_SIZE)
		{
			adr = inf.min_addr;
			i = 0;
		}
		*(adr + i) = pros->reg[inf.val[0]][j]; //SEGF sur max adr
		j++;
		i++;
	}
}
