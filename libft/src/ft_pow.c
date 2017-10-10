/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 22:57:36 by cobecque          #+#    #+#             */
/*   Updated: 2017/07/09 18:58:39 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_pow(double x, double y)
{
	double		i;
	double		tmp;

	i = 2;
	tmp = x;
	if (y == 0)
		return (1);
	if (y == 1)
		return (x);
	while (i <= y)
	{
		tmp = tmp * x;
		i++;
	}
	return (tmp);
}
