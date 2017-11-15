/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 14:14:38 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/14 19:11:05 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/*
** Renvoie 0 si on dois decrementer CYCLE_TO_DIE
*/
int			check_delta(int death, int live, int ctd)
{
	if (live >= NBR_LIVE)
	{
		if (death == ctd)
			return (0);
	}
	return (-1);
}

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

/*
** Gestion des cycles
*/
int			cycle_gestion(t_vm *virtual, t_process *pro, int ctd)
{
	int		check;
	int		cycle;
	int		cycle_d;

	check = 0;
	cycle = 0;
	cycle_d = 0;
	while (check_alive(pro) > 1)
	{
		if (check_delta(cycle_d, nb_live, ctd) == 0 || (check == 10 && ctd > CYCLE_DELTA))
		{
			ctd -= CYCLE_DELTA;
			cycle += cycle_d;
			cycle_d = 0;
			check = 0;
		}
		else if (cycle_d == CYCLE_TO_DIE)
		{
			cycle = cycle_d;
			cycle_d = 0;
			pro = kill_them_all(pro);
			check++;
		}
		else
			cycle_d++;
	}
	return (winner(pro)); // return le numero du champions gagnants
}

while (i < NB_CYCLE_MAX)
{
	if (f1(d1) == 1)
		d1 = d2;
	f2(d1);
	f3(d1);
	f4(d1);
	i++;
}
