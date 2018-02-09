/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:10:27 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/09 01:44:21 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_aff(t_inf inf, t_process *pros, t_vm vm)
{
	unsigned char		res;
	
	vm.arg.ver = vm.arg.ver;
/*	res = (pros->reg[inf.val[0]][0] >> 24) & 0xFF;
	res += ((pros->reg[inf.val[0]][1] >> 16) & 0xFF);
	res += ((pros->reg[inf.val[0]][2] >> 8) & 0xFF);
	res += (pros->reg[inf.val[0]][2] & 0xFF);
	aff = res % 256;*/
	res = inf.val[0];
	pros->carry = pros->carry;
//	ft_printf("%d\n", aff);
}
