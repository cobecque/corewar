/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 17:29:39 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/23 05:03:37 by rostroh          ###   ########.fr       */
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

int			*get_fd(int argc, char **argv)
{
	int			i;
	int			*fd_tab;

	i = 1;
	if (!(fd_tab = (int *)malloc(sizeof(int) * argc)))
		return (NULL);
	fd_tab[0] = argc;
	while (i < argc)
	{
		if ((fd_tab[i] = open(argv[i], O_RDONLY, 0)) <= 0)
			return (NULL);
		i++;
	}
	return (fd_tab);
}

int			main(int argc, char **argv)
{
	int			i;
	int			*fd;
	t_vm		data;
	//t_inf		**ret;

	i = 0;
	if (argc == 1)
		ft_printf("Usage: ./corewar <champion1.cor> <...>\nMax 4 champions\n");
	else
	{
		if ((fd = get_fd(argc, argv)) == NULL)
		{
			ft_printf("Error occured while malloc or open\n");
			return (0);
		}
		data = fill_champ(fd);
		if (check_error(data.error) == 1)
			return (0);
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
