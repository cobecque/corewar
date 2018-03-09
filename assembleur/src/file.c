/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 01:05:23 by cobecque          #+#    #+#             */
/*   Updated: 2018/03/08 06:53:20 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_free_tab(char **tab)
{
	int		j;

	j = 0;
	while (tab[j] != NULL)
	{
		free(tab[j]);
		j++;
	}
	free(tab);
}

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
	ft_free_tab(par);
	return (ins);
}

t_file		add_label(t_file file, char *l, int i)
{
	char		*inst;
	t_inst		*tmp;

	file.ins = add_inst(file.ins, i, l);
	tmp = file.ins;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->label = ft_strsub(l, 0, ft_size_label(l));
	inst = cut_label(l, ft_size_label(l));
	instruction(file, inst);
	free(inst);
	return (file);
}

t_file		instruction(t_file file, char *l)
{
	int		i;
	int		j;

	i = 0;
	if (l == NULL)
		return (file);
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
		file = add_label(file, l, i);
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
	free(line);
	return (file);
}
