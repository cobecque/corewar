/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 09:11:04 by cobecque          #+#    #+#             */
/*   Updated: 2018/03/07 07:45:09 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*cut_start(char *line)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if (i == 0)
		{
			while (line[i] != '\0' && (line[i] == '\t' || line[i] == ' '))
			{
				i++;
				j++;
			}
		}
		if (line[i] != '\0')
			i++;
	}
	res = ft_strsub(line, j, ft_strlen(line) - j);
	return (res);
}

char		**ft_cut(char *s, int i, int j, int count)
{
	char	**tab;
	int		let;
	int		tmp;

	tmp = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
		i = ft_sep(s, i, &count) + 1;
	count++;
	if (!(tab = (char **)malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	i = 0;
	while (j < count)
	{
		let = 0;
		ft_letter(s, &i, &j, &let);
		tab[j - 1] = ft_strsub(s, tmp, let);
		tmp = i;
		if (s[i] == '\0')
			j++;
	}
	tab[count] = NULL;
	return (tab);
}

int			ft_letter(char *s, int *i, int *j, int *let)
{
	while (s[*i] != '\0')
	{
		if (s[*i] == ' ' || s[*i] == '\t' || s[*i] == ',')
		{
			if (s[*i] == ',')
				(*i)++;
			while (s[*i] != '\0' && (s[*i] == ' ' || s[*i] == '\t' || s[*i] == ','))
				(*i)++;
			(*j)++;
			return (0);
		}
		else
		{
			(*let)++;
			(*i)++;
			if (s[*i] == '\0')
				(*j)++;
		}
	}
	return (1);
}

char		*cut_middle(char *line)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = line_size(line, i);
	if (!(res = (char *)malloc(sizeof(char *) * j + 1)))
		return (NULL);
	j = 0;
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && line[i] != '"')
		{
			if (line[i] != ' ' && line[i] != '\t')
			{
				res[j] = line[i];
				j++;
			}
			i++;
		}
		cpy_name(res, line, &i, &j);
	}
	j++;
	res[j] = '\0';
	return (res);
}

void		cpy_name(char *res, char *line, int *i, int *j)
{
	if (line[*i] == '"')
	{
		res[*j] = line[*i];
		(*i)++;
		(*j)++;
		while (line[*i] != '\0' && line[*i] != '"')
		{
			res[*j] = line[*i];
			(*i)++;
			(*j)++;
		}
		if (line[*i] == '"')
			res[*j] = line[*i];
	}
	if (line[*i] != '\0')
		(*i)++;
}
