/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:34:49 by rostroh           #+#    #+#             */
/*   Updated: 2017/12/18 07:46:15 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_process	*dup_pros(t_process *src, t_inf inf)
{
	t_process	*new;
	t_process	*tmp;
	int			i;
	int			j;
	int			nb;

	i = 0;
	nb = 0;
	tmp = src;
	if (!(new = (t_process *)malloc(sizeof(t_process))))
		return (NULL);
	while (i < REG_NUMBER)
	{ 
		j = 0;
		while (j < REG_SIZE)
		{
			new->reg[i][j] = src->reg[i][j];
			j++;
		}
		i++;
	}
	while (tmp->next != NULL)
	{
		nb++;
		tmp = tmp->next;
	}
	new->pc = NULL;
	new->carry = src->carry;
	new->live = 1;
	new->start_cycle = -1;
	if (nb == 0 && src->number == 0)
		new->number = 1;//
	else
		new->number = tmp->number + 1;
	new->champ = src->champ;
	new->ins = src->ins + (inf.val[0] % IDX_MOD);
	new->pc = new->ins;
	new->next = NULL;
	tmp->next = new;
	tmp = src;
//	ft_printf("le process numero %d est entrain de fork pour creer le numero %d\n", src->number, new->number);
	return (tmp);
}

void	ft_fork(t_inf inf, t_process *pros)
{
	pros = dup_pros(pros, inf);
}
