/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:26:36 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/25 02:05:57 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_zjmp(t_inf inf, t_process *pros, t_pam arg)
{
	if (arg.ver_num.op == 1 && pros->carry == 0)
		ft_printf("P%5d | zjmp %d FAILED\n", pros->number, inf.val[0]);
	if (pros->carry == 1)
	{
		if (arg.ver_num.op == 1)
			ft_printf("P%5d | zjmp %d OK\n", pros->number, inf.val[0]);
		pros->ins = pros->ins + (inf.val[0] % IDX_MOD);
		if (pros->ins >= inf.min_addr + MEM_SIZE)
			pros->ins = (pros->ins - (inf.min_addr + MEM_SIZE)) + inf.min_addr;
		if (pros->ins < inf.min_addr)
		{
			if (pros->ins >= 0)
				pros->ins = (inf.min_addr + MEM_SIZE - 1 - (int)pros->ins);
			else
				pros->ins = (int)pros->ins + (inf.min_addr + MEM_SIZE - 1);
		}
		pros->pc = pros->ins;
	}
}
