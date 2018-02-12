/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 01:54:32 by cobecque          #+#    #+#             */
/*   Updated: 2018/02/12 05:22:24 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_sep(char *s, int i, int *count)
{
	if (s[i] == ' ' || s[i] == '\t')
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (s[i] != '\0')
			*count += 1;
		i--;
	}
	return (i);
}

char		**ft_cut(char *s, char c)
{
	char	**tab;
	int		i;
	int		count;
	int		let;
	int		j;
	int		tmp;

	i = 0;
	tmp = 0;
	count = 0;
	c = 'a';
	if (s)
	{
		while (s[i] != '\0')
		{
			i = ft_sep(s, i, &count);
			i++;
		}
		if (count == 0 && s[i - 1])
			count = 1;
		else
			count++;
		if (!(tab = (char **)malloc(sizeof(char *) * (count + 1))))
			return (NULL);
		j = 0;
		i = 0;
		let = 0;
		while (j < count)
		{
			let = 0;
			while (s[i] != '\0')
			{
				if (s[i] == ' ' || s[i] == '\t')
				{
					while (s[i] == ' ' || s[i] == '\t')
						i++;
					j++;
					break ;
				}
				else
				{
					if (s[i] != ',')
						let++;
					i++;
				}
			}
			if (s[i] == '\0')
				j++;
			tab[j - 1] = ft_strsub(s, tmp, let);
			tmp = i;
		}
		tab[count] = NULL;
		return (tab);
	}
	return (NULL);
}
