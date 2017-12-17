/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:06:39 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/28 06:36:26 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	ft_lfork(t_inf inf, t_process *pros)
{
	t_process	*cpy;

//	ft_printf(C_GRN"lfork je t'envoie au combat -> val = %d ins = %d\n"FC_ALL, inf.val[0], pros->ins);
	cpy = dup_pros(pros, inf);
}
