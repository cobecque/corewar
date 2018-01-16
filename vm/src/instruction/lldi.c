/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:02:39 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/12 08:08:18 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_lldi(t_inf inf, t_process *pros, t_pam arg)
{
	int	adr;

	arg.ver = arg.ver;
	if (inf.typ[0] == 1)
		inf.val[0] = pros->reg[inf.val[0]][3];
	if (inf.typ[1] == 1)
		inf.val[1] = pros->reg[inf.val[1]][3];
	adr = ((inf.val[0]) + (inf.val[1]));
	pros->carry = (adr == 0) ? 1 : 0;
	reg_write(pros, (unsigned int)adr, inf.val[2], REG_SIZE);
	pros->val[inf.val[2]] = (unsigned int)adr;
}
