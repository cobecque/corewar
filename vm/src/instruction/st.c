/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:10:39 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/14 13:18:59 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		ft_st(t_inf inf, t_process pros, t_vm vm)
{
	if (inf.typ[0] == 1)
		reg_write(inf.val[0], inf.val[1], REG_SIZE);
	else
		*(pros.pc + (inf.val[1] % IDX_MOD)) = inf.val[0];
}
