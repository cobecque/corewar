/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 05:40:33 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/12 01:51:02 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int			ocp_valid(int line, int ocp)
{
	if ((line == 1 || line == 12) && (ocp == 144 || ocp == 208 || ocp == -112))
		return (1);
	if (line == 2 && (ocp == 80 || ocp == 112))
		return (1);
	if ((line == 3 || line == 4) && ocp == 84)
		return (1);
	if ((line == 5 || line == 6 || line == 7) && (ocp == 84 || ocp == 148 ||
				ocp == 212 || ocp == 100 || ocp == 116 || ocp == 164 ||
				ocp == 228 || ocp == 244 || ocp == 180))
		return (1);
	if ((line == 9 || line == 13) && (ocp == 84 || ocp == 100 || ocp == 148 ||
				ocp == 212 || ocp == 228 || ocp == 164 || ocp == -108))
		return (1);
	if (line == 10 && (ocp == 84 || ocp == 100 || ocp == 116 || ocp == 120 ||
				ocp == 104 || ocp == 88))
		return (1);
	if (line == 15 && (ocp == 64))
		return (1);
	return (0);
}

int			get_line(int opc)
{
	int		i;

	i = 0;
	if (opc > 17 || opc < 1)
		return (-1);
	while (i < 17)
	{
		if (g_op_tab[i].op_code == opc)
			return (i);
		i++;
	}
	return (-1);
}

int			type_param(int ocp, int pos, int line, int *res)
{
	ocp = (ocp >> (6 - (2 * pos)));
	if ((ocp & 3) == 3)
	{
		*res = 3;
		return (2);
	}
	if ((ocp & 2) == 2)
	{
		if (g_op_tab[line].strange == 0)
		{
			*res = 4;
			return (4);
		}
		else
		{
			*res = 2;
			return (2);
		}
	}
	if ((ocp & 1) == 1)
	{
		*res = 1;
		return (1);
	}
	return (0);
}

int			adv_value(int line, int ocp)
{
	int		i;
	int		res;
	int		val;

	i = 0;
	res = 0;
	val = 0;
	while (i < g_op_tab[line].nb_arg)
	{
		val += type_param(ocp, i, line, &res);
		i++;
	}
	return (val);
}

int			have_ocp(int line)
{
	if (line == 0 || line == 8 || line == 11 || line == 14)
		return (-1);
	return (0);
}
