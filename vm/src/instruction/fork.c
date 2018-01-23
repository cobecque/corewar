/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:34:49 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/23 17:21:10 by cobecque         ###   ########.fr       */
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
	new->last_live[0] = src->start_cycle + 1;
	new->last_live[1] = 0;
	new->line = -1;
	new->seek = 0;
	new->start_cycle = -1;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		new->live_champ[i] = 0;
		i++;
	}
	if (nb == 0 && src->number == 0)
		new->number = 1;//
	else
		new->number = tmp->number + 1;
	new->champ = src->champ;
	if (src->line == 14)
		new->ins = src->ins + inf.val[0];
	else
		new->ins = src->ins + (inf.val[0] % IDX_MOD);
	if (new->ins >= inf.min_addr + MEM_SIZE)
	{
		while (new->ins >= inf.min_addr + MEM_SIZE)
			new->ins -= MEM_SIZE;
	}
	if (new->ins < inf.min_addr)
	{
		if (new->ins >= 0)
			new->ins = (inf.min_addr + MEM_SIZE - 1 - (int)new->ins);
		else
			new->ins = (int)new->ins + (inf.min_addr + MEM_SIZE - 1);
	}
	new->pc = new->ins;
	new->next = NULL;
	tmp->next = new;
	new->pre = tmp;
	tmp = src;
	if (arg.ver_num.op == 1 && src->line == 11)
		ft_printf("P%5d | fork %d (%d)\n", src->number, inf.val[0], src->ins - inf.min_addr + inf.val[0]);
	if (arg.ver_num.op == 1 && src->line == 14)
		ft_printf("P%5d | lfork %d (%d)\n", src->number, inf.val[0], src->ins - inf.min_addr + inf.val[0]);
		//ft_printf("le process %d fork  %d a l'adresse %d\n", src->number, inf.val[0] % IDX_MOD, new->pc);
	return (tmp);
}

void	ft_fork(t_inf inf, t_process *pros, t_pam arg)
{
	pros = dup_pros(pros, inf, arg);
}
