/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 08:00:17 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/14 09:21:15 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_process	*gestion_process(t_process *pro, int cycle, t_vm vm)
{
	t_process		*cpy;
	t_inf			inf;
	int				nb;
	int				i;
	int				bol;
	int				bol2;
	char			*ret;
	unsigned int	a;
	unsigned int	b;
	int				p;
	int				adv;
	int				ocp;
	int				yolo;
	int				len;

	len = 0;
	a = 0;
	bol = 0;
	bol2 = 0;
	vm.error = 1;
	cpy = pro;
	inf.min_addr = vm.addr;
	ret = cpy->pc;
	nb = 0;
	p = 0;
	ocp = 0;
	adv = 0;
	if (vm.arg.ver_num.cy == 1)
		ft_printf("It is now cycle %d\n", cycle);
	while (cpy->next != NULL)
		cpy = cpy->next;
	while (cpy != NULL)
	{
		if (cpy->live != -1)
		{
			inf.min_addr = vm.addr;
			if (cpy->pc >= (inf.min_addr + MEM_SIZE))
				cpy->pc = inf.min_addr;
			if (cpy->pc < inf.min_addr)
			{
				if (cpy->pc < 0)
					cpy->pc = (char *)((long)cpy->pc + (inf.min_addr +
								MEM_SIZE));
				else
					cpy->pc = (char *)((inf.min_addr + MEM_SIZE) -
							(long)cpy->pc);
			}
			if (cpy->seek == 0)
				cpy->line = get_line(*(cpy->pc));
			i = 0;
			if (cpy->line != -1 && cpy->start_cycle == -1)
			{
				cpy->seek = 1;
				if (cycle != 0)
					cpy->start_cycle = cycle - 1;
				else
					cpy->start_cycle = cycle;
			}
			if (cpy->start_cycle + g_op_tab[cpy->line].cycle == cycle &&
					cpy->line <= 17 && cpy->line >= 0)
			{
				if (cpy->seek == 1)
				{
					yolo = 0;
					adv = 0;
					bol = 0;
					ocp = 0;
					nb = 0;
					if (!cpy->pc)
						break ;
					cpy->ins = cpy->pc;
					cpy->pc++;
					if (cpy->pc >= inf.min_addr + MEM_SIZE)
						cpy->pc = inf.min_addr;
					cpy->inf = add_elem(cpy->line, *(cpy->pc));
					cpy->inf.min_addr = vm.addr;
					if (have_ocp(cpy->line) == 0)
					{
						nb = 1;
						ocp = *(cpy->pc);
						bol2 = cpy->line;
						if (ocp_valid(bol2, ocp) == 0)
							bol = -1;
						cpy->pc++;
						if (cpy->pc >= inf.min_addr + MEM_SIZE)
							cpy->pc = inf.min_addr;
						if (bol == -1)
						{
							adv = adv_value(cpy->line, ocp);
							if (vm.arg.ver_num.pc == 1)
								ft_printf("ADV %d (0x%.4x -> 0x%.4x) %s %s",
										adv + 2, cpy->ins - cpy->inf.min_addr,
										cpy->ins - cpy->inf.min_addr + adv + 2,
										get_hexa(*cpy->ins), get_hexa(ocp));
							yolo = 0;
							while (yolo < adv)
							{
								if (vm.arg.ver_num.pc == 1)
									ft_printf(" %s", get_hexa(*cpy->pc));
								cpy->pc++;
								if (cpy->pc == inf.min_addr + MEM_SIZE)
									cpy->pc = inf.min_addr;
								yolo++;
							}
							if (vm.arg.ver_num.pc == 1)
								ft_printf(" \n");
							cpy->line = -1;
						}
					}
					if (bol == 0)
					{
						if (!(cpy->inf.val = (int *)malloc(sizeof(int) * 3)))
							return (NULL);
						i = 0;
						len = 0;
						adv = 0;
						yolo = 0;
						bol2 = 0;
						while (i < g_op_tab[cpy->line].nb_arg)
						{
							p = 0;
							a = 0;
							adv += cpy->inf.l[i];
							while (p < cpy->inf.l[i])
							{
								if ((cpy->pc + len) >= inf.min_addr + MEM_SIZE)
								{
									yolo = len;
									len = 0;
									cpy->pc = inf.min_addr;
								}
								if (p == 0)
									a = *(cpy->pc + len);
								else
								{
									b = *(cpy->pc + len) << 24;
									a = (a << 8) | (b >> 24);
								}
								if ((cpy->pc + len) >= inf.min_addr + MEM_SIZE)
								{
									yolo = len;
									len = 0;
									cpy->pc = inf.min_addr;
								}
								p++;
								len++;
							}
							cpy->inf.val[i] = a;
							i++;
						}
						cpy->seek = 2;
						if (nb == 1)
						{
							bol2 = 2;
							len = yolo + len + 2;
						}
						else
						{
							bol2 = 1;
							len = yolo + len + 1;
						}
						g_instructab[cpy->line](cpy->inf, cpy, vm);
						cpy->pc = cpy->ins;
						if (vm.arg.ver_num.pc == 1 && (cpy->line != 8 ||
									cpy->carry == 0))
						{
							p = 0;
							if (nb == 1)
								adv += 2;
							else
								adv++;
							i = 0;
							ft_printf("ADV %d (0x%.4x -> 0x%.4x) %s", adv,
									cpy->ins - inf.min_addr, cpy->ins -
									inf.min_addr + adv, get_hexa(*cpy->ins));
							if (nb == 1)
								ft_printf(" %s", get_hexa(*(cpy->ins + 1)));
							nb++;
							while (i < len - bol2)
							{
								if ((cpy->ins + p + nb) >= inf.min_addr +
										MEM_SIZE)
								{
									nb = 0;
									p = 0;
									cpy->ins = inf.min_addr;
								}
								ft_printf(" %s", get_hexa(*(cpy->ins + p +
												nb)));
								p++;
								i++;
								if ((cpy->ins + p) >= inf.min_addr + MEM_SIZE)
								{
									p = 0;
									nb = 0;
									cpy->ins = inf.min_addr;
								}
							}
							if (vm.arg.ver_num.pc == 1)
								ft_printf(" \n");
						}
						i = 0;
						if (cpy->line != 8 || cpy->carry == 0)
						{
							while (i < len)
							{
								if (cpy->pc > inf.min_addr + MEM_SIZE)
									cpy->pc = (inf.min_addr + 1);
								cpy->pc++;
								i++;
							}
							if (cpy->pc > inf.min_addr + MEM_SIZE)
								cpy->pc = inf.min_addr + 1;
						}
					}
					cpy->start_cycle = -1;
					cpy->seek = 0;
				}
			}
			else if (cpy->line == -1)
			{
				if (cpy->pc >= inf.min_addr + MEM_SIZE)
					cpy->pc = inf.min_addr;
				cpy->pc++;
			}
			if (cpy->pc >= inf.min_addr + MEM_SIZE)
				cpy->pc = inf.min_addr;
		}
		cpy = cpy->pre;
	}
	return (pro);
}
