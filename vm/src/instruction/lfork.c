/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:06:39 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/09 01:43:37 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	ft_lfork(t_inf inf, t_process *pros, t_vm vm)
{
	t_process	*cpy;

//	ft_printf(C_GRN"lfork je t'envoie au combat -> val = %d ins = %d\n"FC_ALL, inf.val[0], pros->ins);
	cpy = dup_pros(pros, inf, vm);
}
