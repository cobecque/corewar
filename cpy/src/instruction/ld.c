/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 12:00:11 by rostroh           #+#    #+#             */
/*   Updated: 2017/12/13 22:56:03 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_ld(t_inf inf, t_process *pros)
{
	//ft_printf(C_RED"ld je t'envois au combat\t"FC_ALL);
	pros->carry = inf.val[0] == 0 ? 1 : 0;
//	ft_printf("pc = %d\n", pros->pc);
	reg_write(pros, (unsigned int)inf.val[0], inf.val[1], REG_SIZE);
	pros->val[inf.val[1]] = (unsigned int)inf.val[0];
//	ft_printf("pc = %d\n", pros->pc);
}