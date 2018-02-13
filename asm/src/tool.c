/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 01:54:32 by cobecque          #+#    #+#             */
/*   Updated: 2018/02/13 08:22:38 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			label_range(t_inst *ins, char *label, int pos, int len)
{
	t_inst	*tmp;
	int		i;

	i = 0;
	tmp = ins;
	while (tmp != NULL)
	{
		if (tmp->label != NULL && ft_strcmp(tmp->label, label) == 0)
		{
			if (tmp->nb_ins < pos)
				i += len;
			break ;
		}
		if (tmp->label == NULL)
		{
			i++;
			if (tmp->ocp != 0)
				i++;
			i += tmp->len;
		}
		tmp = tmp->next;
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

t_inst			*find_label(t_inst *ins)
{
	t_inst		*tmp;

	tmp = ins;
	while (tmp != NULL)
	{
		if (tmp->label == NULL)
		{
			if (tmp->bol != 0)
			{
				tmp->val[0] += check_label(ins, tmp->label1, ins->nb_ins);
				tmp->val[1] += check_label(ins, tmp->label2, ins->nb_ins);
				tmp->val[2] += check_label(ins, tmp->label3, ins->nb_ins);
			}
		}
		tmp = tmp->next;
	}
	return (ins);
}

int			check_label(t_inst *ins, char *label, int line)
{
	int			pos;
	int			len;

	pos = line;
	len = 1;
	if (label != NULL)
		return (label_range(ins, label, pos, len));
	return (0);
}

int			ft_sep(char *s, int i, int *count)
{
	if (s[i] == ' ' || s[i] == '\t')
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (s[i] != '\0')
			*count += 1;
		i--;
	}
	return (i);
}

char		**ft_cut(char *s, char c)
{
	char	**tab;
	int		i;
	int		count;
	int		let;
	int		j;
	int		tmp;

	i = 0;
	tmp = 0;
	count = 0;
	c = 'a';
	if (s)
	{
		while (s[i] != '\0')
		{
			i = ft_sep(s, i, &count);
			i++;
		}
		if (count == 0 && s[i - 1])
			count = 1;
		else
			count++;
		if (!(tab = (char **)malloc(sizeof(char *) * (count + 1))))
			return (NULL);
		j = 0;
		i = 0;
		let = 0;
		while (j < count)
		{
			let = 0;
			while (s[i] != '\0')
			{
				if (s[i] == ' ' || s[i] == '\t')
				{
					while (s[i] == ' ' || s[i] == '\t')
						i++;
					j++;
					break ;
				}
				else
				{
					if (s[i] != ',')
						let++;
					i++;
				}
			}
			if (s[i] == '\0')
				j++;
			tab[j - 1] = ft_strsub(s, tmp, let);
			tmp = i;
		}
		tab[count] = NULL;
		return (tab);
	}
	return (NULL);
}
