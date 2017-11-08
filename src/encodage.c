/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encodage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 16:19:51 by cobecque          #+#    #+#             */
/*   Updated: 2017/11/07 18:24:23 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_file		*ft_instruction(t_file *file)
{
	t_file	*tmp;

	tmp = file;
	while (tmp != NULL)
	{
		if (tmp->line != NULL)
		{
			tmp->code = search_instruction(tmp->line, tmp->label, tmp);
			if (tmp->code != NULL)
				tmp->line = cut_line(tmp->line, tmp->label);
		}
		tmp = tmp->next;
	}
	return (file);
}

t_file		*ft_ocp(t_file *file)
{
	t_file	*tmp;
	char	*ocp;

	tmp = file;
	while (tmp != NULL)
	{
		if (tmp->inst != NULL && ft_strcmp(tmp->inst, "live") != 0 && ft_strcmp(tmp->inst, "zjmp") != 0 && ft_strcmp(tmp->inst, "lfork") != 0  && ft_strcmp(tmp->inst, "fork") != 0)
		{
			if (tmp->line != NULL && tmp->code != NULL)
			{
				ocp = ft_calc_ocp(tmp->line);
				tmp->code = ft_strcat(tmp->code, " ");
				tmp->code = ft_strcat(tmp->code, ocp);
			}
		}
		tmp = tmp->next;
	}
	return (file);
}

t_file		*ft_parametre(t_file *file)
{
	t_file	*tmp;
	char	*code;

	tmp = file;
	while (tmp != NULL)
	{
		if (tmp->line != NULL && tmp->code != NULL && tmp->inst != NULL)
		{
			code = ft_calc_para(tmp->line, tmp);
			if (code != NULL)
				tmp->code = ft_strcat(tmp->code, code);
			free(code);
		}
		tmp = tmp->next;
	}
	return (file);
}

t_file		*ft_spec_param(t_file *file)
{
	t_file	*tmp;
	int		i;

	tmp = file;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->line != NULL && tmp->code != NULL)
			tmp->code = search_spec(tmp->code, file, i);
		i++;
		tmp = tmp->next;
	}
	return (file);
}
