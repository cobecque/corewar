/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:28:23 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/14 13:32:54 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_ldi(t_inf inf, t_process pros)
{
	 void	*adr;

	 adr = ((inf.val[0] % IDX_MOD) + (inf.val[1] % IDX_MOD));
	 pros.carry = (adr == 0) ? 1 : 0;
	 reg_write((int)adr, inf.val[2], REG_SIZE);
}