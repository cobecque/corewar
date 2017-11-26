/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:28:23 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/26 06:49:37 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_ldi(t_inf inf, t_process *pros)
{
	int	adr;

	if (inf.typ[0] == 1)
		inf.val[0] = pros->reg[inf.val[0]][3];
	if (inf.typ[1] == 1)
		inf.val[1] = pros->reg[inf.val[1]][3];
	adr = ((inf.val[0] % IDX_MOD) + (inf.val[1] % IDX_MOD));
	pros->carry = (adr == 0) ? 1 : 0;
	reg_write(pros, (unsigned int)adr, inf.val[2], REG_SIZE);
}
