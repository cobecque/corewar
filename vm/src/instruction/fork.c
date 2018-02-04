/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:34:49 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/04 19:20:14 by cobecque         ###   ########.fr       */
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
	int			bol;
	int			lol;
	char		*adr;

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
	{
		new->last_live[0] = src->last_live[0];
		new->last_live[1] = src->last_live[1];
		new->ins = src->ins + inf.val[0];
		adr = src->ins + inf.val[0];
	}
	else
	{
		adr = src->ins + (inf.val[0] % IDX_MOD);
		new->last_live[0] = src->last_live[0];//src->start_cycle + 1;
		new->last_live[1] = src->last_live[1];
		new->ins = src->ins + (inf.val[0] % IDX_MOD);
	}
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
		//if (src->number == 6152)
		//	ft_printf("Creat %d at %d\n", new->number, new->ins);
	}
	new->pc = new->ins;
	new->next = NULL;
	tmp->next = new;
	new->pre = tmp;
	tmp = src;
	lol = (int)adr;
	if (adr < inf.min_addr)
	{
		if ((int)adr > 0)
			adr = inf.min_addr + MEM_SIZE - ((int)inf.min_addr - ((int)adr % MEM_SIZE));
		else
			adr = inf.min_addr + MEM_SIZE + (int)adr % MEM_SIZE;
	}
	else if (adr >= (inf.min_addr + MEM_SIZE))
	{
		bol = (int)adr;
		if (bol >= (int)inf.min_addr + MEM_SIZE)
		{
			while (bol > (MEM_SIZE + (int)inf.min_addr))
			{
				adr = adr - MEM_SIZE;
				bol = bol - MEM_SIZE;
			}
			if (adr < inf.min_addr)
			{
				if (adr < 0)
				{
					adr = (int)inf.min_addr + MEM_SIZE + adr;
				}
				else
					adr = (inf.min_addr + MEM_SIZE) - (int)adr;
			}
		}
	}
	if ((lol > 4456 || lol < 0) && src->line != 14)
		lol = (int)adr;
	if (arg.ver_num.op == 1 && src->line == 11)
		ft_printf("P%5d | fork %d (%d)\n", src->number, inf.val[0], lol - 256);//src->ins - inf.min_addr + inf.val[0]);
	if (arg.ver_num.op == 1 && src->line == 14)
		ft_printf("P%5d | lfork %d (%d)\n", src->number, inf.val[0], lol - 256);//src->ins - inf.min_addr + inf.val[0]);
	return (tmp);
}

void	ft_fork(t_inf inf, t_process *pros, t_pam arg)
{
	pros = dup_pros(pros, inf, arg);
}
