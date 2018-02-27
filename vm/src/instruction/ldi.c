/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:28:23 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/27 16:33:42 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int			s_check_params(t_inf inf)
{
	int		bol;

	bol = 0;
	if (inf.val[2] <= 0 || inf.val[2] > REG_NUMBER)
		bol = 1;
	if ((inf.typ[0] == 1 && (inf.val[0] <= 0 || inf.val[0] > REG_NUMBER)) ||
			(inf.typ[1] == 1 && (inf.val[1] <= 0 || inf.val[1] > REG_NUMBER)))
		bol = 1;
	return (bol);
}

static t_process	*s_fill_reg(t_process *pros, char *adr, t_inf inf)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (j < 4)
	{
		if ((adr + j) >= inf.min_addr + MEM_SIZE)
		{
			adr = inf.min_addr;
			i = 0;
		}
		pros->reg[inf.val[2]][j] = *(adr + i);
		i++;
		j++;
	}
	return (pros);
}

void				ft_ldi(t_inf inf, t_process *pros, t_vm *vm)
{
	char			*adr;
	t_reg			r;
	int				lol;

	if (s_check_params(inf) == 0)
	{
		r.r1 = catch_reg_val(0, inf, pros);
		r.r2 = catch_reg_val(1, inf, pros);
		r.res = r.r1 + r.r2;
		adr = pros->ins + (r.res % IDX_MOD);
		lol = (int)adr;
		adr = get_relative(adr, inf);
		if (lol > 4456 || lol < -80)
			lol = (int)adr;
		if (lol < 0 && lol > -80)
			lol = lol + 256;
		if (vm->arg.ver_num.op == 1)
		{
			ft_printf("P%5d | ldi %d %d r%d\n       |", pros->number, r.r1,
					r.r2, inf.val[2]);
			ft_printf("-> load from %d + %d = %d (with pc and mod %d)\n", r.r1,
					r.r2, r.res, lol - 256);
		}
		pros = s_fill_reg(pros, adr, inf);
	}
}
