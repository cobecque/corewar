/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:33:00 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/14 13:34:33 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_sti(t_inf inf, t_process pros)
{
	void	*adr;

	adr = inf.val[1] + inf.val[2];
	pros.carry = (adr == 0) ? 1 : 0;
	reg_write((int)adr, inf.val[0], REG_SIZE);
}
