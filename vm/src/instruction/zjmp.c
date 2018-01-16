/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:26:36 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/12 09:30:25 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_zjmp(t_inf inf, t_process *pros, t_pam arg)
{
//	ft_printf(C_YEL"zjmp je t'envois au combat -> val = %d\n"FC_ALL, inf.val[0]);
	if (arg.ver == 14 && pros->carry == 0)
		ft_printf("pros = %d zjmp KO\n", pros->number);
	if (pros->carry == 1)
	{
		if (arg.ver == 14)
			ft_printf("pros = %d zjmp OK\n", pros->number);
//		ft_putstr("hey\n");
		pros->ins = pros->ins + (inf.val[0]  % IDX_MOD);
		pros->pc = pros->ins;
	}
}
