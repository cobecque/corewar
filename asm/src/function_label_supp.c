/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_label_supp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:36:23 by cobecque          #+#    #+#             */
/*   Updated: 2017/11/15 15:41:11 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			is_end_label(t_file *tmp, char *label, int *size)
{
	char	*new;

	if (tmp->label != NULL && label != NULL)
	{
		if (ft_strcmp(label, tmp->label) == 0)
		{
			if (tmp->code != NULL)
			{
				new = ft_strdup(tmp->code);
				*size += octet_on_line(new);
			}
			return (1);
		}
	}
	return (-1);
}
