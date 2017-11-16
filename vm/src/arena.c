/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 14:14:38 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/16 16:58:14 by rostroh          ###   ########.fr       */
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
	unsigned char *aff;

	vm.error = 1;
	cpy = pro;
	i = 0;
	if (cpy == NULL)
		ft_printf("Ohoh\n");
	aff = (unsigned char*)(cpy->pc);
	line = get_line((int)(*aff));
	while (cpy != NULL)
	{
		//ft_printf("number = %d, line = %d et cycle = %d\n", cpy->number, line, cycle);
		if (cpy->start_cycle == -1)
			cpy->start_cycle = cycle;
		if (cpy->start_cycle + g_op_tab[line].cycle == cycle)
		{
			ft_printf("Champ%d: Execution de %s\n", cpy->number, g_op_tab[line].name);
			aff = (unsigned char*)(cpy->pc);
			line = get_line((int)(*aff));
			cpy->pc++;
			aff = (unsigned char*)(cpy->pc);
			inf = add_elem(line, (int)(*aff));
			if (!(inf.val = (int *)malloc(sizeof(int) * 3)))
				return (NULL);
		//	ft_printf("%d\n", g_op_tab[line].nb_arg);
			if (line != -1)
			{
				while (i < g_op_tab[line].nb_arg)
				{
					if (inf.typ[i] == 3 && ft_strcmp("live", g_op_tab[line].name))
						inf.typ[i] = 2;
				//	ft_printf("typ = %d\n", inf.typ[0]);
					cpy->pc = cpy->pc + inf.typ[i];
					aff = (unsigned char*)(cpy->pc);
					inf.val[i] = (int)(*aff);
	//				ft_printf(C_RED"inf.val[%d] = %d\n"FC_ALL, i, inf.val[i]);
					i++;
				}
			}
			call_tree(inf, *cpy, vm);
			cpy->start_cycle = -1;
			cpy->pc++;
			ft_printf("Champ%d: Fin execution de %s\n", cpy->number, g_op_tab[line].name);
		}
		cpy = cpy->next;
	}
//	ft_printf("FIN\n");
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
	return (winner(pro)); // return le numero du champions gagnants
}
