/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 04:04:15 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/09 15:47:02 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void			message_champ(int nb, int i, t_champ champ)
{
	if (nb == 1)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", \
				champ.nb, champ.len, champ.name, champ.comment);
	if (nb == 2)
		ft_printf("Contestant %d, \"%s\", has won !\n", i, champ.name);
}

void			message(int nb)
{
	if (nb == 1)
	{
		ft_printf("Usage: ./corewar [-dump N, -end N, -v N, -nc] -n N");
		ft_printf(" <champion1.cor> <...>\nMax 4 champions\n\tUse ./corewar");
		ft_printf("-help for more info\n");
	}
	if (nb == 2)
	{
		ft_printf("--Help Corewar--\n\t-a\t\t: Prints output from \"aff\" ");
		ft_printf("(Default is to hide it)\n\t-dump N\t\t: Dumps memory after");
		ft_printf(" N cycles then exits\n\t-end  N\t\t: Ends corewar after N ");
		ft_printf("cycles then exits\n\t-n    N\t\t: Specifies the placement ");
		ft_printf("of each champ (1 to put on top) (2 champions can't ");
		ft_printf("have the same number)\n\t-v    N\t\t: Verbosity levels, ");
		ft_printf("can be added together to enable several:\n\t\t\t\t- 0 : ");
		ft_printf("Show only essentials\n\t\t\t\t- 1 : Show lives\n\t\t\t\t- ");
		ft_printf("2 : Show cycles\n\t\t\t\t- 4 : Show operations (Params are");
		ft_printf(" NOT litteral ...)\n\t\t\t\t- 8 : Show death\n\t\t\t\t- 16");
		ft_printf(" : Show PC movements (except for jumps)\n\t-nc\t\t: Prints");
		ft_printf(" memory cycle by cycle with an ncurses viewer\n");
	}
}
