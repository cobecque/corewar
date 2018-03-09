/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 01:54:32 by cobecque          #+#    #+#             */
/*   Updated: 2018/03/08 06:44:05 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_cut_comment(char *s, int *i)
{
	int		bol;

	bol = 0;
	if (s[*i] == '#')
	{
		bol = 1;
		while (s[*i] != '\0')
			(*i)++;
	}
	return (bol);
}

int			ft_sep(char *s, int i, int *count)
{
	int		bol;

	bol = ft_cut_comment(s, &i);
	if (s[i] == ' ' || s[i] == '\t')
	{
		while (s[i] == ' ' || s[i] == '\t' || s[i] == ',')
			i++;
		if (s[i] == '#' || s[i] == ';')
		{
			bol = 1;
			while (s[i] != '\0')
				i++;
		}
		if (s[i] != '\0' && bol == 0)
			*count += 1;
		i--;
	}
	else if (s[i] == ',' && bol == 0)
	{
		i++;
		while (s[i] != '\0' && (s[i] == ' ' || s[i] == '\t'))
			i++;
		*count += 1;
	}
	return (i);
}

int			line_size(char *line, int i)
{
	int			j;

	j = 0;
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && line[i] != '"')
		{
			if (line[i] != ' ' && line[i] != '\t')
				j++;
			i++;
		}
		if (line[i] == '"')
		{
			i++;
			j++;
			while (line[i] != '\0' && line[i] != '"')
			{
				i++;
				j++;
			}
		}
		if (line != '\0')
			i++;
	}
	return (j);
}

int			ft_size_label(char *line)
{
	int		i;

	i = 0;
	while (line[i] != '\0' && line[i] != ':')
		i++;
	return (i);
}

char		*cut_label(char *line, int size)
{
	char	*res;
	int		i;
	int		j;

	i = size + 1;
	res = NULL;
	while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
		i++;
	j = i;
	while (line[j] != '\0')
		j++;
	if (line[i] != '\0')
		res = ft_strsub(line, i, j);
	return (res);
}
