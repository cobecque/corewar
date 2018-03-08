/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 17:29:39 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/08 15:07:46 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int			*sort_fd(int *fd, t_pam arg)
{
	int		i;
	int		j;
	int		*tr;

	i = 1;
	if (!(tr = (int *)malloc(sizeof(int) * 5)))
		return (NULL);
	tr[0] = fd[0];
	while (i < fd[0])
	{
		j = 0;
		while (j < fd[0])
		{
			if (arg.n[j] == i)
				break ;
			j++;
		}
		tr[i] = fd[j + 1];
		i++;
	}
	free(fd);
	return (tr);
}

void		option_n(t_pam *pam, char **argv, int *fd_tab, t_fd *fd)
{
	if (ft_strcmp(argv[fd->i], "-n") == 0)
	{
		pam->n_o = 1;
		fd->i++;
		fd->tmp++;
		fd_tab[0]--;
		if (fd->i < fd->len)
		{
			if (string_is_digit(argv[fd->i]) == 0)
				pam->patern = ft_strdup("option -n have incorrect parameter");
			else
				pam->n[fd->n] = ft_atoi(argv[fd->i]);
			fd->n++;
			fd->i++;
			fd->tmp++;
			fd_tab[0]--;
		}
		else
			pam->patern = ft_strdup("option -n have incorrect parameters");
	}
}

int			*get_fd(int argc, char **argv, t_pam *pam)
{
	t_fd		fd;
	int			*fd_tab;

	fd.i = pam->nb + 1;
	fd.n = 0;
	fd.tmp = pam->nb;
	fd.len = argc;
	if (!(fd_tab = (int *)malloc(sizeof(int) * argc - pam->nb)))
		return (NULL);
	fd_tab[0] = argc - pam->nb;
	while (fd.i < argc)
	{
		option_n(pam, argv, fd_tab, &fd);
		if (fd.i < argc)
		{
			if (fd.i - fd.tmp > MAX_PLAYERS)
				pam->patern = ft_strdup("Too many champ");
			else if ((fd_tab[fd.i - fd.tmp] = open(argv[fd.i], O_RDONLY, 0))
					<= 0)
				pam->patern = ft_strdup("Wrong file or directory");
		}
		fd.i++;
	}
	return (fd_tab);
}

void		start_init(int *fd, t_pam arg)
{
	t_vm		data;

	if (arg.n_o == 1)
		fd = sort_fd(fd, arg);
	data.arg = arg;
	if (error_nb_champ(data, fd) != 0)
	{
		ft_putstr("Error at -n parameters\n");
		exit(-1);
	}
	data = fill_champ(fd);
	if (check_error(data) != 0)
	{
		ft_putstr("Champion too big\n");
		exit(-1);
	}
	vm_stuff(data);
}

int			main(int argc, char **argv)
{
	int			i;
	int			*fd;
	t_pam		arg;

	i = 0;
	if (argc == 1)
		message(1);
	else
	{
		arg = get_option(argc, argv, 0);
		if (arg.patern != NULL)
		{
			if (ft_strcmp(arg.patern, "Help") != 0)
				ft_printf("Bad patern : %s\n", arg.patern);
			return (0);
		}
		if ((fd = get_fd(argc, argv, &arg)) == NULL || arg.patern != NULL)
		{
			ft_printf("%s\n", arg.patern);
			free(arg.patern);
			return (0);
		}
		start_init(fd, arg);
	}
	return (0);
}
