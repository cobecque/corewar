/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:34:49 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/02 23:32:08 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_process	*init_new(t_process *new, t_process *src)
{
	int			i;
	int			j;

	i = 0;
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
	new->last_live[0] = src->last_live[0];
	new->last_live[1] = src->last_live[1];
	new->next = NULL;
	new->pc = NULL;
	new->carry = src->carry;
	new->live = 1;
	new->line = -1;
	new->seek = 0;
	new->start_cycle = -1;
	new->champ = src->champ;
	return (new);
}

t_process	*keep_in(t_process *new)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		new->live_champ[i] = 0;
		i++;
	}
	return (new);
}

t_process	*fork_lf(t_process *new, t_process *src, t_inf inf, char **adr)
{
	if (src->line == 14)
	{
		new->ins = src->ins + inf.val[0];
		*adr = src->ins + inf.val[0];
	}
	else
	{
		*adr = src->ins + (inf.val[0] % IDX_MOD);
		new->ins = *adr;
	}
	return (new);
}

static void	s_print(char *adr, t_vm *vm, t_inf inf, t_process *src)
{
	int		lol;

	lol = (int)adr;
	adr = get_relative(adr, inf);
	if ((lol > 4456 || lol < 0) && src->line != 14)
		lol = (int)adr;
	if (vm->arg.ver_num.op == 1 && src->line == 11)
		ft_printf("P%5d | fork %d (%d)\n", src->number, inf.val[0], lol - 256);
	if (vm->arg.ver_num.op == 1 && src->line == 14)
		ft_printf("P%5d | lfork %d (%d)\n", src->number, inf.val[0], lol - 256);
}

t_process	*dup_pros(t_process *src, t_inf inf, t_vm *vm)
{
	t_process	*new;
	t_process	*tmp;
	int			nb;
	char		*adr;

	nb = 0;
	tmp = src;
	while (tmp->next != NULL)
	{
		nb++;
		tmp = tmp->next;
	}
	if (!(new = (t_process *)malloc(sizeof(t_process))))
		return (NULL);
	new = init_new(new, src);
	new = keep_in(new);
	new = fork_lf(new, src, inf, &adr);
	new->ins = get_relative(new->ins, inf);
	new->pc = new->ins;
	tmp->next = new;
	new->number = vm->number + 1;
	vm->number++;
	new->pre = tmp;
	tmp = src;
	s_print(adr, vm, inf, src);
	return (tmp);
}
