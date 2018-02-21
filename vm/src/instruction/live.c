/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:25:54 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/21 18:44:27 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_live(t_inf inf, t_process *pro, t_vm vm)
{
	int	a;
	int	b;
	int	i;

	i = 0;
	a = pro->reg[1][0];
	b = pro->reg[1][1];
	a = (a << 8) | (b);
	b = pro->reg[1][2];
	a = (a << 8) | (b);
	b = pro->reg[1][3];
	a = (a << 8) | (b);
	b = inf.val[0];
	if (vm.arg.ver_num.op == 1)
		ft_printf("P%5d | live %d\n", pro->number, b);
	while (i < vm.nb_pros)
	{
		if (b == vm.play[i].r1)
		{
			if (vm.arg.ver_num.li == 1)
				ft_printf("Player %d (%s) is said to be alive\n", vm.play[i].nb, vm.play[i].name);
			pro->last_live[1] = vm.play[i].nb;
			break ;
		}
		else
			pro->last_live[1] = 0;
		i++;
	}
	pro->live++;
	pro->last_live[0] = pro->start_cycle + 11;
}
