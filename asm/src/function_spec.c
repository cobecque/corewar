/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_spec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 17:59:08 by cobecque          #+#    #+#             */
/*   Updated: 2017/11/15 14:10:49 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*search_spec(char *code, t_file *file, int nb)
{
	int		size;
	char	*new;
	t_file	*tmp;
	char	*p1;
	char	*p2;
	char	*p3;
	char	*label;
	int		signe;

	label = NULL;
	new = ft_strdup(code);
	tmp = file;
	p1 = NULL;
	p2 = NULL;
	signe = 0;
	nb = 0;
	size = 0;
	p3 = NULL;
	while (tmp != NULL)
	{
		if (tmp->code != NULL && code != NULL && ft_strcmp(tmp->code, code) == 0)
			break;
		tmp = tmp->next;
	}
	if (tmp->param[0] != NULL)
		p1 = ft_strdup(tmp->param[0]);
	if (tmp->param[1] != NULL)
		p2 = ft_strdup(tmp->param[1]);
	if (tmp->param[2] != NULL)
		p3 = ft_strdup(tmp->param[2]);
	if (p1 != NULL && ft_strncmp(p1, "%:", 2) == 0)
		label = ft_strdup(p1);
	else if (p2 != NULL && ft_strncmp(p2, "%:", 2) == 0)
		label = ft_strdup(p2);
	else if (p3 != NULL && ft_strncmp(p3, "%:", 2) == 0)
		label = ft_strdup(p3);
	if (label != NULL)
		signe = ft_label_signed(file, tmp->line, label);
	if (signe > 0)
		size = label_pos(tmp, label, new);
	else if (signe <= 0)
		size = label_neg(file, label, new);
	if (size == 0)
		return (new);
	if (label && signe > 0)
	{
		signe = ft_is_spec(new);
		label = ft_strsub(new, 0, signe);
		label = ft_strcat(label, "0x00 ");
		label = ft_strcat(label, conv_hex(ft_binary(ft_itoa(size))));
		if (signe + 4 < (int)ft_strlen(new))
			new = ft_strsub(new, signe + 4, ft_strlen(new) - (signe + 4));
		else
			new = ft_strdup("\0");
		new = ft_strcat(label, new);
	}
	if (label && signe <= 0)
	{
		signe = ft_is_spec(new);
		label = ft_strsub(new, 0, signe);
		label = ft_strcat(label, "0xff ");
		label = ft_strcat(label, conv_hex(ft_binary(ft_itoa(size))));
		if (signe + 4 < (int)ft_strlen(new))
			new = ft_strsub(new, signe + 4, ft_strlen(new) - (signe + 4));
		else
			new = ft_strdup("\0");
		new = ft_strcat(label, new);
	}
	return (new);
}

int			ft_label_signed(t_file *file, char *line, char *label)
{
	char	*new;
	char	*lol;
	t_file	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = file;
	new = NULL;
	lol = NULL;
	if (label)
		lol = ft_strsub(label, 2, ft_strlen(label) - 2);
	if (line)
		new = ft_strdup(line);
	while (tmp != NULL)
	{
		if (tmp->label != NULL && lol != NULL && ft_strcmp(lol, tmp->label) == 0)
			break;
		if (tmp->line != NULL)
			i++;
		tmp = tmp->next;
	}
	tmp = file;
	while (tmp != NULL)
	{
		if (tmp->line != NULL && new != NULL && ft_strcmp(tmp->line, new) == 0)
			break;
		if (tmp->line != NULL)
				j++;
		tmp = tmp->next;
	}
	return (i - j);
}

int			ft_is_spec(char *code)
{
	char	*tmp;
	int		i;
	int		nb;

	i = 0;
	nb = ft_strlen(code);
	while (i < nb)
	{
		tmp = ft_strsub(code, i, 4);
		if (ft_strcmp(tmp, "0xXX") == 0)
			return (i);
		i += 4;
		i++;
	}
	return (-1);
}

t_file		*file_param(t_file *file)
{
	t_file	*tmp;
	int		i;
	int		j;
	int		nb;

	tmp = file;
	while (tmp != NULL)
	{
		j = 0;
		i = 0;
		nb = 0;
		if (tmp->line != NULL && tmp->line[i] != '\0')
		{
			while (tmp->line[i] != '\0' && tmp->line[i] != '\t' && tmp->line[i] != ' ')
			{
				j = i;
				while (tmp->line[i] != '\0' && tmp->line[i] != ',' && tmp->line[i] != '\t' && tmp->line[i] != ' ')
					i++;
				tmp->param[nb] = ft_strsub(tmp->line, j, i - j);
				nb++;
				if (tmp->line[i] != '\0')
					i++;
			}
			tmp->param[nb] = NULL;
		}
		tmp = tmp->next;
	}
	return (file);
}
