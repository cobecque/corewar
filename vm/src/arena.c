/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 14:14:38 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/12 12:19:31 by rostroh          ###   ########.fr       */
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
	t_process	*yolo;

	cpy = pro;
	/*if (cpy != NULL)
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
	}*/
	yolo = NULL;
	while (cpy != NULL)
	{
		if (cpy->live == 0)
		{
			ft_printf("cpy->number %d\n", cpy->number);
			if (cpy->number == 12)
				ft_printf("kill the process %d\n", cpy->number);
			tmp = cpy->next;
			tmp->pre = cpy->pre;
		//	yolo = cpy;
		//	yolo->next = NULL;
		//	yolo->pre = NULL;
		//	free(yolo);
			cpy = tmp;
		}
		else
			cpy = cpy->next;
		if (cpy != NULL)
			yolo = cpy;
	}
	cpy = yolo;
	while (cpy != NULL)
	{
		cpy->live = 0;
//		ft_printf("pros = %d\n", cpy->number);
		cpy = cpy->pre;
	}
	return (pro);
}

int			count_pros(t_process *pro)
{
	t_process	*tmp;
	int			i;

	i = 0;
	tmp = pro;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_process	*gestion_process(t_process *pro, int cycle, t_vm vm, int *val)
{
	t_process	*cpy;
	t_inf		inf;
	int			nb;
	int			i;
	int			bol;
	int			bol2;
	char		*ret;
	unsigned int	a;
	unsigned int	b;
	int			p;

	*val = 0;
	a = 0;
	bol = 0;
	bol2 = 0;
	vm.error = 1;
	cpy = pro;
	inf.min_addr = vm.addr;
	ret = cpy->pc;
	nb = 0;
	p = 0;
	if (vm.arg.ver == 14)
		ft_printf("Au cycle %d\n", cycle);
	while (cpy->next != NULL)
		cpy = cpy->next;
	while (cpy != NULL)
	{
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
		if (cpy->line != -1 && cpy->start_cycle != -1)//&& cpy->start_cycle + g_op_tab[line].cycle == cycle)
		{
			if (cpy->seek == 1)
			{
				if (!cpy->pc)
					break ;
				if (cpy->line == 11)
					p++;
				cpy->ins = cpy->pc;
				cpy->pc++;
				cpy->inf = add_elem(cpy->line, *(cpy->pc));
				cpy->inf.min_addr = vm.addr;
				if (have_ocp(cpy->line) == 0)
					cpy->pc++;
				if (!(cpy->inf.val = (int *)malloc(sizeof(int) * 3)))
					return (NULL);
				while (i < g_op_tab[cpy->line].nb_arg)
				{
					p = 0;
					while (p < cpy->inf.l[i])
					{
						if (p == 0)
							a = *cpy->pc;
						else
						{
							b = *cpy->pc << 24;
							a = (a << 8) | (b >> 24);
						}
						cpy->pc++;
						p++;
					}
					cpy->inf.val[i] = a;
					if (cpy->line == 0)
						ft_printf("cpy->pc %d et a %d et process %d\n", *cpy->pc, a, cpy->number);
					i++;
				}
				cpy->seek = 2;
			}
	//		ft_printf("line2 ==== %d\n", line);
			if (cpy->start_cycle + g_op_tab[cpy->line].cycle == cycle && cpy->line <= 17 && cpy->line >= 0)
			{
				g_instructab[cpy->line](cpy->inf, cpy, vm.arg);
				cpy->start_cycle = -1;
				cpy->seek = 0;
			}
		}
		else if (cpy->line == -1)
			cpy->pc++;
		if (cpy->pc >= inf.min_addr + MEM_SIZE)
			cpy->pc = inf.min_addr;
		cpy = cpy->pre;
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
//		if (i == 4096 - 119)
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
	//	if (cycle >= 1)
	//	{
	//		//	ft_printf("TRUC\n");
			pro = gestion_process(pro, cycle, virtual, &val);
	//	}
		if (cycle_d == ctd)
		{
			if (check_alive(virtual.nb_pros, pro) <= 1)
			{
			//	break ;
			}
			cycle_d = 0;
			if (count_live(pro) >= NBR_LIVE || check == 10)
			{
				check = 0;
				ctd -= CYCLE_DELTA;
				ft_printf("Cycle to die = %d\n", ctd);
				if (ctd < 0)
					break ;
			}
			else
				check++;
			pro = kill_them_all(pro);
		}
		if (cycle > 22000)
		{
			break ;
		}
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
