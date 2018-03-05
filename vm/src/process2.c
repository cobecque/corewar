/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:12:48 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/04 22:50:05 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_process		*check_ocp(t_process *cpy, int *nb, int *bol, t_vm vm)
{
	*nb = 1;
	cpy->ocp = *(cpy->pc);
	if (ocp_valid(cpy->line, cpy->ocp) == 0)
		*bol = -1;
	cpy->pc++;
	if (cpy->pc >= cpy->inf.min_addr + MEM_SIZE)
		cpy->pc = cpy->inf.min_addr;
	if (vm.arg.ver_num.pc == 1 && *bol == -1)
		*bol = -2;
	return (cpy);
}

t_process		*calc_len(t_process *cpy, int *len, int *bol, int nb)
{
	cpy->seek = 2;
	if (nb == 1)
	{
		*bol = 2;
		*len += 2;
	}
	else
		*len += 1;
	return (cpy);
}

t_process		*get_adr(t_process *cpy)
{
	if (cpy->line == -1)
	{
		if (cpy->pc >= cpy->inf.min_addr + MEM_SIZE)
			cpy->pc = cpy->inf.min_addr;
		cpy->pc++;
	}
	if (cpy->pc >= cpy->inf.min_addr + MEM_SIZE)
		cpy->pc = cpy->inf.min_addr;
	return (cpy);
}

t_process		*calc_val(int *adv, int *nb, t_process *cpy)
{
	(*adv)++;
	if (*nb == 1)
		(*adv)++;
	ft_printf("ADV %d (0x%.4x -> 0x%.4x) %s", *adv, cpy->ins -
			cpy->inf.min_addr, cpy->ins - cpy->inf.min_addr + *adv,
			get_hexa(*cpy->ins));
	if (*nb == 1)
		ft_printf(" %s", get_hexa(*(cpy->ins + 1)));
	(*nb)++;
	return (cpy);
}

t_process		*reverse_list(int cy, int cycle, t_vm *vm)
{
	t_process	*cpy;

	cpy = vm->end_l;
	if (cy == 1)
		ft_printf("It is now cycle %d\n", cycle);
	return (cpy);
}
