/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 14:14:38 by rostroh           #+#    #+#             */
/*   Updated: 2017/12/16 03:49:32 by rostroh          ###   ########.fr       */
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
	t_process	*cpy;

	winner = -1;
	cpy = pro;
	while (pro != NULL)
	{
		if (pro->live != 0)
		{
			//		ft_printf("pro %d\n", pro->champ);
			if (winner != -1 && winner != pro->champ)
			{
				winner = -1;
				break ;
				//	ft_printf("Their's more than one process alive, an occured\n");
				//	return (-1);
			}
			else
				winner = pro->champ;
		}
		pro = pro->next;
	}
	//	if (winner == -1)
	//		winner = more_live(cpy);//truc chelou 
	return (winner);
}

/*
 ** Repporte le nombre de process vivant
 */
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
		//		i++;
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
	//	if (nb == 0)
	//		nb_chicken = -1;
	return (nb_chicken);
}

/*
 ** Met le live a -1 si le process est mort
 */
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
			//	free(tmp->pc);
			//	free(tmp->ins);
			tmp = cpy->next;
			//	free(tmp);
		}
		while (cpy->next != NULL)
		{
			if (cpy->next->live == 0)
			{
				tmp = cpy->next;
				//	free(tmp->pc);
				//	free(tmp->ins);
				tmp->next = tmp->next;
				//	free(tmp);
			}
			else
				cpy->next->live = 0;
			cpy = cpy->next;
		}
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
					//ft_printf("Champ %d: %s\n", cpy->number, g_op_tab[line].name);
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
						inf.val[i] = *cpy->pc;*//*(ret + *(cpy->pc));
												  }
												  else
												  inf.val[i] = *(cpy->pc);
						//inf.val[i] = (int)(*aff);
						//				ft_printf("pc = %d val = %d\n", cpy->pc, inf.val[i]);
						i++;*/
						//ft_printf("cpy adresse = %d\n", cpy->pc);
						p = 0;
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
										inf.val[i] += *cpy->pc * (ft_pow(256, inf.l[i] - nb));
								}
							}
							if (line == 0 && p == 0)
								inf.val[i] = 0;
							cpy->pc++;
							p++;
						}
						//ft_printf("val[%d] = %d\n", i, inf.val[i]);
						i++;
					}
				}
				else
					cpy->pc++;
				//ft_printf("%d\n", line);
				//	if (cpy->reg[2][3] != 0)
				//			ft_printf("hahahah = %d\n", cpy->reg[2][3]);
				//		if (cpy->reg[4][3] != 0)
				//			ft_printf("voila = %d\n", cpy->reg[4][3]);
				if (line <= 17)
				{
					ft_printf("cylce %d et %s\n", cycle, g_op_tab[line].name);
//					if (line == 10)
//						ft_printf("cylce %d\n", cycle);
					g_instructab[line](inf, cpy);
				}
		/*		if (line == 10)
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
					g_instructab[8](inf, cpy);*/
				cpy->start_cycle = -1;
				//		ft_printf("fin instru %d\n", cpy->pc);
				if (cpy->pc + 1 > inf.min_addr + MEM_SIZE)
					cpy->pc = inf.min_addr;
				//		else
				//			cpy->pc++;
			}
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
		//ft_printf("Cycle = %d et nombre processus %d\n", cycle, i);
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

char		*get_hexa(int val)
{
	char	*str;

	if (val == 0)
		return ("00");
	str = (char *)malloc(sizeof(char) * 3);
	str[2] = '\0';
	if (val < 0)
	{
//		ft_putchar('a');
		val = 256 + val;
	}
	if (val % 16 >= 10)
		str[1] = val % 16 + 'a' - 10;
	if (val % 16 < 10)
		str[1] = val % 16 + '0';
//	ft_putchar(str[1]);
	if (val / 16 >= 10)
		str[0] = val / 16 + 'a' - 10;
	if (val / 16 < 10)
		str[0] = val / 16 + '0';
//	ft_putchar(str[0]);
	//ft_printf("%s\n", str);
	return (str);
}

void		dump(int *ptr)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE - 1)
	{
		if (i % 64 == 0 && i != 0)
			ft_putchar('\n');
		if (ptr[i] != 0)
			ft_printf(C_RED"%s "FC_ALL, get_hexa(ptr[i]));
		else
			ft_printf("%s ", get_hexa(ptr[i]));
		i++;
	}
	ft_putchar('\n');
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
//	dump(virtual.addr);
	while (42)
	{
		pro = gestion_process(pro, cycle, virtual);
		if (cycle_d == ctd)
		{
			//	ft_putchar('a');
			if (check_alive(virtual.nb_pros, pro) <= 1)
			{
				//		ft_putchar('?');
				break ;
			}
			cycle_d = 0;
			if (count_live(pro) >= NBR_LIVE || check == 10)
			{
				check = 0;
				ctd -= CYCLE_DELTA;
				if (ctd < 0)
					break ;
				//	ft_printf("CYLE_TO_DIE = %d\n", ctd);
			}
			else
				check++;
			pro = kill_them_all(pro);
		}
		cycle++;
		cycle_d++;
	}
	dump(virtual.addr);
	//ft_printf("At the end, cycle = %d\n", cycle);
	return (winner(pro)); // return le numero du champions gagnants
}