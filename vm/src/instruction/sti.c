/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:33:00 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/06 07:56:31 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int			relative(int *adr, int val)
{
	int		ret;

	ret = (int)adr;
	return (ret + val);
}

void		ft_sti(t_inf inf, t_process *pros)
{
//	int			ret;
//	char		*adr;
/*
	ret = 0;
	if (inf.typ[1] == 1)
		ret += pros->val[inf.val[1]];
	else
	{
		if (*(pros->ins + 3) == -1)
		{
			ret += *(pros->ins + 4);
		}
		else
			ret += inf.val[1];
	}
	if (inf.typ[2] == 1)
	{
//		ft_putchar('b');
	//	ft_printf("la val qui bug romeo %d\n", pros->val[inf.val[2]]);
		ret += pros->val[inf.val[2]];
	//	ft_printf("%d\n", ret);
//		if (pros->start_cycle >= 3340)
//			ft_printf("\tr2 = %d\t", pros->val[inf.val[2]]);
	}
	else
	{
		if (inf.typ[1] == 1)
		{
			if (*(pros->ins + 4) == -1)
				ret += *(pros->ins + 5);
			else
				ret += inf.val[2];
		}
		else
		{
			if (*(pros->ins + 5) == -1)
				ret += *(pros->ins + 6);
			else
				ret += inf.val[2];
		}
	}
		//	if (ret < 0)
//		ret /= 4;
	adr = pros->ins + (int)ret;
//	ft_printf("min adr = %d registre = %d adr = %d avec ret = %d et pros->ins = %d\n",(int)inf.min_addr,  inf.val[0], (int)adr, ret, (int)pros->ins);
//	if (pros->start_cycle >= 3340)
//		ft_printf("\tret = %d\n", ret);
	if (adr < inf.min_addr)
	{
//		ft_printf("LE CALCUL : %d pour %d %d et %d %d\n", (int)adr, pros->ins, (MEM_SIZE) + inf.min_addr, inf.min_addr, (int)adr % MEM_SIZE);
//		adr = inf.min_addr + MEM_SIZE / 4 + ((int)adr % MEM_SIZE - (int)inf.min_addr);
//		ft_putchar('c');
//		ft_printf("1: adr = %d, max_adr = %d, trop = %d\n", adr, inf.min_addr + MEM_SIZE, (int)adr % MEM_SIZE);
		if ((int)adr > 0)
			adr = inf.min_addr + MEM_SIZE - ((int)inf.min_addr - ((int)adr % MEM_SIZE));
		else
			adr = inf.min_addr + MEM_SIZE + (int)adr % MEM_SIZE;
	//	ft_printf("neg fuck %d\n", (int)adr);
		//		ft_printf("2: adr = %d\n", adr);
		//adr = (int)adr % MEM_SIZE;
	}
	else if (adr > inf.min_addr + MEM_SIZE)
	{
//		ft_putchar('d');
		adr = inf.min_addr + (int)adr % MEM_SIZE;
	}
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (j < 4)
	{
		if ((adr + j) >= inf.min_addr + MEM_SIZE)
		{
			adr = inf.min_addr;
			i = 0;
		}
		*(adr + i) = pros->reg[inf.val[0]][j]; //SEGF sur max adr
		j++;
		i++;
	}*/
	char			*adr;
	int				res;
	int				bug;
	int				i;
	int				j;
	int				ff;

	ff = 0;
//	if (inf.val[0] != 1)
//	ft_printf(C_YEL"arrive de sti dans la place a l'adresse %d avec pour valeur %d et %d\n"FC_ALL, (int)pros->ins, inf.val[1], inf.val[2]);
	res = 0;
	bug = 0;
	if (inf.typ[1] == 1)
	{
		i = 0;
		while (i < 4)
		{
			res += pros->reg[inf.val[1]][i];
			i++;
		}
	}
	else
		res += inf.val[1];
	//ft_printf("res avant le r2 %d\n", res);
	if (inf.typ[2] == 1)
	{
		i = 0;
		while (i < 4)
		{
			if (ff == 0 && pros->reg[inf.val[2]][i] == 255)
				;
			else
			{
				if (ff == 0 && i > 0)
				{
					bug += (-256 + pros->reg[inf.val[2]][i]);
				}
				else
					bug += pros->reg[inf.val[2]][i];
	//			ft_printf("res apres le r2 %d && pros>reg = %d\n", bug, pros->reg[inf.val[2]][i]);
				ff = 1;
			}
			i++;
		}
	}
	else
		res += inf.val[2];
	//if (inf.val[0] != 1)
//		ft_printf("pros numero %d & res je t'ai jamais aime %d\n\n", pros->number, res + bug);
	res = (int)res + (int)bug;
	adr = pros->ins + ((int)res % IDX_MOD);
	if (adr < inf.min_addr)
	{
		if ((int)adr > 0)
			adr = inf.min_addr + MEM_SIZE - ((int)inf.min_addr - ((int)adr % MEM_SIZE));
		else
			adr = inf.min_addr + MEM_SIZE + (int)adr % MEM_SIZE;
	}
	else if (adr > inf.min_addr + MEM_SIZE)
		adr = inf.min_addr + MEM_SIZE - (adr - inf.min_addr + MEM_SIZE);
	i = 0;
	j = 0;
	while (j < 4)
	{
		if ((adr + j) >= inf.min_addr + MEM_SIZE)
		{
			adr = inf.min_addr;
			i = 0;
		}
		*(adr + i) = pros->reg[inf.val[0]][j]; //SEGF sur max adr
	//	ft_printf(C_RED"reg[%d][%d] = %x a l'adresse %d\n"FC_ALL, inf.val[0], j, pros->reg[inf.val[0]][j], (int)(adr + i));
		j++;
		i++;
	}
}
