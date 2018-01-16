/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:06:39 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/12 08:12:12 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	ft_lfork(t_inf inf, t_process *pros, t_pam arg)
{
	t_process	*cpy;

	arg.ver = arg.ver;
//	ft_printf(C_GRN"lfork je t'envoie au combat -> val = %d ins = %d\n"FC_ALL, inf.val[0], pros->ins);
	cpy = dup_pros(pros, inf, arg);
}
