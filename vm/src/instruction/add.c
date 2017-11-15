/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:19:03 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/14 13:22:14 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_add(t_inf inf, t_process pros)
{
	int		res;

	res = inf.val[0] + inf.val[1];
	pros.carry = (res == 0) ? 1 : 0;
	inf.val[2] = res;
}
