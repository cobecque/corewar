/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:19:03 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/08 08:44:54 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int			check_r(t_inf inf)
{
	if (inf.val[0] <= REG_NUMBER && inf.val[0] > 0 && inf.val[1] <= REG_NUMBER
			&& inf.val[1] > 0 && inf.val[2] > 0 && inf.val[2] <= REG_NUMBER)
		return (0);
	return (1);
}

void		ft_add(t_inf inf, t_process *pros, t_vm *vm)
{
	int					a;
	int					b;
	int					res;

	if (check_r(inf) == 0)
	{
		a = catch_reg_val(0, inf, pros);
		b = catch_reg_val(1, inf, pros);
		res = a + b;
		if (vm->arg.ver_num.op == 1)
			ft_printf("P%5d | add r%d r%d r%d\n", pros->number,
					inf.val[0], inf.val[1], inf.val[2]);
		pros->carry = (res == 0) ? 1 : 0;
		pros->val[inf.val[2]] = (int)res;
		reg_write(pros, res, inf.val[2], REG_SIZE);
	}
}
