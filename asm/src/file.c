/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 01:05:23 by cobecque          #+#    #+#             */
/*   Updated: 2018/02/13 08:29:33 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_inst		*find_param(char *line, int i, t_inst *ins)
{
	char	**par;
	int		j;
	int		ocp;

	j = 0;
	ocp = 0;
	par = ft_cut(line, ',');
	while (par[j] != NULL)
	{
		if (j > 0)
		{
			ins->val[j - 1] = find_val(par[j]);
			ins->typ[j - 1] = find_typ(par[j], i);
			ocp = (ocp << 2) | find_ocp(par[j]);
		}
		j++;
	}
	ins->len = j - 1;
	j = ins->len;
	while (j++ < 4)
		ocp = ocp << 2;
	ins->ocp = ocp;
	j = 0;
	while (par[j] != NULL)
	{
		if (j > 0)
		{
			if (j == 1)
			{
				ins->label1 = have_label(par[j]);
				if (ins->label1 != NULL)
					ins->bol = 1;
			}
			if (j == 2)
			{
				ins->label2 = have_label(par[j]);
				if (ins->label2 != NULL)
					ins->bol = 1;
			}
			if (j == 3)
			{
				ins->label3 = have_label(par[j]);
				if (ins->label3 != NULL)
					ins->bol = 1;
			}
		}
		j++;
	}
	return (ins);
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
	new->label = NULL;
	new->label1 = NULL;
	new->label2 = NULL;
	new->label3 = NULL;
	new->typ[0] = 0;
	new->typ[1] = 0;
	new->typ[2] = 0;
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

t_file		instruction(t_file file, char *line)
{
	int		i;
	int		len;

	i = 0;
	while (i < 16)
	{
		len = ft_strlen(g_op_tab[i].name);
		if (line[0] != '\0')
		{
			if (ft_strncmp(line, g_op_tab[i].name, len) == 0)
			{
				file.ins = add_inst(file.ins, i, line);
				break ;
			}
		}
		i++;
	}
	if (i == 16)
	{
		ft_printf("passage\n");
		if (line && line[0] != '\n' && line[0] != '\0')
		{
			file.ins = add_inst(file.ins, i, line);
			file.ins->label = ft_strsub(line, 0, ft_strlen(line) - 1);
		}
	}
	return (file);
}

t_file		fill_file(t_file file, char *line)
{
	if (ft_strncmp(line, ".name", 5) == 0 && file.name == NULL)
		file.name = ft_strsub(line, 7, ft_strlen(line) - 8);
	else if (ft_strncmp(line, ".comment", 8) == 0 && file.comment == NULL)
		file.comment = ft_strsub(line, 10, ft_strlen(line) - 11);
	else
		file = (instruction(file, line));
	return (file);
}

t_file		init_file(void)
{
	t_file	file;

	file.name = NULL;
	file.comment = NULL;
	file.ins = NULL;
	return (file);
}
