/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 08:00:17 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/06 00:32:01 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_process	*find_val(t_process *cpy, int *adv, int *len)
{
	unsigned int	a;
	int				yolo;
	int				p;
	int				i;

	yolo = 0;
	i = 0;
	while (i < g_op_tab[cpy->line].nb_arg)
	{
		p = 0;
		a = 0;
		(*adv) = (*adv) + cpy->inf.l[i];
		while (p < cpy->inf.l[i])
		{
			if ((cpy->pc + yolo) >= cpy->inf.min_addr + MEM_SIZE)
				(*len) = yolo;
			cpy = calcul_val(cpy, &yolo, &a, &p);
			p++;
			yolo++;
		}
		cpy->inf.val[i] = a;
		i++;
	}
	(*len) = (*len) + yolo;
	return (cpy);
}

t_process	*calcul_val(t_process *cpy, int *yolo, unsigned int *a, int *p)
{
	if ((cpy->pc + (*yolo)) >= cpy->inf.min_addr + MEM_SIZE)
	{
		*yolo = 0;
		cpy->pc = cpy->inf.min_addr;
	}
	if (*p == 0)
		*a = *(cpy->pc + (*yolo));
	else
		*a = ((*a) << 8) | (*(cpy->pc + (*yolo)) & 0xFF);
	return (cpy);
}

t_process	*start_gestion(t_process *cpy, t_vm vm, int cycle)
{
	cpy->inf.min_addr = vm.addr;
	if (cpy->pc >= (cpy->inf.min_addr + MEM_SIZE))
		cpy->pc = cpy->inf.min_addr;
	if (cpy->pc < cpy->inf.min_addr)
	{
		if ((int)cpy->pc < 0)
			cpy->pc = cpy->pc + (cpy->inf.min_addr +
					MEM_SIZE - cpy->inf.min_addr);
		else
			cpy->pc = (char *)((cpy->inf.min_addr + MEM_SIZE) -
					(long)cpy->pc);
	}
	if (cpy->seek == 0)
		cpy->line = get_line(*(cpy->pc));
	if (cpy->line != -1 && cpy->start_cycle == -1)
	{
		cpy->seek = 1;
		if (cycle != 0)
			cpy->start_cycle = cycle - 1;
		else
			cpy->start_cycle = cycle;
	}
	return (cpy);
}

t_process	*init_inf(t_process *cpy, t_vm vm, int *nb, int *bol)
{
	*nb = 0;
	*bol = 0;
	cpy->ocp = 0;
	cpy->ins = cpy->pc;
	cpy->pc++;
	if (cpy->pc >= cpy->inf.min_addr + MEM_SIZE)
		cpy->pc = cpy->inf.min_addr;
	cpy->inf = add_elem(cpy->line, *(cpy->pc));
	cpy->inf.min_addr = vm.addr;
	return (cpy);
}

t_process	*gestion_process(t_process *pro, int cycle, t_vm *vm)
{
	t_process		*cpy;
	t_var			var;

	cpy = reverse_list(vm->arg.ver_num.cy, cycle, vm);
	while (cpy != NULL)
	{
		cpy = start_gestion(cpy, *vm, cycle);
		cpy = get_adr(cpy);
		if (cpy->start_cycle + g_op_tab[cpy->line].cycle == cycle &&
				cpy->line <= 17 && cpy->line >= 0 && cpy->seek == 1)
		{
			if (!cpy->pc)
				break ;
			cpy = if_must_be_call(cpy, &var, vm);
		}
		cpy = cpy->pre;
	}
	return (pro);
}
