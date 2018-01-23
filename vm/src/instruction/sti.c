/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:33:00 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/21 17:44:14 by rostroh          ###   ########.fr       */
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

//	if (inf.val[0] != 1)
	res = 0;
	r2 = 0;
	r1 = 0;
	if (inf.typ[1] == 1)
	{
		i = 0;
		while (i < 4)
		{
			r1 += pros->reg[inf.val[1]][i];
			i++;
		}
	}
	else
		r1 += inf.val[1];
	//ft_printf("res avant le r2 %d\n", res);
	if (inf.typ[2] == 1)
	{
		i = 0;
		while (i < 4)
		{
	/*		a = pro->reg[1][0];
			b = pro->reg[1][1];
			a = (a << 8) | (b);
			b = pro->reg[1][2];
			a = (a << 8) | (b);
			b = pro->reg[1][3];
			a = (a << 8) | (b);
	*/		r2 = (r2 << 8) | (pros->reg[inf.val[2]][i]);
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
		adr = adr - (inf.min_addr + MEM_SIZE) + inf.min_addr;
	i = 0;
	j = 0;
	if (arg.ver_num.op == 1)
		ft_printf("P%5d | sti r%d %d %d\n       | -> store to %d + %d = %d (with pc and mod %d)\n", pros->number, inf.val[0], r1, r2, r1, r2, res, pros->ins - inf.min_addr + res);
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
