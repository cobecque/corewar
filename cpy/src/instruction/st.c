/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:10:39 by rostroh           #+#    #+#             */
/*   Updated: 2017/12/13 23:03:19 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_st(t_inf inf, t_process *pros)
{
	int		*adr;

	adr = NULL;
//	ft_printf(C_BLU"st je t'envoie au combat\n"FC_ALL);
	if (inf.typ[1] == 1)
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
	}
}
