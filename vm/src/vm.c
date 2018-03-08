/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 07:22:21 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/08 09:42:44 by cobecque         ###   ########.fr       */
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
		data.color[(int)(base_addr - data.addr) + i] = nb;
		i++;
	}
	return (data);
}

void		init_visu_info(t_vm *vm, t_cycle *cy)
{
	int			i;

	i = 0;
	while (i < vm->nb_pros)
	{
		vm->inf_v.last_live[i] = 0;
		vm->inf_v.nb_live[i] = 0;
		vm->inf_v.nb_pro_c[i] = 0;
		i++;
	}
	*cy = init_cycle();
	vm->alive = vm->nb_pros;
	vm->number = vm->nb_pros;
	vm->ctd = CYCLE_TO_DIE;
	vm->cycle = 1;
}

void		gates_are_open(t_vm data, t_process *lst)
{
	int			winner;
	t_cycle		cy;
	pid_t		father;

	father = 0;
	init_visu_info(&data, &cy);
	data.start_l = lst;
	if (data.arg.sdl == 1)
		ft_init_ncurses(lst, data);
	if (data.arg.music == 1)
		father = fork();
	if (father == 0 && data.arg.music == 1)
		play_music(data, father);
	else
	{
		winner = cycle_gestion(data, lst, cy);
		if (data.arg.music == 1)
			kill(0, SIGKILL);
		if (data.arg.sdl == 1)
			ft_quit_ncurses(data, winner);
		if (winner != -1 && winner != 0)
			message_champ(2, winner, data.play[winner - 1]);
	}
}

void		vm_stuff(t_vm data)
{
	int			i;
	t_process	*ret;
	t_process	*cpy;

	i = 0;
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
		data.end_l = cpy;
		i++;
	}
	gates_are_open(data, ret);
	free(data.addr);
}
