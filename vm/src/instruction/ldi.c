/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:28:23 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/21 17:39:54 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_ldi(t_inf inf, t_process *pros, t_pam arg)
{
	arg.ver = arg.ver;
/*	char	*adr;
	int		i;
	int		res;

	i = 0;
	res = 0;
	if (inf.typ[0] != 1)
	{
		if (*(pros->ins + 2) == -1)
			res = *(pros->ins + 3);
		else
			res = inf.val[0];
	}
	if (inf.typ[0] == 1)
		res += pros->val[inf.val[0]];
	if (inf.typ[1] == 1)
		res += pros->val[inf.val[1]];
	adr = pros->ins + res;
	pros->carry = (adr == 0) ? 1 : 0;
	while (i < 4)
	{
		pros->reg[inf.val[2]][i] = *(adr + i);
		pros->val[inf.val[2]] += *(adr + i);
		i++;
	}*/
	unsigned int	res;
	char			*adr;
	int				i;
	int				r1;
	int				r2;
	int				j;

	//ft_printf(C_YEL"coucou je suis le ldi a l'adresse %d\n"FC_ALL, pros->ins);
	res = 0;
	if (inf.typ[0] == 1)
	{
		i = 0;
		while (i < 4)
		{
			res += pros->reg[inf.val[0]][i];
			i++;
		}
	}
	else
		res += inf.val[0];
	r1 = res;
	r2 = 0;
	if (inf.typ[1] == 1)
	{
		i = 0;
		while (i < 4)
		{
			r2 += pros->reg[inf.val[1]][i];
			i++;
		}
	}
	else
		r2 += inf.val[1];
	res = r1 + r2;
	adr = pros->ins + (int)res;
	pros->carry = (adr == 0) ? 1 : 0;
	if (arg.ver_num.op == 1)
		ft_printf("P%5d | ldi %d %d r%d\n       | -> load from %d + %d = %d (with pc and mod %d)\n", pros->number, r1, r2, inf.val[2], r1, r2, res, pros->ins + res - inf.min_addr);
	i = 0;
	j = 0;
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
