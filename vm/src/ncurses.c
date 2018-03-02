/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:56:34 by cobecque          #+#    #+#             */
/*   Updated: 2018/03/02 19:23:44 by rostroh          ###   ########.fr       */
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

void			ft_menu(WINDOW *menu, t_vm *vm, int nb, t_process *pro)
{
	int		len;
	int		x;
	int		y;

	len = 0;
	y = 290;
	x = 9;
	fill_inf_v(pro, vm);
	move(5, 259);
	clrtoeol();
	printw("Cycle : %d", vm->cycle);
	move(7, 259);
	clrtoeol();
	printw("Process : %d", nb);
	while (len < vm->nb_pros)
	{
		y = 259;
		attron(COLOR_PAIR(vm->play[len].nb));
		move(x, y);
		clrtoeol();
		printw("PLAYER -%d :", len + 1);
		move(x, y + 12);
		clrtoeol();
		printw("%s", vm->play[len].name);
		move(x + 1, 260);
		clrtoeol();
		printw("-Last live cycle : %d", vm->inf_v.last_live[len]);
		move(x + 2, 260);
		clrtoeol();
		printw("-Live in current period : %d", vm->inf_v.nb_live[len]);
		move(x + 3, 260);
		clrtoeol();
		printw("-Process number : %d", vm->inf_v.nb_pro_c[len]);
		len++;
		x += 5;
		box(menu, ACS_VLINE, ACS_HLINE);
	}
	attron(COLOR_PAIR(5));
	move(x, 259);
	if (vm->ctd == 986 || vm->ctd == 86)
		clrtoeol();
	printw("Cycle to die : %d\0\0\0", vm->ctd);
	box(menu, ACS_VLINE, ACS_HLINE);
	move(x + 2, 259);
	printw("Cycle delta : %d", CYCLE_DELTA);
	move(x + 4, 259);
	printw("Nbr live : %d", NBR_LIVE);
	move(x + 6, 259);
	printw("Max checks : %d", MAX_CHECK);
	y = 41;
	while (y < 65)
	{
		x = 0;
		while (x < 48)
		{
			move(y, 257 + x);
			printw("#");
			x++;
		}
		y += 6;
	}
	move(0, 0);
	wrefresh(menu);
	y = 0;
	while (y < vm->nb_pros)
	{
		vm->inf_v.nb_pro_c[y] = 0;
		y++;
	}
}

int			check_color(t_vm vm, char *addr)
{
	int		c;

	c = (int)vm.color[(int)addr - (int)vm.addr];
	return (c);
}

int				is_pc(char *addr, t_process *pro)
{
	t_process	*tmp;

	tmp = pro;
	while (tmp != NULL)
	{
		if (tmp->pc == addr && tmp->live != -1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void			ft_init_game(t_process *pro, WINDOW *game, t_vm vm)
{
	int		i;
	int		x;
	int		y;
	int		j;
	int		p;
	int		nb;
	int		c;

	i = 0;
	p = 0;
	y = 1;
	nb = 5;
	c = 0;
	while (i < 64)
	{
		j = 0;
		x = 1;
		while (j < 64)
		{
			move(y, x);
			nb = check_color(vm, vm.addr + p);
			if (nb != 0)
				attron(COLOR_PAIR(nb));
			else
				attron(COLOR_PAIR(5));
			if (is_pc(vm.addr + p, pro) == 1)
				attron(A_STANDOUT);
			printw("%s", get_hexa(*(vm.addr + p)));
			attroff(A_STANDOUT);
			x += 4;
			j++;
			p++;
		}
		i++;
		y++;
	}
	attron(COLOR_PAIR(5));
	wrefresh(game);
}

int				ft_nb_pros(t_process *pro)
{
	t_process	*tmp;
	int			i;

	i = 0;
	tmp = pro;
	while (tmp != NULL)
	{
		if (tmp->live != -1)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void			ft_init_ncurses(t_process *pro, t_vm vm)
{
	WINDOW	*menu;
	WINDOW	*game;

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	menu = subwin(stdscr, 66, 50, 0, 256);
	game = subwin(stdscr, 66, 257, 0, 0);
	box(menu, ACS_VLINE, ACS_HLINE);
	box(game, ACS_VLINE, ACS_HLINE);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	ft_menu(menu, &vm, ft_nb_pros(pro), pro);
	ft_init_game(pro, game, vm);
	wrefresh(game);
	wrefresh(menu);
	move(3, 259);
	printw("Cycles/second : %d", 80);
	move(2, 259);
	printw("Limit speed : %d", 100);
	move(1, 275);
	printw("*PAUSED");
	while (1)
	{
		if (getch() == 32)
			break ;
	}
	move(1, 275);
	printw("*PLAYED");
	wrefresh(menu);
	nodelay(stdscr, TRUE);
	free(menu);
	free(game);
}

t_vm			ft_ncurses(t_process *pro, t_vm vm)
{
	WINDOW	*menu;
	WINDOW	*game;
	int		ch;

	ch = 0;
	menu = subwin(stdscr, 66, 50, 0, 256);
	game = subwin(stdscr, 66, 257, 0, 0);
	box(menu, ACS_VLINE, ACS_HLINE);
	box(game, ACS_VLINE, ACS_HLINE);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	ft_menu(menu, &vm, ft_nb_pros(pro), pro);
	ft_init_game(pro, game, vm);
	ch = getch();
	if (ch == 32)
	{
		wrefresh(menu);
		while (1)
		{
			move(1, 275);
			printw("*PAUSED");
			ch = getch();
			if (ch == 32)
				break ;
			if (ch == 27)
			{
				free(menu);
				free(game);
				endwin();
				kill(0, SIGKILL);
				exit(-1);
			}
		}
		move(1, 275);
		printw("*PLAYED");
		wrefresh(menu);
	}
	if (ch == 27)
	{
		free(menu);
		free(game);
		endwin();
		kill(0, SIGKILL);
		exit(-1);
	}
	ch = getch();
	move(3, 259);
	clrtoeol();
	printw("Cycles/second : %d", 80);
	box(menu, ACS_VLINE, ACS_HLINE);
	wrefresh(menu);
	free(menu);
	free(game);
	return (vm);
}

void			ft_quit_ncurses(void)
{
	while (1)
	{
		if (getch() == 27)
		{
			kill(0, SIGKILL);
			break ;
		}
	}
	endwin();
}
