/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:10:39 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/27 15:33:28 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int		s_check_params(t_inf inf)
{
	int			bol;

	bol = 0;
	if (inf.val[0] <= 0 || inf.val[0] > REG_NUMBER)
		bol = 1;
	if (inf.typ[1] == 1 && (inf.val[1] <= 0 || inf.val[0] > REG_NUMBER))
		bol = 1;
	return (bol);
}

static void		s_message(t_vm *vm, t_process *pros, t_inf inf, int res)
{
	if (vm->arg.ver_num.op == 1)
		ft_printf("P%5d | st r%d %d\n", pros->number, inf.val[0], res);
}

void			ft_st(t_inf inf, t_process *pros, t_vm *vm)
{
	char			*adr;
	int				i;
	int				j;
	unsigned int	res;

	if (s_check_params(inf) == 0)
	{
		res = catch_reg_val(1, inf, pros);
		adr = pros->ins + ((int)res % IDX_MOD);
		adr = get_relative(adr, inf);
		i = 0;
		j = -1;
		s_message(vm, pros, inf, res);
		while (++j < 4)
		{
			if ((adr + j) >= inf.min_addr + MEM_SIZE)
			{
				adr = inf.min_addr;
				i = 0;
			}
			*(adr + i) = pros->reg[inf.val[0]][j];
			vm->color[i + (int)adr - (int)inf.min_addr] = pros->champ;
			i++;
		}
	}
}
