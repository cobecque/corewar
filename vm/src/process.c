/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 08:00:17 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/21 14:00:14 by cobecque         ###   ########.fr       */
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
		*a = ((*a) << 8) | ((unsigned int)(*(cpy->pc + (*yolo)) << 24) >> 24);
	return (cpy);
}

t_process	*start_gestion(t_process *cpy, t_vm vm, int cycle)
{
	cpy->inf.min_addr = vm.addr;
	if (cpy->pc >= (cpy->inf.min_addr + MEM_SIZE))
		cpy->pc = cpy->inf.min_addr;
	if (cpy->pc < cpy->inf.min_addr)
	{
		if (cpy->pc < 0)
			cpy->pc = (char *)((long)cpy->pc + (cpy->inf.min_addr +
						MEM_SIZE));
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

t_process	*gestion_process(t_process *pro, int cycle, t_vm vm)
{
	t_process		*cpy;
	int				nb;
	int				bol;
	int				adv;
	int				len;

	cpy = pro;
	if (vm.arg.ver_num.cy == 1)
		ft_printf("It is now cycle %d\n", cycle);
	while (cpy->next != NULL)
		cpy = cpy->next;
	while (cpy != NULL)
	{
		if (cpy->live != -1)
		{
			cpy = start_gestion(cpy, vm, cycle);
			if (cpy->start_cycle + g_op_tab[cpy->line].cycle == cycle &&
					cpy->line <= 17 && cpy->line >= 0)
			{
				if (cpy->seek == 1)
				{
					if (!cpy->pc)
						break ;
					cpy = init_inf(cpy, vm, &nb, &bol);
					if (have_ocp(cpy->line) == 0)
					{
						nb = 1;//norme
						cpy->ocp = *(cpy->pc);
						if (ocp_valid(cpy->line, cpy->ocp) == 0)
							bol = -1;
						cpy->pc++;
						if (cpy->pc >= cpy->inf.min_addr + MEM_SIZE)
							cpy->pc = cpy->inf.min_addr;//fin norme
						if (vm.arg.ver_num.pc == 1 && bol == -1)
							bol = -2;
						cpy = ocp_invalid(cpy, &bol, &len);
					}
					if (bol == 0)
					{
						if (!(cpy->inf.val = (int *)malloc(sizeof(int) * 3)))//norme
							return (NULL);
						len = 0;
						adv = 0;
						bol = 1;
						find_val(cpy, &adv, &len);
						cpy->seek = 2;
						if (nb == 1)
						{
							bol = 2;
							len += 2;
						}
						else
							len += 1;//fin norme
						g_instructab[cpy->line](cpy->inf, cpy, vm);
						cpy->pc = cpy->ins;
						if (vm.arg.ver_num.pc == 1 && (cpy->line != 8 ||
									cpy->carry == 0))
						{//norme
							adv++;
							if (nb == 1)
								adv++;
							ft_printf("ADV %d (0x%.4x -> 0x%.4x) %s", adv,
									cpy->ins - cpy->inf.min_addr, cpy->ins -
									cpy->inf.min_addr + adv,
									get_hexa(*cpy->ins));
							if (nb == 1)
								ft_printf(" %s", get_hexa(*(cpy->ins + 1)));
							nb++;
							cpy = adv_printf(cpy, len - bol, nb);
							if (vm.arg.ver_num.pc == 1)
								ft_printf(" \n");
						}//fin norme
						cpy = move_pc(cpy, len);
						free(cpy->inf.val);
					}
					cpy->start_cycle = -1;
					cpy->seek = 0;
				}
			}
			else if (cpy->line == -1)//norme
			{
				if (cpy->pc >= cpy->inf.min_addr + MEM_SIZE)
					cpy->pc = cpy->inf.min_addr;
				cpy->pc++;
			}
			if (cpy->pc >= cpy->inf.min_addr + MEM_SIZE)
				cpy->pc = cpy->inf.min_addr;//fin norme
		}
		cpy = cpy->pre;
	}
	return (pro);
}
