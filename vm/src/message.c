/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 04:04:15 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/24 15:41:54 by rostroh          ###   ########.fr       */
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
		ft_printf("Usage: ./corewar [-dump N, -end N, -v N, -SDL, -help]");
		ft_printf("<champion1.cor> <...>\nMax 4 champions\n\tUse ./corewar");
		ft_printf("-help for more info\n");
	}
	if (nb == 2)
	{
		ft_printf("--Help Corewar--\n\t-dump N\t\t: Dumps memory after N");
		ft_printf("cycles then exits\n\t-end N\t\t: End corewar after N");
		ft_printf("cycles then exits\n\t-v N\t\t: Verbosity levels, can be");
		ft_printf("added together to enable several:\n\t\t\t\t- 0 : Show only");
		ft_printf(" essentials\n\t\t\t\t- 1 : Show lives\n\t\t\t\t- 2 : Show");
		ft_printf("cycles\n\t\t\t\t- 4 : Show operations (Params are NOT ");
		ft_printf("litteral ...)\n\t\t\t\t- 8 : Show death\n\t\t\t\t- 16 : ");
		ft_printf("Show PC movements (except for jumps)\n\t-SDL\t\t: Prints ");
		ft_printf("memory cycle by cycle with an SDL viewer\n");
	}
}
