/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:26:36 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/26 05:40:06 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_zjmp(t_inf inf, t_process *pros)
{
//	ft_printf(C_YEL"zjmp je t'envois au combat -> val = %d\n"FC_ALL, inf.val[0]);
	if (pros->carry == 1)
	{
//		ft_putstr("hey\n");
		pros->ins = pros->ins + (inf.val[0]  % IDX_MOD);
	}
}
