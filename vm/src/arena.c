/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 14:14:38 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/06 10:25:46 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int			winner(t_process *pro)
{
	int			winner;
	t_process	*cpy;

	winner = -1;
	cpy = pro;
	while (pro != NULL)
	{
		if (pro->live != 0)
		{
			if (winner != -1 && winner != pro->champ)
			{
				winner = -1;
				break ;
			}
			else
				winner = pro->champ;
		}
		pro = pro->next;
	}
	return (winner);
}

int			check_alive(int nb_champ, t_process *pro)
{
	int		*tab;
	int		nb_chicken;
	int		i;
	int		nb;

	if (!(tab = (int *)malloc(sizeof(int) * nb_champ)))
		return (-1);
	nb = 0;
	i = 0;
	nb_chicken = 0;
	while (pro != NULL)
	{
		if (pro->live != 0 && pro->champ < nb_champ)
			tab[pro->champ] = 1;
		pro = pro->next;
	}
	while (i < nb_champ)
	{
		if (tab[i] >= 0)
		{
			nb_chicken += tab[i];
		}
		i++;
	}
	return (nb_chicken);
}

t_process	*kill_them_all(t_process *pro)
{
	t_process	*tmp;
	t_process	*cpy;

	cpy = pro;
	if (cpy != NULL)
	{
		if (cpy->live == 0)
		{
			tmp = cpy;
			tmp = cpy->next;
		}
		while (cpy->next != NULL)
		{
			if (cpy->next->live == 0)
			{
				tmp = cpy->next;
				tmp->next = tmp->next;
			}
			else
				cpy->next->live = 0;
			cpy = cpy->next;
		}
	}
	return (pro);
}

int			count_pros(t_process *pro)
{
	int			i;

	i = 0;
	while (pro != NULL)
	{
		i++;
		pro = pro->next;
	}
	return (i);
}

t_process	*gestion_process(t_process *pro, int cycle, t_vm vm, int *val)
{
	t_process	*fun;
	t_process	*cpy;
	t_inf		inf;
	int			nb;
	int			line;
	int			i;
	int			bol;
	int			bol2;
	char		*ret;
	int			all_pro;
	unsigned int	a;
	unsigned int	b;
	int			p;

	a = 0;
	bol = 0;
	bol2 = 0;
	vm.error = 1;
	cpy = pro;
	if (cpy == NULL)
		ft_printf("Ohoh\n");
	ret = cpy->pc;
	nb = 0;
	p = 0;
	all_pro = count_pros(pro);
	while (cpy->next != NULL)
		cpy = cpy->next;
	while (cpy != NULL)
	{
	//	ft_putstr("Hello 1\n");
		line = get_line(*(cpy->pc));
		i = 0;
		if (line != -1 && cpy->start_cycle == -1)
			cpy->start_cycle = cycle - 1 + bol;
	//	ft_putstr("Hello 2\n");
		if (line != -1)
		{
			if (line != -1 && cpy->start_cycle + g_op_tab[line].cycle == cycle)
			{
				if (!cpy->pc)
				{
					ft_printf("clapclap\n");
					break ;
				}
				if (line == 11)
					p++;
				cpy->ins = cpy->pc;
				if (line != -1)
				{
					cpy->pc++;
		//			if (line == 2)
		//				ft_printf(C_BLU"cpy->ins = %d && cpy->pros = %d\n"FC_ALL, cpy->ins, cpy->number);
					inf = add_elem(line, *(cpy->pc));
					inf.min_addr = vm.addr;
					if (have_ocp(line) == 0)
						cpy->pc++;
					if (!(inf.val = (int *)malloc(sizeof(int) * 3)))
						return (NULL);
					while (i < g_op_tab[line].nb_arg)
					{
						/*p = 0;
						pos = 1;
						nb = 0;
						inf.val[i] = 0;
						while (p < inf.l[i])
						{
							nb++;
							if (inf.val[i] == 0 && *cpy->pc == 0 && p != 0)
								;
							else
							{
								if (p == 0 && *cpy->pc != -1)
								{
									pos = 1;
									ff = 1;
									inf.val[i] += *cpy->pc * (ft_pow(256, inf.l[i] - nb));
								}
								else if (p == 0 && *cpy->pc == -1)
								{
									pos = 0;
								}
								else if (p != 0)
								{
									if (*cpy->pc < 0 && *cpy->pc > -128 && *cpy->pc != 0 && pos == 1)
										inf.val[i] += (256 + *cpy->pc) * (ft_pow(256, inf.l[i] - nb));
									else if (*cpy-> pc > 0 && *cpy->pc != 0 && pos == 0)
									{
										inf.val[i] += (-256 + *cpy->pc) * (ft_pow(256, inf.l[i] - nb));
										ff = 1;
									}
									else if (*cpy->pc == -1 && ff == 0)
										inf.val[i] += 0;
									else
									{
										inf.val[i] += *cpy->pc * (ft_pow(256, inf.l[i] - nb));
										ff = 1;
									}
								}
							}
							if (line == 0 && p == 0)
								inf.val[i] = 0;
							cpy->pc++;
							p++;
						}*/
						p = 0;
						while (p < inf.l[i])
						{
							if (p == 0)
								a = *cpy->pc;
							else
							{
								b = *cpy->pc << 24;
								a = (a << 8) | (b >> 24);
							}
						/*	if (line == 2 && cycle == 8920)
								ft_printf("cpy->pc = %d et a = %d\n", *cpy->pc, a);
						*/	cpy->pc++;
							p++;
						}
						inf.val[i] = a;
			//			if (line == 2 && cycle == 8915)
			//				ft_printf("inf.val = %d\n", inf.val[i]);
						i++;
					}
				}
				else
					cpy->pc++;
			//	if (cpy->next == NULL)
				if (line == 10)
					(*val)++;
				if (line <= 17 && line >= 0)
				{
				//	if (cycle >= 3365 && cycle <= 3500)
				//	if (cpy->number == 1)
				//		ft_printf("Process %d cycle %d et %s\n", cpy->number, cycle, g_op_tab[line].name);
			//		if (line == 2)
			//			ft_printf("cycle = %d\t", cycle);
					/*	if (cpy->number != 74)
							;
						else
							g_instructab[line](inf, cpy);
					}
					else*/
							g_instructab[line](inf, cpy);
			//		cycle--;
				}
	//			ft_printf("\n");
				if (count_pros(pro) > all_pro)
					bol = 1;
				else
					bol = 0;
				//ft_printf("Process = %d et Cycle = %d et nb = %d\n", cpy->number, cycle, count_pros(pro));
				cpy->start_cycle = -1;
				if (cpy->pc + 1 > inf.min_addr + MEM_SIZE)
					cpy->pc = inf.min_addr;
			}
		}
		/*if (bol == 1)
			break ;*/
		cpy = cpy->pre;
	}
	if (line != -1)
	{
		i = 0;
		fun = pro;
		while (fun != NULL)
		{
			i++;
			fun = fun->next;
		}
	}
	return (pro);
}

int			count_live(t_process *pro)
{
	int		nb;

	nb = 0;
	while (pro != NULL)
	{
		nb += pro->live;
		pro = pro->next;
	}
	return (nb);
}

char		*get_hexa(int val)
{
	char	*str;

	if (val == 0)
		return ("00");
	str = (char *)malloc(sizeof(char) * 3);
	str[2] = '\0';
	if (val < 0)
	{
		val = 256 + val;
	}
	if (val % 16 >= 10)
		str[1] = val % 16 + 'a' - 10;
	if (val % 16 < 10)
		str[1] = val % 16 + '0';
	if (val / 16 >= 10)
		str[0] = val / 16 + 'a' - 10;
	if (val / 16 < 10)
		str[0] = val / 16 + '0';
	return (str);
}

void		dump(char *ptr)
{
	int		i;
	int		p;

	i = 0;
	p = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0 && i != 0)
			ft_putchar('\n');
		if (i % 64 == 0)
		{
			ft_putstr("0x0");
			if (p < 16)
				ft_putchar('0');
			ft_printf("%x0 : ", p);
			p += 4;
		}
//		if (i == 392 - 256)
//			ft_printf(C_RED"%s "FC_ALL, get_hexa(ptr[i]));
//		else
			ft_printf("%s ", get_hexa(ptr[i]));
		i++;
	}
	ft_putchar('\n');
}

int			cycle_gestion(t_vm virtual, t_process *pro, int ctd)
{
	int		val;
	int		check;
	int		cycle;
	int		cycle_d;

	check = 0;
	cycle = 0;
	cycle_d = 0;
//	dump(virtual.addr);
//	ft_putchar('\n');
//	dump(virtual.addr);
		val = 0;
	while (42)
	{
		if (cycle >= 1)
		{
		//	ft_printf("TRUC\n");
			pro = gestion_process(pro, cycle, virtual, &val);
		}
		if (cycle_d == ctd)
		{
			if (check_alive(virtual.nb_pros, pro) <= 1)
			{
				break ;
			}
			cycle_d = 0;
			if (count_live(pro) >= NBR_LIVE || check == 10)
			{
				check = 0;
				ctd -= CYCLE_DELTA;
				if (ctd < 0)
					break ;
			}
			else
				check++;
			pro = kill_them_all(pro);
		}
		if (cycle > 8930)
			break ;
		
		//	{
			cycle++;
			cycle_d++;
	//	}
	}
//	ft_printf("cycle = %d\n", cycle);
//	ft_printf("\n");
	dump(virtual.addr);
	return (winner(pro));
}
