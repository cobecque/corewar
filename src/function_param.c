/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_param.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 19:05:35 by cobecque          #+#    #+#             */
/*   Updated: 2017/10/21 16:55:02 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char		*ft_calc_para(char *line, t_file *file)
{
	char	*code;
	char	*new;
	int		i;
	int		bol;
	int		j;
	int		p;

	i = 0;
	bol = 0;
	p = 0;
	code = ft_strdup("\0");
	while (line[i] != '\0')
	{
		p = 0;
		while (line[i] != '\0' && (line[i] == 'r' || line[i] == '%'))
			i++;
		if (line[i] == ':')
			p = 1;
		if (line[i] == 'r' || line[i] == '%')
			i++;
		j = i;
		while (line[i] != '\0' && line[i] != ',')
			i++;
		new = ft_strsub(line, j, i - j);
		if (new != NULL)
		{
			if (new[j] == '%' || ft_strcmp(file->inst, "live") == 0)
			{
				if (new[i] == '\0')
					code = ft_strcat(code, ft_x_octet(file, new, 1, p));
				else
					code = ft_strcat(code, ft_x_octet(file, new, 0, p));
				bol++;
			}
			else
			{
				if (new[i] == '\0')
					code = ft_strcat(code, ft_two_octet(new, 1, p));
				else
					code = ft_strcat(code, ft_two_octet(new, 0, p));
				bol++;
			}
		}
		if (line[i] == ',')
			i++;
	}
	return (code);
}

char		*ft_x_octet(t_file *file, char *str, int bol, int label)
{
	int		i;
	char	*new;
//	char	*yolo;
//	char	*hey;

	i = 0;
	new = NULL;
	if (label == 1)
	{
		new = ft_strdup(" ");
		new = ft_strcat(new, "0xXX");
		return (new);
	}
	while (i < 17)
	{
		if (ft_strcmp(file->inst, g_op_tab[i].name) == 0)
				break;
		i++;
	}
	if (ft_strcmp(file->inst, "live") == 0 || g_op_tab[i].direct_size == 1)
	{
		if (bol == 0)
		{
			new = ft_strdup(" ");
			new = ft_strcat(new, conv_hex(ft_binary(str)));
		}
		if (new == NULL)
			new = ft_strdup(" 0x00");
		new = ft_strcat(new, " ");
		new = ft_strcat(new, "0x00");
		new = ft_strcat(new, " ");
		new = ft_strcat(new, "0x00");
		new = ft_strcat(new, " ");
		new = ft_strcat(new, "0x00");
		if (bol == 1)
		{
			new = ft_strcat(new, " ");
		/*	ft_printf("new = %s\n", new);
			yolo = ft_binary(str);
			ft_printf("yolo = %s\n", yolo);
			if (!(hey = (char *)malloc(sizeof(char) * 5)))
				return (NULL);
			hey = ft_strcpy(hey, conv_hex(yolo));
			ft_printf("hey = %s\n", hey);
			new = ft_strcat(new, hey);
			ft_printf("new a la fin = %s\n", new);*/
			new = ft_strcat(new, conv_hex(ft_binary(str)));
		}
	}
	else
		new = ft_two_octet(str, bol, label);
	return (new);
}

char		*ft_two_octet(char *str, int bol, int label)
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
	}
	if (new == NULL)
		new = ft_strdup(" 0x00");
	new = ft_strcat(new, " ");
	new = ft_strcat(new, "0x00");
	if (bol == 1)
	{
		new = ft_strcat(new, " ");
		new = ft_strcat(new, conv_hex(ft_binary(str)));
	}
	return (new);
}

char	*ft_binary(char *str)
{
	char	*reverse;
	char	*res;
	int		nb;
	int		reste;
	int		i;
	int		j;

	i = 0;
	j = 0;
	nb = ft_atoi(str);
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
	while (i < 8)
	{
		reverse[i] = '0';
		i++;
	}
	reverse[i] = '\0';
	i--;
	while (i >= 0)
	{
		res[j] = reverse[i];
		j++;
		i--;
	}
	res[j] = '\0';
	return (res);
}
