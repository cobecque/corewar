/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:33:00 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/02 20:03:57 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int		s_check_params(t_inf inf)
{
	int				bol;

	bol = 0;
	if (inf.val[0] <= 0 || inf.val[0] > REG_NUMBER)
		bol = 1;
	if (inf.typ[1] == 1 && (inf.val[1] <= 0 || inf.val[1] > REG_NUMBER))
		bol = 1;
	if (inf.typ[2] == 1 && (inf.val[2] <= 0 || inf.val[2] > REG_NUMBER))
		bol = 1;
	return (bol);
}

static char		*fill_adr(t_process *pros, char *adr, t_inf inf, t_vm *vm)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (j < 4)
	{
		if ((adr + j) >= inf.min_addr + MEM_SIZE)
		{
			adr = inf.min_addr;
			i = 0;
		}
		*(adr + i) = pros->reg[inf.val[0]][j];
		vm->color[i + (int)adr - (int)inf.min_addr] = pros->champ;
		j++;
		i++;
	}
	return (adr);
}

void			ft_sti(t_inf inf, t_process *pros, t_vm *vm)
{
	char			*adr;
	t_reg			r;
	int				lol;

	if (s_check_params(inf) == 0)
	{
		r.r1 = catch_reg_val(1, inf, pros);
		r.r2 = catch_reg_val(2, inf, pros);
		r.res = r.r1 + r.r2;
		adr = pros->ins + ((int)r.res % IDX_MOD);
		lol = (int)adr;
		adr = get_relative(adr, inf);
		if (lol > 4650 || lol < 0)
			lol = (int)adr;
		if (vm->arg.ver_num.op == 1)
		{
			ft_printf("P%5d | sti r%d %d %d\n       ", pros->number,
					inf.val[0], r.r1, r.r2);
			ft_printf("| -> store to %d + %d = %d (with pc and mod %d)\n",
					r.r1, r.r2, r.res, (int)adr - (int)inf.min_addr);
		}
		adr = fill_adr(pros, adr, inf, vm);
	}
}
