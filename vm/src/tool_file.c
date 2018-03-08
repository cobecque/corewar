/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:06:02 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/08 15:07:58 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int			string_is_digit(char *str)
{
	while (*str != '\0')
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

t_process	*sound_and_reset(t_process *pro, t_vm *vm, int truc)
{
	if (truc == 1 && vm->arg.sdl == 1 && vm->arg.music == 1)
		system("afplay sound_bank/wilhelm.mp3");
	pro = re_init_live(vm->start_l, vm);
	return (pro);
}

void		print_dead(t_vm *vm, t_process *cpy, int ctd, int cycle)
{
	int		bol;

	bol = 0;
	if (cpy->last_live[0] == 0)
		bol = 1;
	if (vm->arg.ver_num.de == 1)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				cpy->number, cycle - bol - cpy->last_live[0], ctd);
}

int			error_nb_champ(t_vm data, int *fd)
{
	int			i;
	int			tab[4];

	i = 0;
	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 0;
	if (data.arg.n_o == 1)
	{
		while (i < fd[0] - 1)
		{
			if (data.arg.n[i] > 4 || data.arg.n[i] < 1)
				return (3);
			tab[data.arg.n[i] - 1]++;
			if (tab[data.arg.n[i] - 1] > 1)
				return (3);
			i++;
		}
		if ((tab[0] == 0 && tab[1] != 0) || (tab[1] == 0 && tab[2] != 0) ||
				(tab[2] == 0 && tab[3] != 0))
			return (3);
	}
	return (0);
}

int			check_error(t_vm data)
{
	if (data.error == 1)
		return (1);
	if (data.error == 0)
		return (0);
	return (1);
}
