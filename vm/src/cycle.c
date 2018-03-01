/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 09:46:38 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/01 15:42:45 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_cycle			init_cycle(void)
{
	t_cycle		cy;

	cy.i = 0;
	cy.val = 0;
	cy.die = 0;
	cy.win = 0;
	cy.yolo = 0;
	cy.check = 0;
	cy.cycle_d = 0;
	return (cy);
}

t_process		*cycle_to_die(t_process *pro, t_cycle *cy, t_vm *vm)
{
	cy->cycle_d = 0;
	cy->die = count_live(pro);
	cy->yolo = winner(pro);
	if (cy->yolo != -1)
		cy->win = cy->yolo;
	pro = kill_them_all(pro, *vm, vm->cycle, vm->ctd);
	if (cy->die >= NBR_LIVE || cy->check == 10)
	{
		cy->check = 0;
		vm->ctd -= CYCLE_DELTA;
		if (vm->arg.ver_num.cy == 1)
			ft_printf("Cycle to die is now %d\n", vm->ctd);
	}
	else
		cy->check++;
	return (pro);
}

int				count_alive(t_process *pro)
{
	int			i;
	t_process	*tmp;

	i = 0;
	tmp = pro;
	while (tmp != NULL)
	{
		if (tmp->live != -1)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void			ft_is_dump(t_vm virtual)
{
	if (virtual.arg.dump != 0 && virtual.cycle == virtual.arg.dump)
	{
		dump(virtual.addr);
		exit(-1);
	}
}

int				cycle_gestion(t_vm virtual, t_process *pro, t_cycle cy)
{
	while (42)
	{
		cy.i = 0;
		if (cy.cycle_d == virtual.ctd)
		{
			pro = cycle_to_die(pro, &cy, &virtual);
			if (count_alive(pro) == 0)
				break ;
		}
		pro = gestion_process(pro, virtual.cycle, &virtual);
		if (virtual.arg.sdl == 1)
			virtual = ft_ncurses(pro, virtual);
		if (virtual.ctd < 0)
		{
			cy.yolo = winner(pro);
			if (cy.yolo != -1)
				cy.win = cy.yolo;
			pro = kill_them_all(pro, virtual, virtual.cycle, virtual.ctd);
			break ;
		}
		ft_is_dump(virtual);
		if (virtual.cycle == virtual.arg.end)
			return (cy.win);
		virtual.cycle++;
		cy.cycle_d++;
	}
	return (cy.win);
}
