/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 15:42:09 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/08 08:44:31 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_process		*call_instru(t_process *cpy, t_var *var, t_vm *vm)
{
	if (!(cpy->inf.val = (int *)malloc(sizeof(int) * 3)))
		return (NULL);
	var->len = 0;
	var->adv = 0;
	var->bol = 1;
	find_val(cpy, &var->adv, &var->len);
	cpy = calc_len(cpy, &var->len, &var->bol, var->nb);
	g_instructab[cpy->line](cpy->inf, cpy, vm);
	cpy->pc = cpy->ins;
	if (vm->arg.ver_num.pc == 1 && (cpy->line != 8 ||
				cpy->carry == 0))
	{
		cpy = calc_val(&var->adv, &var->nb, cpy);
		cpy = adv_printf(cpy, var->len - var->bol, var->nb);
		if (vm->arg.ver_num.pc == 1)
			ft_printf(" \n");
	}
	cpy = move_pc(cpy, var->len);
	free(cpy->inf.val);
	return (cpy);
}

t_process		*if_must_be_call(t_process *cpy, t_var *var, t_vm *vm)
{
	cpy = init_inf(cpy, *vm, &var->nb, &var->bol);
	if (have_ocp(cpy->line) == 0)
	{
		cpy = check_ocp(cpy, &var->nb, &var->bol, *vm);
		cpy = ocp_invalid(cpy, &var->bol, &var->len);
	}
	if (var->bol == 0)
		cpy = call_instru(cpy, var, vm);
	cpy->start_cycle = -1;
	cpy->seek = 0;
	free(cpy->inf.l);
	free(cpy->inf.typ);
	return (cpy);
}
