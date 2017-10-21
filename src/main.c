/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 15:23:10 by cobecque          #+#    #+#             */
/*   Updated: 2017/10/20 20:40:14 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int argc, char **argv)
{
	t_file		*file;
	int			fd;
	char		*line;
	char		*name;
	char		*comment;

	file = NULL;
	name = NULL;
	comment = NULL;
	if (argc > 0)
	{
		fd = open(argv[1], O_RDONLY);
		while (get_next_line(fd, &line) > 0)
		{
			if (ft_strncmp(line, ".name", 5) == 0)
				name = ft_strsub(line, 6, ft_strlen(line) - 6);
			else if (ft_strncmp(line, ".comment", 8) == 0)
				comment = ft_strsub(line, 9, ft_strlen(line) - 9);
			else
				file = init_file(file, line);
			free(line);
		}
		close(fd);
	}
	ft_asm(file, name, comment);
	return (0);
}

void	ft_asm(t_file *file, char *name, char *comment)
{
	t_file	*tmp;

	tmp = file;
	name = NULL;
	comment = NULL;
	tmp = ft_encodage(tmp);
	/*while (tmp != NULL)
	{
		if (tmp->code != NULL)
			ft_printf(C_RED"%s\n"FC_ALL, tmp->code);
		tmp = tmp->next;
	}*/
}

t_file	*ft_encodage(t_file *file)
{
	t_file	*tmp;

	tmp = file;
	tmp = ft_label(tmp);
	tmp = ft_instruction(tmp);
	tmp = ft_ocp(tmp);
	tmp = ft_parametre(tmp);
/*	tmp = ft_spec_param(tmp);
*/	return (tmp);
}

t_file	*ft_label(t_file *file)
{
	t_file	*tmp;
	int		i;

	tmp = file;
	while (tmp != NULL)
	{
		i = 0;
		if (tmp->line != NULL)
		{
			while (tmp->line[i] != '\0' && tmp->line[i] != ':')
				i++;
			if (tmp->line[i] == ':')
			{
				tmp->label = ft_strsub(tmp->line, 0, i);
				if (ft_is_label(tmp->label) == 1)
					tmp->label = NULL;
			}
		}
		tmp = tmp->next;
	}
	return (file);
}

int		ft_is_label(char *str)
{
	char	*label;
	int		i;
	int		j;
	int		bol;

	label = ft_strdup(LABEL_CHARS);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		j = 0;
		bol = 0;
		while (label[j] != '\0' && bol == 0)
		{
			if (str[i] == label[j])
				bol++;
			else
				j++;
		}
		if (bol == 0)
			return (1);
		i++;
	}
	return (0);
}
