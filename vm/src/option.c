/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 05:26:30 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/01 17:34:05 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_pam			get_music(t_pam pam, char **argv, int i)
{
	if (ft_strcmp(argv[i], "-music") == 0)
	{
		pam.nb++;
		pam.music = 1;
	}
	return (pam);
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
	if (ft_strcmp(argv[i], "-nc") == 0)
	{
		pam.nb++;
		pam.sdl = 1;
	}
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
	pam.sdl = 0;
	pam.end = -1;
	pam.help = 0;
	pam.ver = -1;
	pam.dump = -1;
	pam.error = 0;
	pam.music = 0;
	pam.patern = NULL;
	while (i < argc)
	{
		pam = get_dump_help(pam, argc, argv, i);
		pam = get_end_sdl(pam, argc, argv, i);
		pam = get_v(pam, argc, argv, i);
		pam = get_music(pam, argv, i);
		if (pam.patern != NULL)
			break ;
		i++;
	}
	return (pam);
}
