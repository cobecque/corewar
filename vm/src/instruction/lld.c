/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:59:24 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/09 01:47:00 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_lld(t_inf inf, t_process *pros, t_vm vm)
{
	pros->carry = (inf.val[0] == 0) ? 1 : 0;
	reg_write(pros, inf.val[0], inf.val[1], REG_SIZE);
	if (vm.arg.ver_num.op == 1)
		ft_printf("P%5d | ld %d r%d\n", pros->number, inf.val[0], inf.val[1]);
	pros->val[inf.val[1]] = (unsigned int)inf.val[0];
}
