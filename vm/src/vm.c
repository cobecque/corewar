/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 07:22:21 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/26 15:40:59 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

char		*malloc_vm(void)
{
	int		i;
	char	*addr;

	i = 0;
	if (!(addr = (char*)malloc(sizeof(char) * MEM_SIZE)))
		return (NULL);
	while (i < MEM_SIZE)
	{
		addr[i] = 0;
		i++;
	}
	return (addr);
}

t_vm		input_data(t_vm data, int nb, char **pc_adr)
{
	int		i;
	char	*base_addr;

	i = 0;
	if (nb == 1)
		base_addr = data.addr;
	else
		base_addr = data.addr + MEM_SIZE / data.nb_pros * (nb - 1);
	*pc_adr = base_addr;
	while (i < data.play[nb - 1].len/* - 4 * nb*/)
	{
		*(base_addr + i) = data.play[nb - 1].code[i];
		data.color[(int)(base_addr - data.addr) + i] = nb;
		i++;
	}
	return (data);
}

void		gates_are_open(t_vm data, t_process *lst)
{
	int			winner;
	t_cycle		cy;

	cy = init_cycle();
	data.ctd = CYCLE_TO_DIE;
	data.cycle = 1;
	winner = cycle_gestion(data, lst, cy);
	ft_printf("%d\n", winner);
	if (winner != -1 && winner != 0)
		message_champ(2, winner, data.play[winner - 1]);
}

void		vm_stuff(t_vm data)
{
	int			i;
	int			j;
	t_process	*ret;
	t_process	*cpy;

	i = 0;
	j = 0;
	ret = NULL;
	cpy = NULL;
	if (!(data.addr = malloc_vm()))
		exit(-1);
	ft_printf("Introducing contestants...\n");
	while (i < data.nb_pros)
	{
		data.play[i].r1 = -data.play[i].nb;
		message_champ(1, 0, data.play[i]);
		ret = add_new_process(ret, i + 1);
		if (cpy == NULL)
			cpy = ret;
		else
			cpy = cpy->next;
		data = input_data(data, i + 1, &(cpy->pc));
		i++;
	}
	gates_are_open(data, ret);
/*	ft_printf("-->%d<--\n", data.color[1602]);
	i = 0;
	j = 0;
	ft_printf("         ");
	while (i < 64)
	{
		if (i < 10)
			ft_putchar('0');
		ft_printf("%d ", i);
		i++;
	}
	ft_putstr("\n\n");//
	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0 && i != 0)
			ft_putchar('\n');
		if (i % 64 == 0)
		{
			ft_putstr("0x0");
			if (j < 16)
				ft_putchar('0');
			ft_printf("%x0 : ", j);
			j += 4;
		}
		ft_printf("0%d ", data.color[i]);
		i++;
	}
	ft_putstr("\n\n");*/
}
