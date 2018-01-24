/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reg_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:19:46 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/24 23:02:12 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		reg_write(t_process *pros, unsigned int val, int reg, int size)
{
	char		*pc;
	char		*ins;
	int			i;

	pc = pros->pc;
	i = 0;
	ins = pros->ins;
	if (reg > 0 && reg <= REG_NUMBER)
	{
		while (i < size)
		{
			(pros->reg[reg][i]) = (val >> ((8 * (3 - i))) & 0xFF);
			i++;
		}
	}
	pros->pc = pc;
	pros->ins = ins;
}
