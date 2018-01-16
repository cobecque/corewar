/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:21:06 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/12 08:10:10 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_sub(t_inf inf, t_process *pros, t_pam arg)
{
	int	res;

	arg.ver = arg.ver;
	inf.val[0] = pros->reg[inf.val[0]][3];
	inf.val[1] = pros->reg[inf.val[1]][3];
	res = inf.val[0] - inf.val[1];
	pros->carry = (res == 0) ? 1 : 0;
	reg_write(pros, (unsigned int)res, inf.val[2], REG_SIZE);
	pros->val[inf.val[2]] = (unsigned int)res;
}
