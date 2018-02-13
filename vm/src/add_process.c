/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 02:58:10 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/12 03:15:27 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_process	*init_new_process(t_process *new, int nb)
{
	new->val[1] = (unsigned int)nb;
	new->reg[1][0] = 255;
	new->reg[1][1] = 255;
	new->reg[1][2] = 255;
	new->reg[1][3] = 255 - nb + 1;
	new->pc = NULL;
	new->ins = NULL;
	new->carry = 0;
	new->live = 0;
	new->last_live[0] = 0;
	new->last_live[1] = 0;
	new->start_cycle = -1;
	new->number = nb;
	new->champ = nb;
	new->seek = 0;
	new->line = -1;
	return (new);
}

t_process	*new_process(int nb)
{
	int			i;
	int			j;
	t_process	*new;

	i = 0;
	if (!(new = (t_process *)malloc(sizeof(t_process))))
		return (NULL);
	while (i < REG_NUMBER)
	{
		j = 0;
		while (j < REG_SIZE)
		{
			new->reg[i][j] = 0;
			j++;
		}
		i++;
		new->val[i] = 0;
	}
	new = init_new_process(new, nb);
	return (new);
}

t_process	*add_new_process(t_process *srt, int nb)
{
	int			i;
	t_process	*new;
	t_process	*begin;

	new = new_process(nb);
	begin = srt;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		new->live_champ[i] = 0;
		i++;
	}
	new->next = NULL;
	new->pre = NULL;
	if (!srt)
		return (new);
	while (srt->next != NULL)
		srt = srt->next;
	srt->next = new;
	new->pre = srt;
	return (begin);
}
