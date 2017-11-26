/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:33:00 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/25 06:26:41 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_sti(t_inf inf, t_process *pros)
{
	int		adr;

	//ft_putchar('a');
//	adr = (int *)malloc(sizeof(int) * 1);
	ft_printf(C_YEL"sti je t'envoie au combat\n"FC_ALL);
//	ft_printf("val1 = %d et val2 = %d min = %d et ins = %d\n", inf.val[1], inf.val[2], inf.min_addr, pros->ins);
	pros->ins = (pros->ins + inf.val[1] + inf.val[2] + 3);
//	ft_printf("AVANT proc = %d\n", *pros->ins);
	if (pros->ins > (inf.min_addr + MEM_SIZE))
		pros->ins = inf.min_addr + (pros->ins - (inf.min_addr + MEM_SIZE));
//	ft_printf("APRES proc = %d\n", *pros->ins);
	adr = *(pros->ins);// + inf.val[1] + inf.val[2]);
//	ft_printf("adr - %d\n", adr);
	pros->carry = (adr == 0) ? 1 : 0;
	reg_write(pros, (unsigned int)adr, inf.val[0], REG_SIZE);
}
