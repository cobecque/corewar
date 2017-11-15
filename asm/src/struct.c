/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 15:49:00 by cobecque          #+#    #+#             */
/*   Updated: 2017/11/15 14:11:12 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_file		*init_file(t_file *file, char *line)
{
	t_file	*tmp;
	t_file	*new;

	tmp = file;
	if (!(new = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	if (line)
		new->line = ft_strdup(line);
	else
		new->line = NULL;
	new->code = NULL;
	new->label = NULL;
	if (!(new->param = (char **)malloc(sizeof(char *) * 4)))
		return (NULL);
	new->param[0] = NULL;
	new->param[1] = NULL;
	new->param[2] = NULL;
	new->param[3] = NULL;
	new->inst = NULL;
	new->binair = NULL;
	new->nb = 0;
	new->next = NULL;
	if (!tmp)
		return (new);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (file);
}
