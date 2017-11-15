/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:06:39 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/14 14:10:13 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_process	ft_lfork(t_inf inf, t_process pros, t_vm vm)
{
	t_process	*cpy;
	cpy = dup_pros(pros);
	if (pros.pc + inf.val[0] > 0 && pros.pc + inf.val[0] <= MEM_SIZE)
	{
		cpy.pc = (pros.pc + inf.val[0]);
		return (cpy);
	}
	return (0);
}
