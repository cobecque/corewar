/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_param.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 19:05:35 by cobecque          #+#    #+#             */
/*   Updated: 2017/11/15 19:38:38 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*ft_calc_para(char *line, t_file *file, int i)
{
	char	*c;
	char	*new;
	char	*tmp;
	int		j;
	int		p;

	i = 0;
	c = ft_strdup("\0");
	if (line == NULL)
		return (NULL);
	tmp = ft_strdup(line);
	new = NULL;
	while (tmp[i] != '\0')
	{
		ft_get_par(tmp, &i, &j, &p);
		new = ft_strsub(tmp, j, i - j);
		if (new != NULL)
		{
			if (tmp[j] == '%' || ft_strcmp(file->inst, "live") == 0
					|| (j - 1 >= 0 && tmp[j - 1] == '%'
						&& tmp[j] != ':' && tmp[j - 1] != 'r'))
			{
				if (tmp[i] == '\0')
					c = ft_strcat(c, ft_x_octet(file, new, 2, p));
				else if (j - 1 == 0)
					c = ft_strcat(c, ft_x_octet(file, new, 0, p));
				else if (j - 1 > 0)
					c = ft_strcat(c, ft_x_octet(file, new, 1, p));
			}
			else
			{
				if (j - 1 >= 0)
				{
					if (tmp[i] == '\0')
						c = ft_strcat(c, ft_two_octet(new, 1, p, tmp[j - 1]));
					else
						c = ft_strcat(c, ft_two_octet(new, 0, p, tmp[j - 1]));
				}
			}
		}
		if (tmp[i] == ',')
			i++;
	}
	return (c);
}

void		ft_get_par(char *tmp, int *i, int *j, int *p)
{
	*p = 0;
	while (tmp[*i] != '\0' && (tmp[*i] == 'r' || tmp[*i] == '%'))
		(*i)++;
	if (tmp[*i] == ':')
		*p = 1;
	if (tmp[*i] == 'r' || tmp[*i] == '%')
		(*i)++;
	*j = *i;
	while (tmp[*i] != '\0' && tmp[*i] != ',')
		(*i)++;
}

char		*ft_x_octet(t_file *file, char *str, int bol, int label)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	if (label == 1)
	{
		new = ft_strdup(" 0xXX");
		return (new);
	}
	while (i < 17)
	{
		if (ft_strcmp(file->inst, g_op_tab[i].name) == 0)
			break;
		i++;
	}
	if ((ft_strcmp(file->inst, "live") == 0 || g_op_tab[i].direct_size == 1) && ft_strcmp(file->inst, "sti") != 0)
	{
		if (bol == 1 && ft_strcmp(file->inst, "xor") != 0)
		{
			new = ft_strdup(" ");
			new = ft_strcat(new, conv_hex(ft_binary(str)));
		}
		if (new == NULL)
			new = ft_strdup(" 0x00");
		new = ft_strcat(new, " 0x00 0x00");
		if (bol == 2 || bol == 0 || ft_strcmp(file->inst, "xor") == 0)
		{
			new = ft_strcat(new, " ");
			new = ft_strcat(new, conv_hex(ft_binary(str)));
		}
	}
	else
	{
		if (bol == 2)
			bol = 1;
		new = ft_two_octet(str, bol, label, '%');
	}
	return (new);
}

char		*ft_two_octet(char *str, int bol, int label, char pa)
{
	char	*new;

	new = NULL;
	if (label == 1)
	{
		new = ft_strdup(" 0xXX");
		return (new);
	}
	if (bol == 0)
	{
		new = ft_strdup(" ");
		new = ft_strcat(new, conv_hex(ft_binary(str)));
		if (pa != 'r')
			new = ft_strcat(new, " 0x00");
	}
	if (new == NULL && pa != 'r')
		new = ft_strdup(" 0x00");
	if (bol == 1)
	{
		if (pa == 'r')
			new = ft_strdup("\0");
		new = ft_strcat(new, " ");
		new = ft_strcat(new, conv_hex(ft_binary(str)));
	}
	return (new);
}

char		*ft_binary(char *str)
{
	char	*reverse;
	char	*res;
	int		nb;
	int		reste;
	int		i;
	int		j;
	int		neg;

	i = 0;
	j = 0;
	neg = 1;
	nb = ft_atoi(str);
	if (nb < 0)
	{
		neg = -1;
		nb = -nb;
	}
	if (!(reverse = (char *)malloc(sizeof(char) * 9)))
		return (NULL);
	if (!(res = (char *)malloc(sizeof(char) * 9)))
		return (NULL);
	while (nb > 0)
	{
		reste = nb % 2;
		nb /= 2;
		reverse[i] = reste + '0';
		i++;
	}
	while (i + j < 8)
	{
		reverse[i] = '0';
		i++;
	}
	reverse[i] = '\0';
	if (neg == -1)
	{
		i = 0;
		while (reverse[i] != '\0')
		{
			if (reverse[i] == '1')
				reverse[i] = '0';
			else
				reverse[i] = '1';
			i++;
		}
		i = 0;
		while (reverse[i] == '1')
			i++;
		if (reverse[i] != '\0')
			reverse[i] = '1';
		i = ft_strlen(reverse);
	}
	i--;
	while (i >= 0)
	{
		res[j] = reverse[i];
		j++;
		i--;
	}
	res[j] = '\0';
	free(reverse);
	return (res);
}
