/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:23:59 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/14 13:25:23 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_or(t_inf inf, t_process pros)
{
	unsigned int	res;

	res = inf.val[0] | inf.val[1];
	pros.carry = (res == 0) ? 1 : 0;
	inf.val[2] = (int)res;
}
