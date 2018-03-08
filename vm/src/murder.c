/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   murder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 08:44:01 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/08 15:23:27 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_process	*re_init_live(t_process *pro, t_vm *vm)
{
	t_process	*cpy;
	int			i;

	i = 0;
	cpy = pro;
	while (i < vm->nb_pros)
	{
		vm->inf_v.nb_live[i] = 0;
		i++;
	}
	while (cpy != NULL)
	{
		cpy->live = 0;
		cpy = cpy->next;
	}
	return (pro);
}

t_process	*kill_dat_process(t_process *pro, t_vm *vm)
{
	t_process	*tmp;
	t_process	*k;

	k = pro;
	if (pro->next == NULL && pro->pre == NULL)
	{
		vm->start_l = NULL;
		tmp = NULL;
	}
	else if (pro->next != NULL)
	{
		tmp = pro->next;
		tmp->pre = pro->pre;
		if (pro->pre != NULL)
			pro->pre->next = tmp;
		else
			vm->start_l = tmp;
	}
	else
	{
		tmp = pro->pre;
		tmp->next = NULL;
	}
	free(k);
	return (tmp);
}

int			final_murder(t_vm *vm, int cycle, int ctd)
{
	t_process	*tmp;
	int			bol;

	bol = 0;
	tmp = vm->end_l;
	while (tmp != NULL)
	{
		if (vm->arg.ver_num.de == 1)
			ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				tmp->number, cycle - tmp->last_live[0] + 1,
				ctd);
		if (tmp->next == NULL)
		{
			vm->end_l = tmp->pre;
			bol = 1;
		}
		tmp = kill_dat_process(tmp, vm);
		if (bol == 0 && vm->start_l != NULL)
			tmp = tmp->pre;
	}
	return (-1);
}

t_process	*more_kills(t_process *cpy, t_vm *vm, int *bol)
{
	if (cpy->next == NULL)
	{
		vm->end_l = cpy->pre;
		*bol = 1;
	}
	vm->alive--;
	cpy = kill_dat_process(cpy, vm);
	return (cpy);
}

t_process	*kill_them_all(t_process *pro, t_vm *vm, int cycle, int ctd)
{
	t_process	*cpy;
	int			bol;
	int			truc;

	truc = 0;
	cpy = vm->end_l;
	while (cpy != NULL)
	{
		bol = 0;
		if (ctd < 0)
		{
			final_murder(vm, cycle, ctd);
			break ;
		}
		else if ((cycle - cpy->last_live[0] - ctd >= 0))
		{
			truc = 1;
			print_dead(vm, cpy, ctd, cycle);
			cpy = more_kills(cpy, vm, &bol);
		}
		if (bol == 0)
			cpy = cpy->pre;
	}
	pro = sound_and_reset(pro, vm, truc);
	return (pro);
}
