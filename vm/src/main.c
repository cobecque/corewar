/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 17:29:39 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/08 08:00:35 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "libft.h"
#include "ft_printf.h"

int			check_error(t_vm data)
{
	int			i;
	int			tab[4];

	i = 0;
	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 0;
	if (data.error == 1)
		return (1);
	if (data.arg.n_o == 1)
	{
		while (i < data.nb_pros)
		{
			if (data.arg.n[i] > 4 || data.arg.n[i] < 1)
				return (3);
			tab[data.arg.n[i] - 1]++;
			if (tab[data.arg.n[i] - 1] > 1)
				return (3);
			i++;
		}
		if ((tab[0] == 0 && tab[1] != 0) || (tab[1] == 0 && tab[2] != 0) ||
				(tab[2] == 0 && tab[3] != 0))
			return (3);
	}
	if (data.error == 0)
		return (0);
	return (1);
}

int			*sort_fd(int *fd, t_pam arg)
{
	int		i;
	int		*tr;

	i = 1;
	if (!(tr = (int *)malloc(sizeof(int) * 5)))
		return (NULL);
	tr[0] = fd[0];
	while (i < fd[0])
	{
		tr[i] = fd[arg.n[i - 1]];
		i++;
	}
	free(fd);
	return (tr);
}

int			*get_fd(int argc, char **argv, t_pam *pam)
{
	int			i;
	int			n;
	int			tmp;
	int			*fd_tab;

	i = pam->nb + 1;
	n = 0;
	tmp = pam->nb;
	if (!(fd_tab = (int *)malloc(sizeof(int) * argc - pam->nb)))
		return (NULL);
	fd_tab[0] = argc - pam->nb;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-n") == 0)
		{
			pam->n_o = 1;
			i++;
			tmp++;
			fd_tab[0]--;
			if (i < argc)
			{
				if (string_is_digit(argv[i]) == 0)
					pam->patern = ft_strdup("option -n have incorrect parameter");
				else
					pam->n[n] = ft_atoi(argv[i]);
				n++;
				i++;
				tmp++;
				fd_tab[0]--;
			}
			else
				pam->patern = ft_strdup("option -n have incorrect parameters");
		}
		if (i < argc)
		{
			if (i - tmp > MAX_PLAYERS)
				pam->patern = ft_strdup("Too many champ");
			else if ((fd_tab[i - tmp] = open(argv[i], O_RDONLY, 0)) <= 0)
				pam->patern = ft_strdup("Wrong file or directory");
		}
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

void		start_init(int *fd, t_pam arg)
{
	int			err;
	t_vm		data;

	if (arg.n_o == 1)
		fd = sort_fd(fd, arg);
	data = fill_champ(fd);
	data.arg = arg;
	if ((err = check_error(data)) != 0)
	{
		if (err == 1)
			ft_putstr("Champion too big\n");
		if (err == 3)
			ft_putstr("Error at -n parameters\n");
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
	fd = NULL;
	if (argc == 1)
		message(1);
	else
	{
		arg = get_option(argc, argv);
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
	while (1)
		;
	return (0);
}
