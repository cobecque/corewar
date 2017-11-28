/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 14:14:38 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/28 09:09:31 by cobecque         ###   ########.fr       */
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
			{
				ft_printf("Their's more than one process alive, an occured\n");
				break ;
			}
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
	int		i;
	int		nb;

	nb = 0;
	i = 0;
	nb_chicken = 0;
	while (pro != NULL)
	{
		if (pro->live != 0)
			nb++;
		i++;
		pro = pro->next;
	}
	if (nb == 0)
		nb_chicken = -1;
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
	t_process	*fun;
	t_process	*cpy;
	t_inf		inf;
	int			nb;
	int			line;
	int			i;
	int			p;
	int			pos;
	//unsigned char	*aff;
	int				*ret;

	vm.error = 1;
	cpy = pro;
	if (cpy == NULL)
		ft_printf("Ohoh\n");
	//aff = (unsigned char*)(cpy->pc);
	ret = cpy->pc;
	nb = 0;
	p = 0;
//	ft_printf("cycle = %d\n", cycle);
	while (cpy != NULL)
	{
		line = get_line(*(cpy->pc));
		i = 0;
		if (line != -1 && cpy->start_cycle == -1)
			cpy->start_cycle = cycle;
		if (line != -1)
//			ft_printf("pour pros %d  le cpy->start_cycle = %d\n", cpy->number, cpy->start_cycle);
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
				//		ft_printf("One more time\n");
				ft_printf("Champ %d: %s\n", cpy->number, g_op_tab[line].name);
				cpy->pc++;
				//	aff = (unsigned char*)(cpy->pc);
				//	inf = add_elem(line, (int)(*aff));
				inf = add_elem(line, *(cpy->pc));
				inf.min_addr = vm.addr;
				if (have_ocp(line) == 0)
					cpy->pc++;
				if (!(inf.val = (int *)malloc(sizeof(int) * 3)))
					return (NULL);
				while (i < g_op_tab[line].nb_arg)
				{
	//				ft_printf("ici le typ %d et la ligne %d\n", inf.typ[i], line);
					/*if (nb == 3 && line != 0)
						nb = 2;
					if (inf.typ[i] == 0)
					{
					//	ft_printf("addresse pc = %d val = %d inst = %d\n", cpy->pc, *cpy->pc, cpy->ins);
						if (*cpy->pc == 0)
						{
	//						ft_putchar('a');
							cpy->pc++;
							if (*cpy->pc < 0)
							{
								*cpy->pc = 256 + *cpy->pc;
							}
						}
						else if (*cpy->pc == -1)
						{
							cpy->pc++;
							if (*cpy->pc > 0)
							{
								*cpy->pc = -256 + *cpy->pc;
							}
			//				ft_printf("val pc neg %d\n", *cpy->pc);
						}
					}
					else
						cpy->pc = cpy->pc + nb;
					//aff = (unsigned char*)(cpy->pc);
					if (inf.typ[i] == 3)
					{
						//aff = (unsigned char *)(ret + (int)(*aff));
						inf.val[i] = *cpy->pc;/*//*(ret + *(cpy->pc));
					}
					else
						inf.val[i] = *(cpy->pc);
					//inf.val[i] = (int)(*aff);
	//				ft_printf("pc = %d val = %d\n", cpy->pc, inf.val[i]);
					i++;*/
					p = 0;
					pos = 1;
					nb = 0;
					inf.val[i] = 0;
					while (p < inf.l[i])
					{
						nb++;
						if (p == 0 && *cpy->pc != -1)
						{
							pos = 1;
							/*if (*cpy->pc < -128 && *cpy->pc != 0)
							{
								inf.val[i] += (256 + *cpy->pc)  * (ft_pow(256, inf.l[i] - nb));
							}
							else if (*cpy->pc != 0)*/
								inf.val[i] += *cpy->pc * (ft_pow(256, inf.l[i] - nb));
						}
						else if (p == 0 && *cpy->pc == -1)
						{
							pos = 0;
							/*if (*cpy->pc > 128 && *cpy->pc != 0)
							{
								inf.val[i] += (-256 + *cpy->pc)  * (ft_pow(256, inf.l[i] - nb));
							}
							else if (*cpy->pc != 0)
								inf.val[i] += *cpy->pc  * (ft_pow(256, inf.l[i] - nb));*/
						}
						else if (p != 0)
						{
							if (*cpy->pc < 0 && *cpy->pc > -128 && *cpy->pc != 0 && pos == 1)
							{
								inf.val[i] += (256 + *cpy->pc) * (ft_pow(256, inf.l[i] - nb));
							}
							else if (*cpy-> pc > 0 && *cpy->pc < 128 && *cpy->pc != 0 && pos == 0)
								inf.val[i] += (-256 + *cpy->pc) * (ft_pow(256, inf.l[i] - nb));
							else
								inf.val[i] += *cpy->pc  * (ft_pow(256, inf.l[i] - nb));
						}
					//	ft_printf("cpy vaut %d et son adresse est %d inf.val[%d] = %d\n", *cpy->pc, cpy->pc, i, inf.val[i]);
						if (line == 0 && p == 0)
							inf.val[i] = 0;
						cpy->pc++;
						p++;
					}
					ft_printf("val[%d] = %d\n", i, inf.val[i]);
					i++;
				}
			}
			else
				cpy->pc++;
			//ft_printf("%d\n", line);
			if (line == 10)
				g_instructab[6](inf, cpy);
			else if (line == 3)
				g_instructab[3](inf, cpy);
			else if (line == 2)
				g_instructab[2](inf, cpy);
			else if (line == 1)
				g_instructab[1](inf, cpy);
			else if (line == 0)
				g_instructab[0](inf, cpy);
			else if (line == 7)
				g_instructab[4](inf, cpy);
			else if (line == 8)
				g_instructab[5](inf, cpy);
			else if (line == 11)
				g_instructab[7](inf, cpy);
			else if (line == 14)
				g_instructab[8](inf, cpy);
			cpy->start_cycle = -1;
	//		ft_printf("fin instru %d\n", cpy->pc);
	/*		if (cpy->pc + 1 > inf.min_addr + MEM_SIZE)
				cpy->pc = inf.min_addr;
			else
				cpy->pc++;
	*/	}
//		if (line != -1)
//				ft_printf(C_RED"cpy->number %d\n"FC_ALL, cpy->number);
		//	//		ft_printf(C_RED"le reg a la fin de la boucle = %d\n"FC_ALL, cpy->reg[1][3]);
		cpy = cpy->next;
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
			ft_printf("Cycle = %d et nombre processus %d\n", cycle, i);
	//		ft_printf("FIN BOUCLE %d\n", i);
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
