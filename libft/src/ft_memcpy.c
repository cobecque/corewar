/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 18:18:36 by cobecque          #+#    #+#             */
/*   Updated: 2016/11/29 00:44:10 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*curr1;
	unsigned char	*curr2;

	i = 0;
	curr1 = (unsigned char *)src;
	curr2 = (unsigned char *)dst;
	while (i < n)
	{
		*curr2 = *curr1;
		i++;
		curr1++;
		curr2++;
	}
	return (dst);
}
