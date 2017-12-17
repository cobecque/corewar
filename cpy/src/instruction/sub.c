/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:21:06 by rostroh           #+#    #+#             */
/*   Updated: 2017/12/13 23:01:36 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_sub(t_inf inf, t_process *pros)
{
	int	res;

	inf.val[0] = pros->reg[inf.val[0]][3];
	inf.val[1] = pros->reg[inf.val[1]][3];
	res = inf.val[0] - inf.val[1];
	pros->carry = (res == 0) ? 1 : 0;
	reg_write(pros, (unsigned int)res, inf.val[2], REG_SIZE);
	pros->val[inf.val[2]] = (unsigned int)res;
}