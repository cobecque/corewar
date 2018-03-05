/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_relative.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:55:59 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/05 01:49:57 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

char		*if_uper_max(char *adr, t_inf inf)
{
	int		tmp;

	tmp = (int)adr;
	if (tmp >= (int)inf.min_addr + MEM_SIZE)
	{
		while (tmp > (MEM_SIZE + (int)inf.min_addr))
		{
			adr = adr - MEM_SIZE;
			tmp = tmp - MEM_SIZE;
		}
		if (adr < inf.min_addr)
		{
			if (tmp < 0)
				adr = inf.min_addr + (MEM_SIZE - (int)inf.min_addr -
						(int)inf.min_addr + (int)adr);
			else
				adr = inf.min_addr + MEM_SIZE - ((int)inf.min_addr - (int)adr);
		}
	}
	return (adr);
}

char		*get_relative(char *adr, t_inf inf)
{
	int		tmp;

	tmp = (int)adr;
	if (adr < inf.min_addr)
	{
		if (tmp >= 0)
			adr = inf.min_addr + MEM_SIZE - ((int)inf.min_addr -
					((int)adr));
		else
		{
			tmp = (tmp % MEM_SIZE);
			adr = inf.min_addr + (MEM_SIZE - (int)inf.min_addr + tmp);
		}
	}
	else if (adr >= (inf.min_addr + MEM_SIZE))
		adr = if_uper_max(adr, inf);
	return (adr);
}
