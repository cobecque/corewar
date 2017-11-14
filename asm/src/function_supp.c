/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_supp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 16:30:54 by cobecque          #+#    #+#             */
/*   Updated: 2017/10/26 01:50:43 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char		*search_instruction(char *line, char *label, t_file *file)
{
	char	*op_code;
	int		i;
	int		j;

	i = 0;
	op_code = ft_strdup(line);
	if (label != NULL && line != NULL)
		op_code = ft_strsub(line, ft_strlen(label) + 1, ft_strlen(line) - ft_strlen(label) - 1);
	while (op_code[i] != '\0' && (op_code[i] == ' ' || op_code[i] == '\t'))
		i++;
	j = i;
	while (op_code[i] != '\0' && op_code[i] != ' ' && op_code[i] != '\t')
		i++;
	op_code = ft_strsub(op_code, j, i - j);
	if (op_code == NULL || op_code[0] == '\0')
		return (NULL);
	file->inst = ft_strdup(op_code);
	i = 0;
	while (i < 17)
	{
		if (op_code != NULL && g_op_tab[i].name != NULL && ft_strcmp(op_code, g_op_tab[i].name) == 0)
		{
			op_code = ft_conv_op_code(g_op_tab[i].op_code);
			break;
		}
		i++;
	}
	return (op_code);
}

char		*cut_line(char *line, char *label)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	new = ft_strdup(line);
	if (label != NULL)
		new = ft_strsub(new, ft_strlen(label) + 1, ft_strlen(new) * ft_strlen(label) - 1);
	while (new[i] != '\0' && (new[i] == ' ' || new[i] == '\t'))
		i++;
	j = i;
	while (new[i] != '\0' && new[i] != ' ' && new[i] != '\t')
		i++;
	while (new[i] != '\0' && (new[i] == ' ' || new[i] == '\t'))
		i++;
	new = ft_strsub(new, i, ft_strlen(new) - i);
	return (new);
}

char		*ft_conv_op_code(int op_code)
{
	char	*tmp;
	int		i;
	int		reste;

	if (!(tmp = (char *)malloc(sizeof(char) * 5)))
		return (NULL);
	i = 0;
	while (op_code > 0)
	{
		if (op_code < 16)
		{
			reste = op_code;
			op_code = 0;
		}
		else
		{
			reste = op_code % 16;
			op_code /= 16;
		}
		if (reste > 9)
			tmp[i] = reste - 10 + 'a';
		else
			tmp[i] = reste + 48;
		i++;
	}
	tmp[i] = '\0';
	return (ft_hex(tmp, i - 1));
}

char		*ft_hex(char *tmp, int j)
{
	int		i;
	char	*res;

	if (!(res = (char *)malloc(sizeof(char) * 5)))
		return (NULL);
	i = 2;
	res[0] = '0';
	res[1] = 'X';
	if (ft_strlen(tmp) == 1)
	{
		res[2] = '0';
		i = 3;
	}
	while (j >= 0)
	{
		res[i] = tmp[j];
		i++;
		j--;
	}
	res[i] = '\0';
	if (ft_strcmp(res, "0x") == 0)
		res = ft_strdup("0x00");
	return(res);
}
