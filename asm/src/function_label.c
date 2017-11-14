/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_label.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 18:44:33 by cobecque          #+#    #+#             */
/*   Updated: 2017/11/08 14:29:00 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		label_pos(t_file *file, char *label, char *code)
{
	char	*new;
	t_file	*tmp;
	int		size;

	new = NULL;
	tmp = file;
	if (label)
		label = ft_strsub(label, 2, ft_strlen(label) - 2);
	if (code)
		new = ft_strdup(code);
	size = octet_on_line(new);
	if (tmp->next != NULL)
		tmp = tmp->next;
	while (tmp != NULL)
	{
		if (tmp->label != NULL && label != NULL)
		{
			if (ft_strcmp(label, tmp->label) == 0)
			{
				if (tmp->code != NULL)
				{
					new = ft_strdup(tmp->code);
					size += octet_on_line(new);
				}
				break;
			}
		}
		if (tmp->code != NULL)
		{
			new = ft_strdup(tmp->code);
			size += octet_on_line(new);
		}
		tmp = tmp->next;
	}
	return (size);
}

int		label_neg(t_file *file, char *label, char *code)
{
	t_file	*tmp;
	char	*new;
	int		size;

	tmp = file;
	new = NULL;
	size = 0;
	if (code)
		new = ft_strdup(code);
	if (label)
		label = ft_strsub(label, 2, ft_strlen(label) - 2);
	while (tmp != NULL)
	{
		if (tmp->label != NULL && label != NULL)
		{
			if (ft_strcmp(tmp->label, label) == 0)
				break;
		}
		tmp = tmp->next;
	}
	while (tmp != NULL)
	{
		if (tmp->code != NULL && ft_strcmp(tmp->code, code) == 0)
			break;
		if (tmp->code != NULL)
		{
			new = ft_strdup(tmp->code);
			size += octet_on_line(new);
		}
		tmp = tmp->next;
	}
	size = - size;
	return (size);
}

int		ft_nb_octet(char *inst)
{
	char	*new;
	int		i;
	int		size;

	i = 0;
	size = 0;
	if (!inst)
		return (0);
	new = ft_strdup(inst);
	while (i < 17)
	{
		if (ft_strcmp(new, g_op_tab[i].name) == 0)
			break;
		i++;
	}
	if (i != 17)
		size = g_op_tab[i].strange;
	if (size == 1)
		return (2);
	else
		return (0);
}

int		octet_on_line(char *code)
{
	int		i;
	int		space;

	i = 0;
	space = 0;
	if (code != NULL)
	{
		while (code[i] != '\0')
		{
			if (code[i] == ' ')
				space++;
			i++;
		}
	}
	i = i - space;
	i = i / 4;
	if (ft_is_spec(code) != -1)
		i++;
	return (i);
}
