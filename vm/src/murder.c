/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   murder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 08:44:01 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/02 23:40:43 by cobecque         ###   ########.fr       */
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

t_process	*re_init_live(t_process *pro)
{
	t_process	*cpy;

	cpy = pro;
	while (cpy != NULL)
	{
		cpy->live = 0;
		cpy = cpy->next;
	}
	return (pro);
}

t_process	*kill_dat_process(t_process *pro)
{
	t_process	*tmp;
	t_process	*k;

	k = pro;
	if (pro->next != NULL)
	{
		tmp = pro->next;
		tmp->pre = pro->pre;
		pro->pre->next = tmp;
	//	if (pro->next != NULL)
	//		tmp->next = pro->next->next;
	}
	else
	{
		tmp = pro->pre;
		tmp->next = NULL;
	//	tmp->pre = pro->pre->pre;
	}
	free(k);
	return (tmp);
}

t_process	*kill_them_all(t_process *pro, t_vm vm, int cycle, int ctd)
{
	t_process	*cpy;
	int			bol;

	cpy = pro;
	while (cpy->next != NULL)
		cpy = cpy->next;
	while (cpy != NULL)
	{
		bol = 0;
		if (ctd < 0)
			cpy->live = final_murder(cpy, vm, cycle, ctd);
		else if ((cycle - cpy->last_live[0] - ctd >= 0))
		{
			if (vm.arg.ver_num.de == 1)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
						cpy->number, cycle - cpy->last_live[0], ctd);
			if (cpy->next == NULL)
				bol = 1;
			cpy = kill_dat_process(cpy);
		}
		if (bol == 0)
			cpy = cpy->pre;
		/*
		if (cpy != NULL)
		{
			if (bol == 1 && cpy->next == NULL)
				bol = 0;
			else if (cpy->next == NULL && bol != 1)
				bol = 1;
			if (cpy->next != NULL)
				bol = 0;
			if (bol == 0)
				cpy = cpy->pre;
		}*/
	}
	pro = re_init_live(pro);
	return (pro);
}
