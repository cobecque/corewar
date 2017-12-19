/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 12:00:11 by rostroh           #+#    #+#             */
/*   Updated: 2017/12/19 13:55:31 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_ld(t_inf inf, t_process *pros)
{
	unsigned int	res;
//	int				y;
/*
	pros->carry = inf.val[0] == 0 ? 1 : 0;
	reg_write(pros, inf.val[0], inf.val[1], REG_SIZE);
	if (*(pros->ins + 2) == -1)
	{
		y = *(pros->ins + 5);
		pros->val[inf.val[1]] = y;
	}
	else
		pros->val[inf.val[1]] = inf.val[0];
*/
	pros->carry = inf.val[0] == 0 ? 1 : 0;
	res = inf.val[0];
//	ft_printf(C_RED"ld a l'adresse %d avec res = %d et pros numero %d registre %d\n"FC_ALL, (int)pros->ins, res, pros->number, inf.val[1]);
	pros->val[inf.val[1]] = (int)res;
	reg_write(pros, res, inf.val[1], REG_SIZE);
}
