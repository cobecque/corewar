/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 14:14:38 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/23 05:00:05 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/*
** Renvoie 0 si on dois decrementer CYCLE_TO_DIE
*//*
int			check_delta(int death, int live, int ctd)
{
	if (live >= NBR_LIVE)
	{
		if (death == ctd)
			return (0);
	}
	return (-1);
}*/

/*
** Revoye le nombre du champions vainqueur
*/
int			winner(t_process *pro)
{
	int			winner;

	winner = -1;
	while (pro != NULL)
	{
		if (pro->live != 0)
		{
			if (winner != -1 && winner != pro->number)
				ft_printf("Their's more than one process alive, an occured\n");
			else
				winner = pro->number;
		}
		pro = pro->next;
	}
	return (winner);
}

/*
** Repporte le nombre de process vivant
*/
int			check_alive(t_process *pro)
{
	int		nb_chicken;
	int		tab[4] = {0};

	nb_chicken = 0;
	while (pro != NULL)
	{
		if (pro->live != 0)
			tab[pro->number] = 1;
		pro = pro->next;
	}
	nb_chicken = tab[0] + tab[1] + tab[2] + tab[3];
	return (nb_chicken);
}

/*
** Met le live a -1 si le process est mort
*/
t_process	*kill_them_all(t_process *pro)
{
	t_process	*cpy;

	cpy = pro;
	while (cpy != NULL)
	{
		if (cpy->live == 0)
			cpy->live--;			//inserer ici bruitage abbatage
		cpy = cpy->next;
	}
	return (pro);
}

t_process	*gestion_process(t_process *pro, int cycle, t_vm vm)
{
	t_process	*cpy;
	t_inf		inf;
	int			line;
	int			i;
	//unsigned char	*aff;
	int				*ret;

	vm.error = 1;
	cpy = pro;
	if (cpy == NULL)
		ft_printf("Ohoh\n");
	//aff = (unsigned char*)(cpy->pc);
	line = get_line(*(cpy->pc));
	ret = cpy->pc;
	while (cpy != NULL)
	{
		i = 0;
		if (cpy->start_cycle == -1)
			cpy->start_cycle = cycle;
		if (cpy->start_cycle + g_op_tab[line].cycle == cycle)
		{
			if (!cpy->pc)
				ft_printf("clapclap\n");
	//		aff = (unsigned char*)(cpy->pc);
	//		line = get_line((int)(*aff));
			line = get_line(*(cpy->pc));
			if (line != -1)
			{
					ft_printf("Champ %d: %s\n", cpy->number + 1, g_op_tab[line].name);
				cpy->pc++;
			//	aff = (unsigned char*)(cpy->pc);
			//	inf = add_elem(line, (int)(*aff));
				inf = add_elem(line, *(cpy->pc));
				if (!(inf.val = (int *)malloc(sizeof(int) * 3)))
					return (NULL);
				while (i < g_op_tab[line].nb_arg)
				{
					cpy->pc = cpy->pc + inf.typ[i];
					//aff = (unsigned char*)(cpy->pc);
					if (inf.typ[i] == 3)
					{
						//aff = (unsigned char *)(ret + (int)(*aff));
						inf.val[i] = *(ret + *(cpy->pc));
					}
					else
						inf.val[i] = *(cpy->pc);
						//inf.val[i] = (int)(*aff);
					i++;
				}
			}
			else
				cpy->pc++;
			//g_instructab[line.op_code];
			cpy->start_cycle = -1;
			cpy->pc++;
		}
		cpy = cpy->next;
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

/*
** Gestion des cycles
*/
int			cycle_gestion(t_vm virtual, t_process *pro, int ctd)
{
	int		check;
	int		cycle;
	int		cycle_d;

	check = 0;
	cycle = 0;
	cycle_d = 0;
	while (42)
	{
		ft_putchar('a');
		pro = gestion_process(pro, cycle, virtual);
		if (cycle_d == ctd)
		{
			if (check_alive(pro) <= 1)
				break ;
			cycle_d = 0;
			pro = kill_them_all(pro);
			if (count_live(pro) >= NBR_LIVE || check == 10)
			{
				check = 0;
				ctd -= CYCLE_DELTA;
			}
			else
				check++;
		}
		cycle++;
		cycle_d++;
	}
	ft_printf("At the end, cycle = %d\n", cycle);
	return (winner(pro)); // return le numero du champions gagnants
}
