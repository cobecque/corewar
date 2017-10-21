/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 15:49:00 by cobecque          #+#    #+#             */
/*   Updated: 2017/10/20 19:40:39 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_file		*init_file(t_file *file, char *line)
{
	t_file	*tmp;
	t_file	*new;

	tmp = file;
	if (!(new = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	new->line = ft_strdup(line);
	new->code = NULL;
	new->label = NULL;
	new->inst = NULL;
	new->next = NULL;
	if (!tmp)
		return (new);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (file);
}
