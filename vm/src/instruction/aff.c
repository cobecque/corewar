/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:10:27 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/12 08:56:12 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_aff(t_inf inf, t_process *pros, t_pam arg)
{
	unsigned char		res;
	
	arg.ver = arg.ver;
/*	res = (pros->reg[inf.val[0]][0] >> 24) & 0xFF;
	res += ((pros->reg[inf.val[0]][1] >> 16) & 0xFF);
	res += ((pros->reg[inf.val[0]][2] >> 8) & 0xFF);
	res += (pros->reg[inf.val[0]][2] & 0xFF);
	aff = res % 256;*/
	res = inf.val[0];
	pros->carry = pros->carry;
//	ft_printf("%d\n", aff);
}
