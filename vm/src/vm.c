/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 07:22:21 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/02 19:23:16 by rostroh          ###   ########.fr       */
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

char		*get_afplay(t_vm vm)
{
	int			i;

	i = 0;
	while (i < vm.nb_pros)
	{
		if (ft_strcmp(vm.play[i].name, "Yandere-chan") == 0)
			return ("afplay ./sound_bank/yuki.mp3");
		i++;
	}
	if (vm.nb_pros == 1)
		return ("afplay ./sound_bank/arcade.mp3");
	if (vm.nb_pros == 2)
		return ("afplay ./sound_bank/red_theme.mp3");
	if (vm.nb_pros == 3)
		return ("afplay ./sound_bank/necrodancer.mp3");
	if (vm.nb_pros == 4)
		return ("afplay ./sound_bank/megalovania.mp3");
	return ("afplay ./sound_bank/ascenseur.mp3");
}

void		play_music(t_vm vm, pid_t son)
{
	char	*to_play;

	to_play = get_afplay(vm);
	while (42)
		system(to_play);
		//system("afplay ./sound_bank/megalovania.mp3");
	kill(son, SIGKILL);
}

void		gates_are_open(t_vm data, t_process *lst)
{
	int			winner;
	t_cycle		cy;
	int			i;
	pid_t		father;

	i = 0;
	father = 0;
	while (i < data.nb_pros)
	{
		data.inf_v.last_live[i] = 0;
		data.inf_v.nb_live[i] = 0;
		data.inf_v.nb_pro_c[i] = 0;
		i++;
	}
	cy = init_cycle();
	data.ctd = CYCLE_TO_DIE;
	data.cycle = 1;
	if (data.arg.sdl == 1)
		ft_init_ncurses(lst, data);
	if (data.arg.music == 1)
		father = fork();
	if (father == 0 && data.arg.music == 1)
		play_music(data, father);
	else
	{
		ft_printf("father %d\n", father);
		winner = cycle_gestion(data, lst, cy);
		if (data.arg.music == 1)
		{
			ft_putstr("Rekt get\n");
			kill(0, SIGKILL);
		}
		if (data.arg.sdl == 1)
			ft_quit_ncurses();
		if (winner != -1 && winner != 0)
			message_champ(2, winner, data.play[winner - 1]);
	}
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
}
