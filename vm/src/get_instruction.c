/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:35:01 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/20 19:25:47 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include <unistd.h>

t_process		*call_tree(t_inf inf, t_process *pro, t_vm vm)
{
	//pros.number = 1;
	vm.error = 1;
	if (ft_strcmp("live", inf.name) == 0)
		pro = ft_live(pro, inf.val[0]);
	if (ft_strcmp("ld", inf.name) == 0)
		;//ft_ld(inf, pros);
/*	if (ft_strcmp("st", inf.name) == 0)
		ft_st(inf, pros, vm);
	if (ft_strcmp("add", inf.name) == 0)
		ft_add(inf, pros);
	if (ft_strcmp("sub", inf.name) == 0)
		ft_sub(inf, pros);
	if (ft_strcmp("and", inf.name) == 0)
		ft_and(inf, pros);
	if (ft_strcmp("or", inf.name) == 0)
		ft_or(inf, pros);
	if (ft_strcmp("xor", inf.name) == 0)
		ft_xor(inf, pros);
	if (ft_strcmp("zjmp", inf.name) == 0)
		ft_zjmp(inf, pros);
	if (ft_strcmp("ldi", inf.name) == 0)
		ft_ldi(inf, pros);
	if (ft_strcmp("fork", inf.name) == 0)
		ft_fork(inf, pros);
	if (ft_strcmp("lld", inf.name) == 0)
		ft_lld(inf, pros);
	if (ft_strcmp("lldi", inf.name) == 0)
		ft_lldi(inf, pros);
	if (ft_strcmp("lfork", inf.name) == 0)
		ft_lfork(inf, pros);
	if (ft_strcmp("aff", inf.name) == 0)
		ft_aff(inf, pros);*/
	return (pro);
}
/*
void		call_instruction(t_inf *inf, t_process pros, t_vm vm)
{
	while (inf != NULL)
	{
		call_tree(*inf, pros, vm);
		inf = inf->next;
	}
}*/
