/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:56:34 by cobecque          #+#    #+#             */
/*   Updated: 2018/03/08 12:32:30 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void			fill_inf_v(t_process *pro, t_vm *vm)
{
	t_process	*tmp;
	int			i;

	tmp = pro;
	while (tmp != NULL)
	{
		i = 0;
		while (i < vm->nb_pros)
		{
			if (tmp->last_live[1] == i + 1 && tmp->live != -1)
			{
				if (vm->inf_v.last_live[i] < tmp->last_live[0])
				{
					vm->inf_v.nb_live[i]++;
					vm->inf_v.last_live[i] = tmp->last_live[0];
				}
			}
			if (tmp->champ == i + 1 && tmp->live != -1)
				vm->inf_v.nb_pro_c[i]++;
			i++;
		}
		tmp = tmp->next;
	}
}

void			player_info(t_vm *vm, int *len, int *x, WINDOW *menu)
{
	while (*len < vm->nb_pros)
	{
		attron(COLOR_PAIR(vm->play[*len].nb));
		move(*x, 259);
		clrtoeol();
		printw("PLAYER -%d :", *len + 1);
		move(*x, 272);
		clrtoeol();
		printw("%s", vm->play[*len].name);
		move(*x + 1, 260);
		clrtoeol();
		printw("-Last live cycle : %d", vm->inf_v.last_live[*len]);
		move(*x + 2, 260);
		clrtoeol();
		printw("-Live in current period : %d", vm->inf_v.nb_live[*len]);
		move(*x + 3, 260);
		clrtoeol();
		printw("-Process number : %d", vm->inf_v.nb_pro_c[*len]);
		(*len)++;
		*x += 5;
		box(menu, ACS_VLINE, ACS_HLINE);
	}
}

void			menu_def(WINDOW *menu, t_vm *vm, int x)
{
	attron(COLOR_PAIR(5));
	move(x, 259);
	clrtoeol();
	printw("Cycle to die : %d\0\0\0", vm->ctd);
	box(menu, ACS_VLINE, ACS_HLINE);
	move(x + 2, 259);
	printw("Cycle delta : %d", CYCLE_DELTA);
	move(x + 4, 259);
	printw("Nbr live : %d", NBR_LIVE);
	move(x + 6, 259);
	printw("Max checks : %d", MAX_CHECK);
}

void			ft_menu(WINDOW *menu, t_vm *vm, int nb, t_process *pro)
{
	int		len;
	int		x;
	int		y;

	len = 0;
	x = 9;
	fill_inf_v(pro, vm);
	move(5, 259);
	clrtoeol();
	printw("Cycle : %d", vm->cycle);
	move(7, 259);
	clrtoeol();
	printw("Process : %d", nb);
	player_info(vm, &len, &x, menu);
	menu_def(menu, vm, x);
	y = 0;
	while (y < vm->nb_pros)
	{
		vm->inf_v.nb_pro_c[y] = 0;
		y++;
	}
}

t_vm			ft_ncurses(t_process *pro, t_vm vm)
{
	struct timespec		speed;
	WINDOW				*menu;
	WINDOW				*game;
	int					ch;

	ch = 0;
	menu = subwin(stdscr, 66, 50, 0, 256);
	game = subwin(stdscr, 66, 257, 0, 0);
	box(menu, ACS_VLINE, ACS_HLINE);
	box(game, ACS_VLINE, ACS_HLINE);
	ft_menu(menu, &vm, vm.alive, pro);
	ft_init_game(pro, game, vm);
	ch = getch();
	ft_catch_event(menu, game, ch);
	move(3, 259);
	clrtoeol();
	printw("Cycles/second : %d", SPEED);
	box(menu, ACS_VLINE, ACS_HLINE);
	wrefresh(menu);
	free(menu);
	free(game);
	speed.tv_sec = 0;
	speed.tv_nsec = 1000000000 / SPEED;
	return (vm);
}
