/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 01:05:23 by cobecque          #+#    #+#             */
/*   Updated: 2018/02/14 09:59:38 by cobecque         ###   ########.fr       */
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
	par = ft_cut(line, 0, 0, 0);
	while (par[j] != NULL)
	{
		if (j > 0)
		{
			ins->val[j - 1] = find_val(par[j]);
			ins->typ[j - 1] = find_typ(par[j], i);
			ocp = (ocp << 2) | find_ocp(par[j], i);
		}
		j++;
	}
	ins->len = j - 1;
	j = ins->len;
	while (j++ < 4)
		ocp = ocp << 2;
	ins->ocp = ocp;
	ins = label_param(par, ins);
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

t_file		instruction(t_file file, char *l)
{
	t_inst	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < 16)
	{
		j = ft_strlen(g_op_tab[i].name);
		if (l[0] != '\0' && ft_strncmp(l, g_op_tab[i].name, j) == 0 &&
				(l[j] == '\t' || l[j] == ' ') && j < (int)ft_strlen(l))
		{
			file.ins = add_inst(file.ins, i, l);
			break ;
		}
		i++;
	}
	if (i == 16 && l && l[0] != '\n' && l[0] != '\0')
	{
		file.ins = add_inst(file.ins, i, l);
		tmp = file.ins;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->label = ft_strsub(l, 0, ft_strlen(l) - 1);
	}
	return (file);
}

t_file		fill_file(t_file file, char *line)
{
	line = cut_start(line);
	if (ft_strncmp(line, ".name", 5) == 0 && file.name == NULL)
	{
		line = cut_middle(line);
		file.name = ft_strsub(line, 6, ft_strlen(line) - 7);
	}
	else if (ft_strncmp(line, ".comment", 8) == 0 && file.comment == NULL)
	{
		line = cut_middle(line);
		file.comment = ft_strsub(line, 9, ft_strlen(line) - 10);
	}
	else if (line[0] != '#')
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
