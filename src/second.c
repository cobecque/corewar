/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 00:15:25 by cobecque          #+#    #+#             */
/*   Updated: 2017/10/14 02:45:14 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	*ft_calcul(char *line, t_op op_tab)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(new = (char *)malloc(sizeof(char) * ft_strlen(line))))
		return (NULL);
	while (i < 17)
	{
		if (ft_strstr(line, op_tab[i].line))
	}
}
