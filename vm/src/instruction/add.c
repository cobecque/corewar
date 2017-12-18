/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:19:03 by rostroh           #+#    #+#             */
/*   Updated: 2017/12/18 10:02:48 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_add(t_inf inf, t_process *pros)
{
	int		res;

//	ft_printf("pros = %d add val = %d  %d  %d \n", pros->number, inf.val[0], inf.val[1], inf.val[2]);
	if (inf.val[0] != 0 || inf.val[1] != 0)
	{
		pros->val[inf.val[2]] = pros->val[inf.val[1]] + pros->val[inf.val[0]];
		res = (int)pros->reg[inf.val[0]][3] + (int)pros->reg[inf.val[1]][3];
	//	pros->val[inf.val[2]] = res;
		pros->carry = (res == 0) ? 1 : 0;
	//	reg_write(pros, res, inf.val[2], REG_SIZE);
	}
}
