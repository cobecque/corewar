/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:28:23 by rostroh           #+#    #+#             */
/*   Updated: 2017/12/19 12:05:57 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_ldi(t_inf inf, t_process *pros)
{
/*	char	*adr;
	int		i;
	int		res;

	i = 0;
	res = 0;
	if (inf.typ[0] != 1)
	{
		if (*(pros->ins + 2) == -1)
			res = *(pros->ins + 3);
		else
			res = inf.val[0];
	}
	if (inf.typ[0] == 1)
		res += pros->val[inf.val[0]];
	if (inf.typ[1] == 1)
		res += pros->val[inf.val[1]];
	adr = pros->ins + res;
	pros->carry = (adr == 0) ? 1 : 0;
	while (i < 4)
	{
		pros->reg[inf.val[2]][i] = *(adr + i);
		pros->val[inf.val[2]] += *(adr + i);
		i++;
	}*/
	unsigned int	res;
	char			*adr;
	int				i;

	//ft_printf(C_YEL"coucou je suis le ldi a l'adresse %d\n"FC_ALL, pros->ins);
	res = 0;
	if (inf.typ[0] == 1)
	{
		i = 0;
		while (i < 4)
		{
			res += pros->reg[inf.val[0]][i];
			i++;
		}
	}
	else
		res += inf.val[0];
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
	adr = pros->ins + (int)res;
	pros->carry = (adr == 0) ? 1 : 0;
	i = 0;
	while (i < 4)
	{
		pros->reg[inf.val[2]][i] = *(adr + i);
		pros->val[inf.val[2]] += *(adr + i);
	//	ft_printf("reg[%d][%d] = %d ou plutot %x\n", inf.val[2], i, pros->reg[inf.val[2]][i], pros->reg[inf.val[2]][i]);
		i++;
	}
}
