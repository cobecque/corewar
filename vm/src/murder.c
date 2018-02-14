/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   murder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 08:44:01 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/14 09:09:33 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int			final_murder(t_process *cpy, t_vm vm, int cycle, int ctd)
{
	if (cpy->live != -1)
	{
		if (vm.arg.ver_num.de == 1)
			ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n"
				, cpy->number, cycle - cpy->last_live[0] + 1,
				ctd);
		return (-1);
	}
	return (cpy->live);
}

t_process	*re_init_live(t_process *pro)
{
	t_process	*cpy;

	cpy = pro;
	while (cpy != NULL)
	{
		if (cpy->live != -1)
			cpy->live = 0;
		cpy = cpy->next;
	}
	return (pro);
}

t_process	*kill_them_all(t_process *pro, t_vm vm, int cycle, int ctd)
{
	t_process	*tmp;
	t_process	*cpy;
	t_process	*yolo;

	cpy = pro;
	yolo = NULL;
	tmp = NULL;
	while (cpy->next != NULL)
		cpy = cpy->next;
	while (cpy != NULL)
	{
		if (ctd < 0)
			cpy->live = final_murder(cpy, vm, cycle, ctd);
		else if ((cycle - cpy->last_live[0] - ctd >= 0) && cpy->live != -1)
		{
			if (vm.arg.ver_num.de == 1)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
						cpy->number, cycle - cpy->last_live[0], ctd);
			cpy->live = -1;
		}
		cpy = cpy->pre;
	}
	pro = re_init_live(pro);
	return (pro);
}
