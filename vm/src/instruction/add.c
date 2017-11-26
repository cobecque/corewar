/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:19:03 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/26 05:38:24 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_add(t_inf inf, t_process *pros)
{
	int		res;

//	ft_putstr("on est la\n");
	res = pros->reg[inf.val[0]][3] + pros->reg[inf.val[1]][3];
	//res = inf.val[0] + inf.val[1];
	pros->carry = (res == 0) ? 1 : 0;
	reg_write(pros, (unsigned int)res, inf.val[2], REG_SIZE);
	//inf.val[2] = res;
}
