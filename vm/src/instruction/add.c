/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:19:03 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/19 18:42:21 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_add(t_inf inf, t_process *pros, t_pam arg)
{
	unsigned int		res;
	int					i;
	int					ff;
	int					fuck;

	arg.ver = arg.ver;
	ff = 0;
	fuck = 0;
	/*if (inf.val[0] != 0 || inf.val[1] != 0)
	{
		pros->val[inf.val[2]] = pros->val[inf.val[1]] + pros->val[inf.val[0]];
		res = (int)pros->reg[inf.val[0]] + (int)pros->reg[inf.val[1]][3];
		pros->carry = (res == 0) ? 1 : 0;
	//	reg_write(pros, res, inf.val[2], REG_SIZE);
	}*/
	if (inf.val[0] != 0 || inf.val[1] != 0)
	{
		i = 0;
		res = 0;
		while (i < 4)
		{
			if (ff == 0 && pros->reg[inf.val[0]][i] == 255)
				;
			else
			{
				if (ff == 0 && i > 0)
					res += -256 + pros->reg[inf.val[0]][i];
				else
				{
					res += pros->reg[inf.val[0]][i];
					ff = 1;
				}
			}
			if (fuck == 0 && pros->reg[inf.val[1]][i] == 255)
				;
			else
			{
				if (fuck == 0 && i > 0)
					res += -256 + pros->reg[inf.val[1]][i];
				else
				{
					res += pros->reg[inf.val[1]][i];
					fuck = 1;
				}
			}
			i++;
		}
		if (arg.ver == 14)
			ft_printf("P%5d | add r%d r%d r%d\n", pros->number, inf.val[0], inf.val[1], inf.val[2]);
		//ft_printf(C_GRN"yolo yolo pros numero %d avec res = %d\n"FC_ALL, pros->number, res);
		pros->carry = (res == 0) ? 1 : 0;
		pros->val[inf.val[2]] = (int)res;
		reg_write(pros, res, inf.val[2], REG_SIZE);
	}
}
