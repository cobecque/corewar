/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_nc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 01:22:31 by cobecque          #+#    #+#             */
/*   Updated: 2018/03/08 10:06:56 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int				check_color(t_vm vm, char *addr)
{
	int		c;

	c = (int)vm.color[(int)addr - (int)vm.addr];
	if (c == 0)
		c = 5;
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

void			get_col(t_process *pro, t_vm vm, int y, int *p)
{
	int		j;
	int		x;

	j = 0;
	x = 1;
	while (j < 64)
	{
		move(y, x);
		attron(COLOR_PAIR(check_color(vm, vm.addr + *p)));
		if (is_pc(vm.addr + *p, pro) == 1)
			attron(A_STANDOUT);
		get_hexa(*(vm.addr + *p), 1);
		attroff(A_STANDOUT);
		x += 4;
		j++;
		(*p)++;
	}
}

void			kill_curse(WINDOW *menu, WINDOW *game, int ch)
{
	if (ch == 27)
	{
		free(menu);
		free(game);
		endwin();
		kill(0, SIGKILL);
		exit(-1);
	}
}

void			ft_catch_event(WINDOW *menu, WINDOW *game, int ch)
{
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
			kill_curse(menu, game, ch);
		}
		move(1, 275);
		printw("*PLAYED");
		wrefresh(menu);
	}
	kill_curse(menu, game, ch);
}
