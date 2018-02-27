/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:23:59 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/26 19:11:36 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_or(t_inf inf, t_process *pros, t_vm *vm)
{
	int	res;
	int	a;
	int	b;

	a = 0;
	b = 0;
	if (check_r(inf) == 0)
	{
		a = catch_reg_val(0, inf, pros);
		b = catch_reg_val(1, inf, pros);
		res = a | b;
		if (vm->arg.ver_num.op == 1)
			ft_printf("P%5d | or %d %d r%d\n", pros->number, a, b, inf.val[2]);
		pros->val[inf.val[2]] = pros->val[inf.val[0]] ^ pros->val[inf.val[1]];
		pros->carry = (res == 0) ? 1 : 0;
		reg_write(pros, res, inf.val[2], REG_SIZE);
	}
}
