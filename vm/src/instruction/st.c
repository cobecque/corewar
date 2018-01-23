/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:10:39 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/23 20:58:23 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_st(t_inf inf, t_process *pros, t_pam arg)
{
	char			*adr;
	int				i;
	int				j;
	unsigned int	res;
	int				bol;

	bol = 0;
	if (inf.val[0] <= 0 || inf.val[0] > REG_NUMBER)
		bol = 1;
	if (inf.typ[1] == 1 && (inf.val[1] <= 0 || inf.val[0] > REG_NUMBER))
		bol = 1;
	if (bol == 0)
	{
		i = 0;
		res = 0;
		if (inf.typ[1] == 1)
		{
			while (i < 4)
			{
				res = (res << 8) | (pros->reg[inf.val[1]][i]);
				i++;
			}
		}
		else
			res = inf.val[1];
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
		arg.ver = arg.ver;
		if (arg.ver_num.op == 1)
			ft_printf("P%5d | st r%d %d\n", pros->number, inf.val[0], res);
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
}
