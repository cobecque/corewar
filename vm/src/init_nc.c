/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_nc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 01:22:07 by cobecque          #+#    #+#             */
/*   Updated: 2018/03/05 06:01:04 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void			ft_init_c(void)
{
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
}

void			ft_param_ncurses(void)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	ft_init_c();
}

void			ft_init_game(t_process *pro, WINDOW *game, t_vm vm)
{
	int		i;
	int		y;
	int		p;

	i = 0;
	p = 0;
	y = 1;
	while (i < 64)
	{
		get_col(pro, vm, y, &p);
		i++;
		y++;
	}
	attron(COLOR_PAIR(5));
	wrefresh(game);
}

void			ft_init_ncurses(t_process *pro, t_vm vm)
{
	WINDOW	*menu;
	WINDOW	*game;

	ft_param_ncurses();
	menu = subwin(stdscr, 66, 50, 0, 256);
	game = subwin(stdscr, 66, 257, 0, 0);
	box(menu, ACS_VLINE, ACS_HLINE);
	box(game, ACS_VLINE, ACS_HLINE);
	ft_menu(menu, &vm, vm.alive, pro);
	ft_init_game(pro, game, vm);
	wrefresh(game);
	wrefresh(menu);
	move(3, 259);
	printw("Cycles/second : %d", SPEED);
	move(1, 275);
	printw("*PAUSED");
	while (1)
		if (getch() == 32)
			break ;
	move(1, 275);
	printw("*PLAYED");
	wrefresh(menu);
	nodelay(stdscr, TRUE);
	free(menu);
	free(game);
}

void			ft_quit_ncurses(void)
{
	while (1)
	{
		if (getch() == 27)
		{
			endwin();
			kill(0, SIGKILL);
			break ;
		}
	}
}
