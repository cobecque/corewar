/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_reg_val.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 18:52:51 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/03 02:08:49 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int			catch_reg_val(int nb, t_inf inf, t_process *pros)
{
	int			i;
	int			ret;

	i = 0;
	if (inf.typ[nb] == 1)
	{
		while (i < 4)
		{
			ret = (ret << 8) | (pros->reg[inf.val[nb]][i]);
			i++;
		}
	}
	else
		ret = inf.val[nb];
	return (ret);
}
