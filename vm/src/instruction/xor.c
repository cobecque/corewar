/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:25:27 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/05 02:59:16 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_xor(t_inf inf, t_process *pros, t_vm *vm)
{
	int			a;
	int			b;
	int			res;
	int			bol;

	a = 0;
	b = 0;
	bol = is_reg_good(inf, pros->line);
	if (bol == 1)
	{
		a = catch_reg_val(0, inf, pros);
		b = catch_reg_val(1, inf, pros);
		res = a ^ b;
		if (vm->arg.ver_num.op == 1)
			ft_printf("P%5d | xor %d %d r%d\n", pros->number, a, b, inf.val[2]);
		pros->val[inf.val[2]] = pros->val[inf.val[0]] ^ pros->val[inf.val[1]];
		pros->carry = (res == 0) ? 1 : 0;
		reg_write(pros, res, inf.val[2], REG_SIZE);
	}
}
