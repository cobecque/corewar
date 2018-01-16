/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:25:54 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/12 10:09:58 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_live(t_inf inf, t_process *pro, t_pam arg)
{
	//	ft_printf("ins = %d && live = %d %d %d %d\n", *pro->ins, *(pro->ins + 1), *(pro->ins + 2), *(pro->ins + 3), *(pro->ins + 4));
/*	if (info.val[0] < 0 || info.val[0] > info.nb)
	{
//		ft_printf("val[0] = %d et reg = %d\n", info.val[0], pro->reg[1][3]);
		if (info.val[0] == pro->reg[1][3])
		{
//			ft_printf("Le processus %d ce dit en vie\n", pro->reg[1][3]);
			pro->live++;
		}
	}*/
	int	a;
	int	b;

/*	a = pro->reg[1][0];
	ft_printf("%x\n", a);
	a = (a << 8) | pro->reg[1][1];
	ft_printf("%x\n", a);
	a = (a << 8) | pro->reg[1][2];
	ft_printf("%x\n", a);
	a = (a << 8) | pro->reg[1][3];
	ft_printf("%x\n", a);
	b = inf.val[0];*/
	a = pro->reg[1][0];
	b = pro->reg[1][1];
	a = (a << 8) | (b);
	b = pro->reg[1][2];
	a = (a << 8) | (b);
	b = pro->reg[1][3];
	a = (a << 8) | (b);
	b = inf.val[0];
/*	b = (b << 8) | (inf.val[0] << 8);
	ft_printf("%d\n", b);
	b = (b << 8) | (inf.val[0] << 16);
	ft_printf("%d\n", b);
	b = (b << 8) | (inf.val[0] << 24);
	ft_printf("%d\n", b);
*/	//ft_printf("le process %d\t", pro->number);
//	if (pro->number == 5)
//		ft_printf(" au pc %d\t", pro->ins);
	if (arg.ver == 14 && b != a)
		ft_printf("le process %d mort avec pour valeur a = %d et b = %d\n", pro->number, a, b);
	if (b == a)
	{
		if (arg.ver == 14)
			ft_printf("le process %d vie avec pour valeur a = %d et b = %d\n", pro->number, a, b);
		pro->live++;
//		ft_printf(" a %d live\n", pro->live);
	}
}
