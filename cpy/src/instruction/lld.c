/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:59:24 by rostroh           #+#    #+#             */
/*   Updated: 2017/12/13 22:57:44 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_lld(t_inf inf, t_process *pros)
{
	pros->carry = (inf.val[0] == 0) ? 1 : 0;
	reg_write(pros, inf.val[0], inf.val[1], REG_SIZE);
	pros->val[inf.val[1]] = (unsigned int)inf.val[0];
}
