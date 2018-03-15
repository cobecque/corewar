/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:13:56 by cobecque          #+#    #+#             */
/*   Updated: 2018/03/15 20:49:15 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_close_error(int fd)
{
	if (close(fd) == -1)
		ft_printf("Error : Close file\n");
}

int			is_not_label(char *label, t_inst *ins)
{
	t_inst	*tmp;

	tmp = ins;
	while (tmp != NULL)
	{
		if (tmp->label != NULL && ft_strcmp(tmp->label, label) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int			is_label_char(char c)
{
	int		i;

	i = 0;
	while (LABEL_CHARS[i] != '\0')
	{
		if (c == LABEL_CHARS[i])
			return (1);
		i++;
	}
	return (0);
}

int			is_true_label(char *l)
{
	int		i;

	i = 0;
	while (l[i] != '\0')
	{
		if (l[i] == ':')
			return (1);
		if (is_label_char(l[i]) == 0)
			return (0);
		i++;
	}
	return (0);
}

int			is_not_value(char *par, char *tmp)
{
	int		i;

	i = 0;
	if (par[0] == '%' && par[1] == ':')
		return (0);
	if (par[0] == ':')
		return (0);
	if (tmp[0] == '-')
		i++;
	while (tmp[i] != '\0')
	{
		if (tmp[i] > '9' || tmp[i] < '0')
			return (1);
		i++;
	}
	return (0);
}
