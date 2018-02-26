/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 17:29:39 by rostroh           #+#    #+#             */
/*   Updated: 2018/02/26 17:04:54 by cobecque         ###   ########.fr       */
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

void		start_init(int *fd, t_pam arg, struct timespec speed)
{
	t_vm		data;

	data = fill_champ(fd);
	data.arg = arg;
	if (check_error(data.error) == 1)
		exit(-1);
	vm_stuff(data, speed);
}

int			main(int argc, char **argv)
{
	int				i;
	int				*fd;
	t_pam			arg;
	struct timespec	speed;

	i = 0;
	speed.tv_sec = 0;
	speed.tv_nsec = 1000000000 / SPEED;
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
		if ((fd = get_fd(argc, argv, arg.nb)) == NULL)
		{
			ft_printf("Error occured while malloc or open\n");
			return (0);
		}
		start_init(fd, arg, speed);
	}
	return (0);
}
