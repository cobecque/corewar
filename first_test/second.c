/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 00:15:25 by cobecque          #+#    #+#             */
/*   Updated: 2017/10/20 19:18:09 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	*search_label(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_strdup(line);
	while (new[i] != '\0' && (new[i] != ':' && new[i] != ',') && new[i] != '%')
		i++;
	if (new[i] == ',' || new[i] == '%')
		return (line);
	j = i;
	while (i >= 0 && new[i] != ' ' && new[i] != '\t')
		i--;
	i++;
	new = ft_strsub(line, i, j - i);
	return (new);
}

t_label	*feed_label(t_label *list, t_file *file)
{
	t_file	*tmp;
	char	*label;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = file;
	while (tmp != NULL)
	{
		if (tmp->line != NULL)
		{
			while (tmp->line[i] != '\0' && tmp->line[i] != ':' && tmp->line[i] != '%' && tmp->line[i] != ',')
				i++;
			if (tmp->line[i] == ':')
			{
				label = ft_strsub(tmp->line, 0, i);
				list = init_label(list, label);
			}
		}
		tmp = tmp->next;
	}
	return (list);
}

char	*ft_param(char *line, t_file *file)
{
	t_label	*l;
	char	*new;
	char	*tmp;
	int		i;
	int		j;
	int		bol;

	i = 0;
	j = 0;
	bol = 0;
	new = ft_strdup(line);
	while (new[i] != '\0')
	{
		while (new[i] == ' ' || new[i] == '\t')
			i++;
		if (new[i] == 'r' || new[i] == '%')
			i++;
		j = i;
		while (new[i] != '\0' && new[i] != ',')
			i++;
		tmp = ft_strsub(new, j, i - j);
		if (tmp != NULL)
		{
			if (new[j] == '%' && bol != 1)
			{
				if (new[i] == '\0')
					ft_x_octet(file, tmp, 1);
				else
					ft_x_octet(file, tmp, 0);
			}
			else if (bol != 1)
			{
				if (new[i] == '\0')
					ft_two_octet(file, tmp, 1);
				else
					ft_two_octet(file, tmp, 0);
			}
		}
		if (new[i] == ',')
			i++;
	}
	return (new);
}

char	*ft_look(char *line, t_file *file)
{
	char	*new;
	char	*op_code;
	int		i;
	int		j;

	i = 0;
	j = 0;
	op_code = NULL;
	new = ft_strdup(line);
	while ((new[j] == ' ' || new[j] == '\t') && new[i] != '\0')
		j++;
	new = ft_strsub(line, j, ft_strlen(line) - j);
	while (new[j] != ' ' && new[j] != '\t')
		j++;
	op_code = ft_strsub(new, 0 , j);
	while (i < 17)
	{
		if (ft_strcmp(op_code, g_op_tab[i].name) == 0)
		{
			file->inst = ft_strdup(op_code);
			break;
		}
		i++;
	}
	if (i < 17)
		op_code = ft_conv_hexa(NULL, g_op_tab[i].op_code);
	if (op_code != NULL)
	{
		file->octet = ft_strdup(op_code);
		new = ft_strsub(new, j, ft_strlen(new) - ft_strlen(op_code) + 1);
		return (new);
	}
	return (NULL);
}

char	*ft_loot_type(char *line, t_file *file)
{
	char	*new;
	char	*binary;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_strdup(line);
	if (!(binary = (char *)malloc(sizeof(char) * 9)))
		return (NULL);
	*binary = '\0';
	while (new[i] != '\0')
	{
		while (new[i] != '\0' && (new[i] == '\t' || new[i] == ' '))
			i++;
		if (j != 0 && new[i - 1] != ',')
		{
			while (new[i] != ',' && new[i] != '\0')
				i++;
			i++;
		}
		if (new[i] == 'r')
		{
			binary = ft_strcat(binary, "01");
			j += 2;
		}
		else if (new[i] == '%')
		{
			binary = ft_strcat(binary, "10");
			j += 2;
		}
		else if (new[i] != ',' && new[i] != '\n' && new[i] != '\0')
		{
			binary = ft_strcat(binary, "11");
			j += 2;
		}
		i++;
	}
	while (j < 8)
	{
		binary[j] = '0';
		j++;
	}
	file->octet = ft_strcat(file->octet, ft_conv_hexa(binary, 0));
	return (new);
}

char	*ft_conv_hexa(char *binary, int deci)
{
	char	*hex;
	char	*reverse;
	int		dec;
	int		reste;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dec = 0;
	if (binary == NULL && deci == 0)
		return (NULL);
	if (!(hex = (char *)malloc(sizeof(char) * 5)))
		return (NULL);
	if (!(reverse = (char *)malloc(sizeof(char) *5)))
		return (NULL);
	if (deci == 0)
		dec = binary_to_decimal(binary);
	else if (binary == NULL)
		dec = deci;
	while (dec > 0)
	{
		if (dec < 16)
		{
			reste = dec;
			dec = 0;
		}
		else
		{
			reste = dec % 16;
			dec /= 16;
		}
		if (reste > 9)
		{
			reverse[i] = reste - 10 + 'A';
			i++;
		}
		else
		{
			reverse[i] = reste + 48;
			i++;
		}
	}
	reverse[i] = '\0';
	i--;
	hex[0] = '0';
	hex[1] = 'x';
	if (ft_strlen(reverse) == 1)
	{
		hex[2] = '0';
		j = 3;
	}
	else
		j = 2;
	while (i >= 0)
	{
		hex[j] = reverse[i];
		i--;
		j++;
	}
	hex[j] = '\0';
	if (ft_strcmp(hex, "0x") == 0)
		hex = ft_strdup("0x00");
	return (hex);
}
