/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_ocp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 18:00:37 by cobecque          #+#    #+#             */
/*   Updated: 2017/11/08 14:28:19 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char		*ft_calc_ocp(char *line)
{
	char	*binary;
	char	*new;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!(binary = (char *)malloc(sizeof(char) * 9)))
		return (NULL);
	new = ft_strdup(line);
	binary = ft_strcpy(binary, "\0");
	while (new[i] != '\0')
	{
		if (j != 0 && new[i - 1] != ',')
		{
			while (new[i] != '\0' && new[i] != ',')
				i++;
			if (new[i] != '\0')
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
		else if (new[i] != ',' && new[i] != '\n' && new[i] != '\0' && new[i] != ' ' && new[i] != '\t')
		{
			binary = ft_strcat(binary, "11");
			j += 2;
		}
		if (new[i] != '\0')
			i++;
	}
	while (j < 8)
	{
		binary[j] = '0';
		j++;
	}
	binary[j] = '\0';
	free(new);
	binary = conv_hex(binary);
	return (binary);
}

char		*conv_hex(char *binary)
{
	char	*res;
	char	*tmp;
	int		i;
	int		j;
	int		reste;

	i = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * 5)))
		return (NULL);
	if (!(res = (char *)malloc(sizeof(char) * 5)))
		return (NULL);
	j = binary_to_decimal(binary);
	if (j == 0)
	{
		res = ft_strdup("0x00");
		return (res);
	}
	while (j > 0)
	{
		if (j < 16)
		{
			reste = j;
			j = 0;
		}
		else
		{
			reste = j % 16;
			j /= 16;
		}
		if (reste > 9)
			tmp[i] = reste - 10 + 'a';
		else
			tmp[i] = reste + 48;
		i++;
	}
	tmp[i] = '\0';
	i--;
	res[0] = '0';
	res[1] = 'x';
	j = 2;
	if (ft_strlen(tmp) == 1)
	{
		res[2] = '0';
		j = 3;
	}
	while (i >= 0)
	{
		res[j] = tmp[i];
		i--;
		j++;
	}
	res[j] = '\0';
	free(tmp);
	if (ft_strcmp(res, "0x") == 0)
		res = ft_strdup("0x00");
	return (res);
}
