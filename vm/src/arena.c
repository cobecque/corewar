/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 14:14:38 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/06 05:02:51 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int			winner(t_process *pro)
{
	int			winner;
	int			last;
	t_process	*cpy;

	winner = -1;
	cpy = pro;
	last = 0;
	while (cpy->next != NULL)
		cpy = cpy->next;
	while (cpy != NULL)
	{
		if (last <= cpy->last_live[0] && cpy->last_live[1] != 0)
		{
			last = cpy->last_live[0];
			winner = cpy->last_live[1];
		}
		cpy = cpy->pre;
	}
	return (winner);
}

int			check_alive(int nb_champ, t_process *pro)
{
	int		*tab;
	int		nb_chicken;
	int		i;

	if (!(tab = (int *)malloc(sizeof(int) * nb_champ)))
		return (-1);
	i = 0;
	nb_chicken = 0;
	while (pro != NULL)
	{
		if (pro->champ < nb_champ)
			tab[pro->champ] = 1;
		pro = pro->next;
	}
	while (i < nb_champ)
	{
		if (tab[i] >= 0)
			nb_chicken += tab[i];
		i++;
	}
	free(tab);
	return (nb_chicken);
}

int			count_live(t_process *pro)
{
	int		nb;

	nb = 0;
	while (pro != NULL)
	{
		if (pro->live != -1)
			nb += pro->live;
		pro = pro->next;
	}
	return (nb);
}
