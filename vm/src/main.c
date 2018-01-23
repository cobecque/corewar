/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 17:29:39 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/23 20:32:41 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "libft.h"
#include "ft_printf.h"

int			check_error(int err)
{
	if (err == 0)
		return (0);
	if (err == 1)
		 ft_putstr("Champion too big\n");
	return (1);
}

int			*get_fd(int argc, char **argv, int arg)
{
	int			i;
	int			*fd_tab;

	i = 1;
	if (!(fd_tab = (int *)malloc(sizeof(int) * argc - arg)))
		return (NULL);
	fd_tab[0] = argc - arg;
	while (i < argc - arg)
	{
		if ((fd_tab[i] = open(argv[i + arg], O_RDONLY, 0)) <= 0)
			return (NULL);
	//	ft_printf("%s pour i = %d et val = %d\n", argv[i + arg], i, i + arg);
		i++;
	}
	return (fd_tab);
}

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

t_pam		get_option(int argc, char **argv)
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
		if (ft_strcmp(argv[i], "-dump") == 0)
		{
			i++;
			pam.nb++;
			if (i < argc)
			{
				pam.nb++;
				if (string_is_digit(argv[i]) == 0)
					pam.patern = ft_strdup("dump's parameters.");
				else
					pam.dump = ft_atoi(argv[i]);
			}
			else
				pam.patern = ft_strdup("dump's parameters.");
		}
		if (ft_strcmp(argv[i], "-help") == 0)
		{
			ft_printf("--Help Corewar--\n\t-dump N\t\t: Dumps memory after N cycles then exits\n\t-end N\t\t: End corewar after N cycles then exits\n\t-v N\t\t: Verbosity levels, can be added together to enable several:\n\t\t\t\t- 0 : Show only essentials\n\t\t\t\t- 1 : Show lives\n\t\t\t\t- 2 : Show cycles\n\t\t\t\t- 4 : Show operations (Params are NOT litteral ...)\n\t\t\t\t- 8 : Show death\n\t\t\t\t- 16 : Show PC movements (except for jumps)\n\t-SDL\t\t: Prints memory cycle by cycle with an SDL viewer\n");
			pam.patern = ft_strdup("Help");
		}
		if (ft_strcmp(argv[i], "-end") == 0)
		{
			i++;
			pam.nb++;
			if (i < argc)
			{
				pam.nb++;
				if (string_is_digit(argv[i]) == 0)
					pam.patern = ft_strdup("end's parameters.");
				else
					pam.end = ft_atoi(argv[i]);
			}
			else
				pam.patern = ft_strdup("end's parameters.");
		}
		if (ft_strcmp(argv[i], "-SDL") == 0)
			pam.sdl = 1;
		if (ft_strcmp(argv[i], "-v") == 0)
		{
			i++;
			pam.nb++;
			if (i < argc)
			{
				pam.nb++;
				if (string_is_digit(argv[i]) == 0)
					pam.patern = ft_strdup("end's parameters.");
				else
				{
					pam.ver = ft_atoi(argv[i]);
					pam.ver_num = get_verbose(pam.ver);
				}
			}
			else
				pam.patern = ft_strdup("end's parameters.");
		//	ft_printf("%d\n", pam.ver);
		}
		if (pam.patern != NULL)
			break ;
		i++;
	}
	return (pam);
}

int			main(int argc, char **argv)
{
	int			i;
	int			*fd;
	t_pam		arg;
	t_vm		data;
	//t_inf		**ret;

	i = 0;
	if (argc == 1)
		ft_printf("Usage: ./corewar [-dump N, -end N, -v N, -SDL, -help] <champion1.cor> <...>\nMax 4 champions\n\tUse ./corewar -help for more info\n");
	else
	{
		arg = get_option(argc, argv);
		if (arg.patern != NULL)
		{
			if (ft_strcmp(arg.patern, "Help") != 0)
				ft_printf("Bad patern at %s\n", arg.patern);
			return (0);
		}
		if ((fd = get_fd(argc, argv, arg.nb)) == NULL)
		{
			ft_printf("Error occured while malloc or open\n");
			return (0);
		}
		data = fill_champ(fd);
		data.arg = arg;
		if (check_error(data.error) == 1)
		{
			return (0);
		}
//		while (data.play[0].code[i] != '\0')
//		{
//			info = get_line(data.play[0].code[i]);
//			i += nb_oct(info, data.play[0].code[i + 1], &start) + 2;
		//	ft_printf("%d\n", i);
//		}
	//	ret = list_info(data);
		vm_stuff(data);
	}
	return (0);
}
