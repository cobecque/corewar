/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 09:22:58 by cobecque          #+#    #+#             */
/*   Updated: 2018/02/14 09:56:52 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			label_range(t_inst *ins, char *label, int pos)
{
	t_inst	*tmp;
	int		i;
	int		j;
	int		neg;

	tmp = ins;
	neg = 1;
	i = 0;
	while (tmp != NULL)
	{
		j = 0;
		if (tmp->label != NULL && ft_strcmp(tmp->label, label) == 0)
			neg = -1;
		if (tmp->label == NULL && tmp->nb_ins >= pos && neg == 1)
			i = ocp_calc(tmp, i, neg);
		else if (tmp->label == NULL && tmp->nb_ins < pos && neg == -1)
			i = ocp_calc(tmp, i, neg);
		tmp = tmp->next;
	}
	return (i);
}

int			ocp_calc(t_inst *tmp, int i, int neg)
{
	int		j;

	j = 0;
	if (neg == 1)
	{
		i++;
		if (tmp->ocp != 0)
			i++;
		while (++j < tmp->len + 1)
			i += tmp->typ[j - 1];
	}
	else if (neg == -1)
	{
		i--;
		if (tmp->ocp != 0)
			i--;
		while (++j < tmp->len + 1)
			i -= tmp->typ[j - 1];
	}
	return (i);
}

char		*have_label(char *par)
{
	char	*tmp;

	if (par[0] == '%' && par[1] == ':')
		tmp = ft_strsub(par, 2, ft_strlen(par) - 2);
	else
		return (NULL);
	return (tmp);
}

t_inst		*find_label(t_inst *ins)
{
	t_inst		*tmp;

	tmp = ins;
	while (tmp != NULL)
	{
		if (tmp->label == NULL)
		{
			if (tmp->bol != 0)
			{
				tmp->val[0] += check_label(ins, tmp->label1, tmp->nb_ins);
				tmp->val[1] += check_label(ins, tmp->label2, tmp->nb_ins);
				tmp->val[2] += check_label(ins, tmp->label3, tmp->nb_ins);
			}
		}
		tmp = tmp->next;
	}
	return (ins);
}

int			check_label(t_inst *ins, char *label, int line)
{
	int			pos;

	pos = line;
	if (label != NULL)
		return (label_range(ins, label, pos));
	return (0);
}
