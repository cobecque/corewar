/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 07:22:21 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/14 19:27:31 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void		*malloc_vm(void)
{
	void	*addr;

	if (!(addr = ft_memalloc(MEM_SIZE)))
		return (NULL);
	ft_printf("\t\t\t-->LA VRAIE ADDRESSE %ld\n", addr);
	return (addr);
}

t_vm		input_data(t_vm data, int nb, void **pc_adr)
{
	int		i;
	char	*base_addr;

	i = 0;
	if (data.nb_pros != nb)
		base_addr = data.addr + MEM_SIZE / data.nb_pros * (data.nb_pros - nb);
	else
		base_addr = data.addr;
	*pc_adr = (void *)base_addr;
	while (i < data.play[nb - 1].len)
	{
		*(base_addr + i) = data.play[nb - 1].code[i];
		i++;
	}
	return (data);
}

t_process	*add_new_process(t_process *srt, int nb)
{
	int			i;
	int			j;
	t_process	*new;
	t_process	*begin;

	i = 0;
	if (!(new = (t_process *)malloc(sizeof(t_process))))
		return (NULL);
	while (i < REG_NUMBER)
	{
		j = 0;
		while (j < REG_SIZE)
		{
			new->reg[i][j] = 0;
			j++;
		}
		i++;
	}
	begin = srt;
	new->pc = NULL;
	new->carry = 0;
	new->live = 0;
	new->number = nb;
	new->next = NULL;
	if (!srt)
		return (new);
	while (srt->next != NULL)
		srt = srt->next;
	srt->next = new;
	return (begin);
}

void		vm_stuff(t_vm data)
{
	int			i;
	t_process	*ret;

	i = 0;
	ret = NULL;
	if (!(data.addr = malloc_vm()))
		exit(-1);
	while (i < data.nb_pros)
	{
		ret = add_new_process(ret, i);
		data = input_data(data, i + 1, &(ret->pc));
		ft_printf("\t\t\t-->ICI L'ADDRESSE VAUT %ld pour %ld<--\n", ret->pc, data.addr);
		i++;
	}
}
