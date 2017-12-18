/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 12:00:11 by rostroh           #+#    #+#             */
/*   Updated: 2017/12/18 09:58:42 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_ld(t_inf inf, t_process *pros)
{
	int		y;

	pros->carry = inf.val[0] == 0 ? 1 : 0;
//	ft_printf("pc = %d\n", pros->pc);
	reg_write(pros, inf.val[0], inf.val[1], REG_SIZE);
	if (*(pros->ins + 2) == -1)
	{
		y = *(pros->ins + 5);
		pros->val[inf.val[1]] = y;
	}
	else
		pros->val[inf.val[1]] = inf.val[0];
//	ft_printf("pc = %d\n", pros->pc);
}
