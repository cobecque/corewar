/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 07:22:21 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/02 06:19:19 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		*malloc_vm(void)
{
	void	*addr;

	if (!(addr = ft_memalloc(MEM_SIZE)))
		return (NULL);
	return (addr);
}

t_vm		input_data(t_vm data, int nb)
{
	int		i;
	char	*base_addr;

	i = 0;
//	ft_printf("%d et %d\n", data.play[nb - 1].len, nb);
	if (data.nb_pros != nb)
		base_addr = data.addr + MEM_SIZE / data.nb_pros * (data.nb_pros - nb);
	else
		base_addr = data.addr;
	//ft_printf(/*"max = %d et nb = %d\n*/"vm = %d base = %d\n\n", /*max, nb,*/ data.addr, base_addr);
	//ft_printf("\n\n");
	while (i < data.play[nb - 1].len)
	{
		*(base_addr + i) = data.play[nb - 1].code[i];
	//	ft_printf("%d ", *(base_addr + i));
		i++;
	}
	return (data);
}

void		vm_stuff(t_vm data)
{
	int		i;

	i = 0;
//	ft_putchar('a');
	if (!(data.addr = malloc_vm()))
		exit(-1);

	while (i < data.nb_pros)
	{
	//	ft_printf("champion: %s\n", data.play[i].name);
		input_data(data, i + 1);
		i++;
	}
	//manage(data);
}
