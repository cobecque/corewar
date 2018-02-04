/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:25:54 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/04 15:35:30 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_live(t_inf inf, t_process *pro, t_pam arg)
{
	int	a;
	int	b;

	a = pro->reg[1][0];
	b = pro->reg[1][1];
	a = (a << 8) | (b);
	b = pro->reg[1][2];
	a = (a << 8) | (b);
	b = pro->reg[1][3];
	a = (a << 8) | (b);
	b = inf.val[0];
	if (arg.ver_num.op == 1)
		ft_printf("P%5d | live %d\n", pro->number, b);
	if (b == -1 || b == -2 || b == -3)
	{
		if (b < MAX_PLAYERS)
		{
			pro->live_champ[b]++;
			if (arg.ver_num.li == 1)
			{
				if (b == -1)
					ft_printf("Player %d (helltrain) is said to be alive\n", -b);
				if (b == -2)
					ft_printf("Player %d (helltrain) is said to be alive\n", -b);
				if (b == -3)
					ft_printf("Player %d (fluttershy) is said to be alive\n", -b);
			}
			pro->last_live[1] = -b;
		}
	}
	pro->live++;
	pro->last_live[0] = pro->start_cycle + 11;

}
