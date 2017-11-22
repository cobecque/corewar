/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:25:54 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/20 19:35:19 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_process	*ft_live(t_process *pro, int nb)
{
	t_process	*srt;

	srt = pro;
	ft_printf("nb = %d\n", nb);
	while (pro != NULL)
	{
		ft_printf("%d\t", pro->number);
		if (pro->number == nb)
		{
			ft_printf("Le champion %d se dit en vie\n", nb);
			pro->live++;
			return (srt);
		}
		pro = pro->next;
	}
	ft_putchar('\n');
	return (srt);
}
