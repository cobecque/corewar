/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:25:54 by rostroh           #+#    #+#             */
/*   Updated: 2017/12/18 07:46:36 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_live(t_inf info, t_process *pro)
{
	//	ft_printf("ins = %d && live = %d %d %d %d\n", *pro->ins, *(pro->ins + 1), *(pro->ins + 2), *(pro->ins + 3), *(pro->ins + 4));
	if (info.val[0] < 0 || info.val[0] > info.nb)
	{
//		ft_printf("val[0] = %d et reg = %d\n", info.val[0], pro->reg[1][3]);
		if (info.val[0] == pro->reg[1][3])
		{
//			ft_printf("Le processus %d ce dit en vie\n", pro->reg[1][3]);
			pro->live++;
		}
	}
}
