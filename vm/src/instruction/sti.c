/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:33:00 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/26 06:55:12 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_sti(t_inf inf, t_process *pros)
{
	int		adr;

	ft_printf("sti je t'envois au combat, val = %d adresse = %d val1 = %d val2 = %d\n", *pros->pc, pros->pc, inf.val[1], inf.val[2]);
	if (inf.typ[1] == 1)
		inf.val[1] = pros->reg[inf.val[1]][3];
	if (inf.typ[2] == 1)
		inf.val[2] = pros->reg[inf.val[2]][3];
	pros->ins = (pros->ins + inf.val[1] + inf.val[2] + 3);
	if (pros->ins > (inf.min_addr + MEM_SIZE))
		pros->ins = inf.min_addr + (pros->ins - (inf.min_addr + MEM_SIZE));
	adr = *(pros->ins);
	pros->carry = (adr == 0) ? 1 : 0;
	reg_write(pros, (unsigned int)adr, inf.val[0], REG_SIZE);
}
