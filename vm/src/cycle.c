/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 09:46:38 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/24 17:48:19 by rostroh          ###   ########.fr       */
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
	int			i;
	int			j;

	while (42)
	{
		cy.i = 0;
		if (cy.cycle_d == virtual.ctd)
		{
			pro = cycle_to_die(pro, &cy, &virtual);
			if (count_alive(pro) == 0)
				break ;
		}
		pro = gestion_process(pro, virtual.cycle, virtual);
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
	i = 0;
	j = 0;
	ft_printf("         ");
	while (i < 64)
	{
		if (i < 10)
			ft_putchar('0');
		ft_printf("%d ", i);
		i++;
	}
	ft_putstr("\n\n");//
	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0 && i != 0)
			ft_putchar('\n');
		if (i % 64 == 0)
		{
			ft_putstr("0x0");
			if (j < 16)
				ft_putchar('0');
			ft_printf("%x0 : ", j);
			j += 4;
		}
		ft_printf("0%d ", virtual.color[i]);
		i++;
	}
	ft_putstr("\n\n");
	return (cy.win);
}
