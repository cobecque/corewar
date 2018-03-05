/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   murder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 08:44:01 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/05 03:26:15 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int			final_murder(t_process *cpy, t_vm vm, int cycle, int ctd)
{
	if (vm.arg.ver_num.de == 1)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n"
				, cpy->number, cycle - cpy->last_live[0] + 1,
				ctd);
	return (-1);
}

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
		free(pro);
		return (NULL);
	}
	if (pro->next != NULL)
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

void		print_dead(t_vm *vm, t_process *cpy, int ctd, int cycle)
{
	int		bol;

	bol = 0;
	if (cpy->last_live[0] == 0)
		bol = 1;
	if (vm->arg.ver_num.de == 1)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				cpy->number, cycle - bol - cpy->last_live[0] , ctd);
}

t_process	*kill_them_all(t_process *pro, t_vm *vm, int cycle, int ctd)
{
	t_process	*cpy;
	int			bol;

	cpy = vm->end_l;
	while (cpy != NULL)
	{
		bol = 0;
		if (ctd < 0)
			cpy->live = final_murder(cpy, *vm, cycle, ctd);
		else if ((cycle - cpy->last_live[0] - ctd >= 0))
		{
			print_dead(vm, cpy, ctd, cycle);
			if (cpy->next == NULL)
			{
				vm->end_l = cpy->pre;
				bol = 1;
			}
			vm->alive--;
			cpy = kill_dat_process(cpy, vm);
		}
		if (bol == 0)
			cpy = cpy->pre;
	}
	pro = re_init_live(vm->start_l, vm);
	return (pro);
}
