/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:34:49 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/16 13:57:56 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_process	*dup_pros(t_process *src, t_inf inf, t_pam arg)
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
	new->line = -1;
	new->seek = 0;
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
	new->pre = tmp;
	tmp = src;
	if (arg.ver == 14)
		ft_printf("le process %d fork  %d a l'adresse %d\n", src->number, inf.val[0] % IDX_MOD, new->pc);
	return (tmp);
}

void	ft_fork(t_inf inf, t_process *pros, t_pam arg)
{
	pros = dup_pros(pros, inf, arg);
}
