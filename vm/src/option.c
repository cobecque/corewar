/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 05:26:30 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/11 06:27:22 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void			message(int nb)
{
	if (nb == 1)
		ft_printf("Usage: ./corewar [-dump N, -end N, -v N, -SDL, -help] <champ\
				ion1.cor> <...>\nMax 4 champions\n\tUse ./corewar -help for mor\
				e info\n");
	if (nb == 2)
		ft_printf("--Help Corewar--\n\t-dump N\t\t: Dumps memory after N cycles\
				then exits\n\t-end N\t\t: End corewar after N cycles then exits\
				\n\t-v N\t\t: Verbosity levels, can be added together to enable\
				several:\n\t\t\t\t- 0 : Show only essentials\n\t\t\t\t- 1 : Sho\
				w lives\n\t\t\t\t- 2 : Show cycles\n\t\t\t\t- 4 : Show operatio\
				ns (Params are NOT litteral ...)\n\t\t\t\t- 8 : Show death\n\t\
				\t\t\t- 16 : Show PC movements (except for jumps)\n\t-SDL\t\t: \
				Prints memory cycle by cycle with an SDL viewer\n");
}

t_pam			get_dump_help(t_pam pam, int argc, char **argv, int i)
{
	if (ft_strcmp(argv[i], "-dump") == 0)
	{
		pam.nb++;
		if (i + 1 < argc)
		{
			pam.nb++;
			if (string_is_digit(argv[i + 1]) == 0)
				pam.patern = ft_strdup("option -dump have incorrect parameter");
			else
				pam.dump = ft_atoi(argv[i + 1]);
		}
		else
			pam.patern = ft_strdup("option -dump have no parameter");
	}
	if (ft_strcmp(argv[i], "-help") == 0)
	{
		message(2);
		pam.patern = ft_strdup("Help");
	}
	return (pam);
}

t_pam			get_end_sdl(t_pam pam, int argc, char **argv, int i)
{
	if (ft_strcmp(argv[i], "-end") == 0)
	{
		pam.nb++;
		if (i + 1 < argc)
		{
			pam.nb++;
			if (string_is_digit(argv[i + 1]) == 0)
				pam.patern = ft_strdup("option -end have incorrect parameter");
			else
				pam.end = ft_atoi(argv[i + 1]);
		}
		else
			pam.patern = ft_strdup("option -end  have no parameter");
	}
	if (ft_strcmp(argv[i], "-SDL") == 0)
		pam.sdl = 1;
	return (pam);
}

t_pam			get_v(t_pam pam, int argc, char **argv, int i)
{
	if (ft_strcmp(argv[i], "-v") == 0)
	{
		pam.nb++;
		if (i + 1 < argc)
		{
			pam.nb++;
			if (string_is_digit(argv[i + 1]) == 0)
				pam.patern = ft_strdup("option -v have incorrect parameter");
			else
			{
				pam.ver = ft_atoi(argv[i + 1]);
				pam.ver_num = get_verbose(pam.ver);
			}
		}
		else
			pam.patern = ft_strdup("option -v have no parameter");
	}
	return (pam);
}

t_pam			get_option(int argc, char **argv)
{
	int			i;
	t_pam		pam;

	i = 1;
	pam.nb = 0;
	pam.end = -1;
	pam.help = 0;
	pam.sdl = 0;
	pam.dump = -1;
	pam.ver = -1;
	pam.error = 0;
	pam.patern = NULL;
	while (i < argc)
	{
		pam = get_dump_help(pam, argc, argv, i);
		pam = get_end_sdl(pam, argc, argv, i);
		pam = get_v(pam, argc, argv, i);
		if (pam.patern != NULL)
			break ;
		i++;
	}
	return (pam);
}
