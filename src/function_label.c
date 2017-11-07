/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_label.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 18:44:33 by cobecque          #+#    #+#             */
/*   Updated: 2017/10/28 04:06:59 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		label_pos(t_file *file, char *label, char *code)
{
	char	*new;
	t_file	*tmp;
	int		space;
	int		size;
	int		i;
	int		l;

	new = NULL;
	space = 0;
	size = 0;
	l = 0;
	tmp = file;
	if (label)
		label = ft_strsub(label, 2, ft_strlen(label) - 2);
	if (code)
		new = ft_strdup(code);
	i = ft_is_spec(new);
	if (i == -1)
		return (size);
	i += 4;
	while (i < (int)ft_strlen(new))
	{
		if (size % 4 == 0 && size != 0)
			space++;
		size++;
		i++;
	}
	size -= space;
	if (tmp->next != NULL)
		tmp = tmp->next;
	while (tmp != NULL)
	{
		space = 0;
		if (tmp->label != NULL && label != NULL)
		{
			if (ft_strcmp(label, tmp->label) == 0)
			{
				if (tmp->code != NULL)
				{
					new = ft_strdup(tmp->code);
					i = 0;
					space = 0;
					while (new[i] != '\0')
					{
						if (new[i] == ' ')
							space++;
						i++;
					}
					size += i - space;
				}
				break;
			}
		}
		if (tmp->code != NULL)
		{
			new = ft_strdup(tmp->code);
			i = 0;
			while (new[i] != '\0')
			{
				if (new[i] == ' ')
					space++;
				i++;
			}
			size += i - space;
		}
		tmp = tmp->next;
		l++;
	}
	size = (size + l) / 4;
	return (size);
}

int		label_neg(t_file *file, char *label, char *code)
{
	t_file	*tmp;
	char	*new;
	int		size;
	int		space;
	int		i;

	tmp = file;
	new = NULL;
	size = 0;
	space = 0;
	if (code)
		new = ft_strdup(code);
	if (label)
		label = ft_strsub(label, 2, ft_strlen(label) - 2);
	i = ft_is_spec(new);
	if (i == -1)
		return (size);
	while (i > 0)
	{
		if (size % 4 == 0 && size != 0)
			space++;
		size++;
		i--;
	}
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
		if (tmp->code != NULL && ft_strcmp(tmp->code, new) == 0)
		{
			i = 0;
			space = 0;
			while (new[i] != '\0')
			{
				if (new[i] == 'X')
					break;
				if (new[i] == ' ')
					space++;
				i++;
			}
			size -= i - space;
			break;
		}
		if (tmp->code != NULL)
		{
			space = 0;
			i = 0;
			new = ft_strdup(tmp->code);
			while (new[i] != '\0')
			{
				if (new[i] == ' ')
					space++;
				i++;
			}
			size -= i - space;
		}
		tmp = tmp->next;
	}
	size /= 4;
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
		return (4);
	else
		return (2);
}
