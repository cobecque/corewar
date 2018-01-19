/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:19:03 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/19 19:18:39 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_add(t_inf inf, t_process *pros, t_pam arg)
{
	unsigned int		res;
	int					i;
	int					a;
	int					b;

	/*if (inf.val[0] != 0 || inf.val[1] != 0)
	  {
	  pros->val[inf.val[2]] = pros->val[inf.val[1]] + pros->val[inf.val[0]];
	  res = (int)pros->reg[inf.val[0]] + (int)pros->reg[inf.val[1]][3];
	  pros->carry = (res == 0) ? 1 : 0;
	//	reg_write(pros, res, inf.val[2], REG_SIZE);
	}*/
	/*if (inf.val[0] != 0 || inf.val[1] != 0)
	  {
	  i = 0;
	  res = 0;
	  while (i < 4)
	  {
	  b = (b << 8) | (pros->reg[inf.val[1]][i]);
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
	  }*/
	if (inf.val[0] != 0 && inf.val[1] != 0 && inf.val[2] != 0)
	{
		if (inf.typ[0] == 1)
		{
			i = 0;
			while (i < 4)
			{
				a = (a << 8) | (pros->reg[inf.val[0]][i]);
				i++;
			}
		}
		else
			a = inf.val[0];
		if (inf.typ[1] == 1)
		{
			i = 0;
			while (i < 4)
			{
				b = (b << 8) | (pros->reg[inf.val[1]][i]);
				i++;
			}
		}
		else
			b = inf.val[1];
		res = a + b;
		if (arg.ver == 14)
			ft_printf("P%5d | add r%d r%d r%d\n", pros->number, inf.val[0], inf.val[1], inf.val[2]);
		pros->carry = (res == 0) ? 1 : 0;
		pros->val[inf.val[2]] = (int)res;
		reg_write(pros, res, inf.val[2], REG_SIZE);
	}
}
