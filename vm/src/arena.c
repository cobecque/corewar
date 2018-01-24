/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 14:14:38 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/24 23:27:39 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

//BECARE if last live < kill_them_all --> no Process
int			winner(t_process *pro)
{
	int			winner;
	int			last;
	t_process	*cpy;

	winner = -1;
	cpy = pro;
	last = 0;
	while (pro != NULL)
	{
		if (pro->live != -1)
		{
			if (last <= pro->last_live[0])
			{
				winner = pro->last_live[1];
				//ft_printf("LE DEMON: %d\n", winner);
			}
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
		if (pro->live != -1 && pro->champ < nb_champ)
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
		{
			if (cpy->live != -1)
			{
				if (vm.arg.ver_num.de == 1)
					ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", cpy->number, cycle - cpy->last_live[0] + 1, ctd);
				cpy->live = -1;
			}
		}
		else if ((cycle - cpy->last_live[0] - ctd >= 0) && cpy->live != -1)
		{
			if (vm.arg.ver_num.de == 1)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", cpy->number, cycle - cpy->last_live[0], ctd);
			cpy->live = -1;
		}
		cpy = cpy->pre;
	}
	cpy = pro;
	while (cpy != NULL)
	{
		if (cpy->live != -1)
			cpy->live = 0;
		cpy = cpy->next;
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
	if (vm.arg.ver_num.cy == 1)
		ft_printf("It is now cycle %d\n", cycle);
	while (cpy->next != NULL)
		cpy = cpy->next;
	while (cpy != NULL)
	{
		if (cpy->live != -1)
		{
			if (cpy->pc >= inf.min_addr + MEM_SIZE)
				cpy->pc = inf.min_addr;
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
			if (cpy->start_cycle + g_op_tab[cpy->line].cycle == cycle && cpy->line <= 17 && cpy->line >= 0)
			{
				if (cpy->seek == 1)
				{
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
						cpy->pc++;
						if (cpy->pc >= inf.min_addr + MEM_SIZE)
							cpy->pc = inf.min_addr;
					}
					if (!(cpy->inf.val = (int *)malloc(sizeof(int) * 3)))
						return (NULL);
					while (i < g_op_tab[cpy->line].nb_arg)
					{
						p = 0;
						a = 0;
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
							if (cpy->pc >= inf.min_addr + MEM_SIZE)
								cpy->pc = inf.min_addr;
							p++;
						}
						cpy->inf.val[i] = a;
						i++;
					}
					cpy->seek = 2;
					g_instructab[cpy->line](cpy->inf, cpy, vm.arg);
					cpy->start_cycle = -1;
					cpy->seek = 0;
				}
			}
			else if (cpy->line == -1)
				cpy->pc++;
			if (cpy->pc >= inf.min_addr + MEM_SIZE)
				cpy->pc = inf.min_addr;
		}
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
		if (pro->live != -1)
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
		ft_printf("%s ", get_hexa(ptr[i]));
		i++;
	}
	ft_putchar('\n');
}

int			cycle_gestion(t_vm virtual, t_process *pro)
{
	int		win;
	int		val;
	int		check;
	int		die;
	int		cycle_d;

	check = 0;
	virtual.cycle = 1;
	cycle_d = 0;
	val = 0;
	die = 0;
	win = 0;
	while (42)
	{
		if (cycle_d == virtual.ctd)
		{
			if (check_alive(virtual.nb_pros, pro) <= 1)
			{
				;
			}
			cycle_d = 0;
			die = count_live(pro);
			pro = kill_them_all(pro, virtual, virtual.cycle, virtual.ctd);
			if (die >= NBR_LIVE || check == 10)
			{
				check = 0;
				virtual.ctd -= CYCLE_DELTA;
				if (virtual.arg.ver_num.cy == 1)
					ft_printf("Cycle to die is now %d\n", virtual.ctd);
			}
			else
				check++;
		}
		pro = gestion_process(pro, virtual.cycle, virtual, &val);
		if (virtual.ctd < 0)
		{
			win = winner(pro);
			pro = kill_them_all(pro, virtual, virtual.cycle, virtual.ctd);
			break ;
		}
		if (virtual.arg.dump != 0 && virtual.cycle == virtual.arg.dump)
		{
			dump(virtual.addr);
			break ;
		}
		if (virtual.cycle == virtual.arg.end)
			break ;
		virtual.cycle++;
		cycle_d++;
	}
	return (win);
}
