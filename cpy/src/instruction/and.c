/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:22:19 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/26 06:49:17 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_and(t_inf inf, t_process *pros)
{
	int		res;

	if (inf.typ[0] == 1)
		inf.val[0] = pros->reg[inf.val[0]][3];
	if (inf.typ[1] == 1)
		inf.val[1] = pros->reg[inf.val[1]][3];
	res = inf.val[0] & inf.val[1];
	pros->carry = (res == 0) ? 1 : 0;
	reg_write(pros, (unsigned int)res, inf.val[2], REG_SIZE);
}
