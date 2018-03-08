/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 06:53:46 by cobecque          #+#    #+#             */
/*   Updated: 2018/03/08 06:53:47 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_inst		*init_info(t_inst *new)
{
	new->label = NULL;
	new->label1 = NULL;
	new->label2 = NULL;
	new->label3 = NULL;
	new->typ[0] = 0;
	new->typ[1] = 0;
	new->typ[2] = 0;
	return (new);
}

t_inst		*add_inst(t_inst *ins, int i, char *line)
{
	t_inst	*new;
	t_inst	*tmp;

	tmp = ins;
	if (!(new = (t_inst *)malloc(sizeof(t_inst))))
		return (NULL);
	new->line = i;
	new->len = 0;
	new->ocp = 0;
	new->nb_ins = 1;
	new = init_info(new);
	new->bol = 0;
	if (i != 16)
		new = find_param(line, i, new);
	new->next = NULL;
	if (tmp == NULL)
		return (new);
	while (tmp->next != NULL)
		tmp = tmp->next;
	new->nb_ins = tmp->nb_ins + 1;
	tmp->next = new;
	return (ins);
}

t_file		init_file(void)
{
	t_file	file;

	file.name = NULL;
	file.comment = NULL;
	file.ins = NULL;
	return (file);
}
