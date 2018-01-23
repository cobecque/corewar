/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 12:00:11 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/23 21:00:14 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_ld(t_inf inf, t_process *pros, t_pam arg)
{
	unsigned int	res;
	int				bol;

	bol = 0;
	if (inf.val[1] <= 0 || inf.val[1] > REG_NUMBER)
		bol = 1;
	if (bol == 0)
	{
		pros->carry = inf.val[0] == 0 ? 1 : 0;
		res = inf.val[0];
		if (arg.ver == 14)
			ft_printf("P%5d | ld %d r%d\n", pros->number, inf.val[0], inf.val[1]);
		pros->val[inf.val[1]] = (int)res;
		reg_write(pros, res, inf.val[1], REG_SIZE);
	}
}
