/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 18:56:18 by cobecque          #+#    #+#             */
/*   Updated: 2017/10/20 19:34:19 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_file	*init_file(t_file *file, char *line)
{
	t_file	*tmp;
	t_file	*new;

	tmp = file;
	if (!(new = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	if (!(new->line = (char *)malloc(sizeof(char) * ft_strlen(line))))
		return (NULL);
	new->line = ft_strcpy(new->line, line);
	new->octet = NULL;
	new->inst = NULL;
	new->next = NULL;
	if (!tmp)
		return (new);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (file);
}

t_label	*init_label(t_label *list, char *label)
{
	t_label	*tmp;
	t_label	*new;

	tmp = list;
	if (!(new = (t_label *)malloc(sizeof(t_label))))
		return (NULL);
	new->label = ft_strdup(label);
	new->next = NULL;
	if (!tmp)
		return (new);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (list);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	char	*name;
	char	*comment;
	t_file	*file;

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
	ft_try_it(file, name, comment, 2);
	return (0);
}

char	*ft_calcul(char *line, t_file *file)
{
	char	*new;
	t_label	*list;
	int		i;
	
	i = 0;
	list = NULL;
	new = ft_strdup(line);
	list = feed_label(list, file);
	new = search_label(new);
	if (ft_strcmp(new, line) != 0)
		new = ft_strsub(line, ft_strlen(new) + 1, ft_strlen(line) - ft_strlen(new));
	new = ft_look(new, file);
	file->octet = ft_strcat(file->octet, " ");
	if (new == NULL)
		return (NULL);
	if (file->inst != NULL && ft_strcmp(file->inst, "live") != 0 && ft_strcmp(file->inst, "zjmp") != 0)
		new = ft_loot_type(new, file);
	new = ft_param(new, file, list);
	ft_printf(C_RED"\n%s\n"FC_ALL,(file->octet));
	return (new);
}

void	ft_two_octet(t_file *file, char *str, int bol)
{
	if (bol == 0)
	{
		file->octet = ft_strcat(file->octet, " ");
		str = ft_binary(str);
		str = ft_conv_hexa(str, 0);
		file->octet = ft_strcat(file->octet, str);
	}
	file->octet = ft_strcat(file->octet, " ");
	file->octet = ft_strcat(file->octet, "0x00");
	if (bol == 1)
	{
		file->octet = ft_strcat(file->octet, " ");
		str = ft_binary(str);
		str = ft_conv_hexa(str, 0);
		file->octet = ft_strcat(file->octet, str);
	}
}

void	spec_calc(t_file *file, t_label *list)
{
	t_label	*l;
	t_file	*tmp;
	char	*enc;
	int		nb_octet;

	tmp = file;
	l = list;
	enc = ft_strdup(file->octet);
	while (tmp != NULL && ft_strncmp(tmp->line, l->label, ft_strlen(l->label)) != 0)
	{
		ft_calcul(tmp->line, file);
		ft_putstr(tmp->octet);
		if (tmp->next == NULL && ft_strncmp(tmp->line, l->label, ft_strlen(l->label)) != 0)
		{
			tmp = file;
			if (l->next != NULL)
				l = l->next;
			else
				break;
		}
		if (l->next == NULL && tmp->next != NULL)
			l = l->next;
		else if (l->next == NULL && tmp->next == NULL && ft_strncmp(tmp->line, l->label, ft_strlen(l->label)) != 0)
			break;
		tmp = tmp->next;
	}
	nb_octet = ft_strlen(file->octet) / 4;

}

void	ft_x_octet(t_file *file, char *str, int bol)
{
	int		i;

	i = 0;
	while (i < 17)
	{
		if (ft_strcmp(file->inst, g_op_tab[i].name) == 0)
			break;
		i++;
	}
	if (g_op_tab[i].direct_size == 1)
	{
		if (bol == 0)
		{
			file->octet = ft_strcat(file->octet, " ");
			str = ft_binary(str);
			str = ft_conv_hexa(str, 0);
			file->octet = ft_strcat(file->octet, str);
		}
		file->octet = ft_strcat(file->octet, " ");
		file->octet = ft_strcat(file->octet, "0x00");
		file->octet = ft_strcat(file->octet, " ");
		file->octet = ft_strcat(file->octet, "0x00");
		file->octet = ft_strcat(file->octet, " ");
		file->octet = ft_strcat(file->octet, "0x00");
		if (bol == 1)
		{
			file->octet = ft_strcat(file->octet, " ");
			str = ft_binary(str);
			str = ft_conv_hexa(str, 0);
			file->octet = ft_strcat(file->octet, str);
		}
	}
	else
		ft_two_octet(file, str, bol);
}

void	ft_try_it(t_file *file, char *name, char *comment, int size)
{
//	header_t	header;
	t_file		*tmp;
	char		*octet;
	int			i;

	i = 0;
	size = 3;
	/*header.magic = COREWAR_EXEC_MAGIC;
	header.prog_name = ft_strcpy(name);
	header.prog_size = size;
	header.comment = ft_strcpy(comment);*/
	ft_putstr_fd(name, 0);
	ft_putstr_fd(comment, 0);
	tmp = file;
	while (tmp != NULL)
	{
		if (tmp->line != NULL && ft_strcmp(tmp->line, "\n") != 0 && ft_strcmp(tmp->line, "\0"))
		{
			octet = ft_calcul(tmp->line, tmp);
			i++;
		}
		tmp = tmp->next;
	}
}

char	*ft_binary(char *str)
{
	char	*reverse;
	char	*res;
	int		nb;
	int		reste;
	int		i;
	int		j;

	i = 0;
	j = 0;
	nb = ft_atoi(str);
	if (!(reverse = (char *)malloc(sizeof(char) * 9)))
		return (NULL);
	if (!(res = (char *)malloc(sizeof(char) * 9)))
		return (NULL);
	while (nb > 0)
	{
		reste = nb % 2;
		nb /= 2;
		reverse[i] = reste + '0';
		i++;
	}
	while (i < 8)
	{
		reverse[i] = '0';
		i++;
	}
	reverse[i] = '\0';
	i--;
	while (i >= 0)
	{
		res[j] = reverse[i];
		j++;
		i--;
	}
	res[j] = '\0';
	return (res);
}
