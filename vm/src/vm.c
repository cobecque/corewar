/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 07:22:21 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/06 19:57:45 by cobecque         ###   ########.fr       */
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
		new->val[i] = 0;
	}
	new->val[1] = (unsigned int)nb;
	//reg_write(new, (unsigned int)nb + 1, 1, 4);
	new->reg[1][0] = 255;
	new->reg[1][1] = 255;
	new->reg[1][2] = 255;
	new->reg[1][3] = 255 - nb + 1;
	begin = srt;
	new->pc = NULL;
	new->ins = NULL;
	new->carry = 0;
	new->live = 0;
	new->last_live[0] = 0;
	new->last_live[1] = 0;
	new->start_cycle = -1;
	new->number = nb;
	new->champ = nb;
	new->seek = 0;
	new->line = -1;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		new->live_champ[i] = 0;
		i++;
	}
	new->next = NULL;
	new->pre = NULL;
	if (!srt)
		return (new);
	while (srt->next != NULL)
		srt = srt->next;
	srt->next = new;
	new->pre = srt;
	return (begin);
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
	//ft_printf("Inctroducing contestants...\n");
	while (j < data.nb_pros)
	{
	//	ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", data.play[j].nb, data.play[j].len, data.play[j].name, data.play[j].comment);
		j++;
	}
	while (i < data.nb_pros)
	{
		ret = add_new_process(ret, i + 1);
		if (cpy == NULL)
			cpy = ret;
		else
			cpy = cpy->next;
		data = input_data(data, i + 1, &(cpy->pc));
		i++;
	}
	data.ctd = CYCLE_TO_DIE;
	i = cycle_gestion(data, ret);
	if (i != -1)
		ft_printf("Contestant %d, \"%s\", has won !\n", i, data.play[i - 1].name);
}
