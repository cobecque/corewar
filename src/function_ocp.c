/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_ocp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 18:00:37 by cobecque          #+#    #+#             */
/*   Updated: 2017/10/21 16:47:11 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char		*ft_calc_ocp(char *line)
{
	char	*binary;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!(binary = (char *)malloc(sizeof(char) * 9)))
		return (NULL);
	*binary = '\0';
	while (line[i] != '\0')
	{
		if (j != 0 && line[i - 1] != ',')
		{
			while (line[i] != '\0' && line[i] != ',')
				i++;
			i++;
		}
		if (line[i] == 'r')
		{
			binary = ft_strcat(binary, "01");
			j += 2;
		}
		else if (line[i] == '%')
		{
			binary = ft_strcat(binary, "10");
			j += 2;
		}
		else if (line[i] != ',' && line[i] != '\n' && line[i] != '\0')
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
	if (ft_strcmp(res, "0x") == 0)
		res = ft_strdup("0x00");
	ft_printf("hex = %s\n", res);
	return (res);
}
