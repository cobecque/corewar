/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:10:39 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/26 05:39:42 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_st(t_inf inf, t_process *pros)
{
//	ft_printf(C_BLU"st je t'envoie au combat\n"FC_ALL);
	if (inf.typ[1] == 1)
		reg_write(pros, inf.val[0], inf.val[1], REG_SIZE);
	else
	{
//		ft_printf("dans st val = %d  r = %d\n", inf.val[1], inf.val[0]);
		*(pros->ins + (inf.val[1] % IDX_MOD)) = inf.val[0];
	}
}
