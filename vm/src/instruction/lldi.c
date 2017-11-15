/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:02:39 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/14 14:05:29 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_lldi(t_inf inf, t_process pros)
{
	void	*adr;

	adr = inf.val[0] + inf.val[1];
	if (adr <= MEM_SIZE)
	{
		pros.carry = (adr == 0) ? 1 : 0;
		reg_write((int)adr, inf.val[2], REG_SIZE);
	}
}
