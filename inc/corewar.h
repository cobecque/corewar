/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 18:53:50 by cobecque          #+#    #+#             */
/*   Updated: 2017/10/13 23:03:05 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "ft_printf.h"

typedef struct		s_file
{
	char			*line;
	struct s_file	*next;
}					t_file;

t_file				*init_file(t_file *file, char *line);
void				ft_try_it(t_file *file, char *n, char *c, int s);
char				*ft_calcul(char *line);

#endif
