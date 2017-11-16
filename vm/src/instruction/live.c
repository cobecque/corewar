/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:25:54 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/16 14:39:59 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_process	*ft_live(t_process *pro, int nb)
{
	t_process	*srt;

	srt = pro;
	while (pro != NULL)
	{
		if (pro->number == nb)
		{
			pro->live++;
			return (srt);
		}
		pro = pro->next;
	}
	return (srt);
}
