/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 18:53:50 by cobecque          #+#    #+#             */
/*   Updated: 2017/10/20 19:55:30 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "ft_printf.h"
# include "op.h"

/*typedef struct		s_file
{
	char			*line;
	char			*octet;
	char			*inst;
	struct s_file	*next;
}					t_file;

typedef struct		s_label
{
	char			*label;
	struct s_label	*next;
}					t_label;
*/
typedef struct		s_file
{
	char			*line;
	char			*code;
	char			*label;
	char			*inst;
	struct s_file	*next;
}					t_file;

typedef struct		s_op
{
	char			*name;
	int				nb_arg;
	int				tab[3];
	int				op_code;
	int				cycle;
	char			*description;
	int				direct_size;
	int				strange;
}					t_op;

extern t_op			g_op_tab[];
/*
t_label				*init_label(t_label *list, char *label);
t_label				*feed_label(t_label *list, t_file *file);
t_file				*init_file(t_file *file, char *line);
void				ft_try_it(t_file *file, char *n, char *c, int s);
void				ft_two_octet(t_file *file, char *str, int bol);
void				ft_x_octet(t_file *file, char *str, int bol);
void				spec_calc(t_file *file, t_label *list);
char				*ft_calcul(char *line, t_file *file);
char				*ft_look(char *line, t_file *file);
char				*ft_loot_type(char *line, t_file *file);
char				*ft_conv_hexa(char *line, int dec);
char				*search_label(char *line);
char				*ft_param(char *line, t_file *file);
char				*ft_binary(char *str);
*/

t_file				*init_file(t_file *file, char *line);
t_file				*ft_encodage(t_file *file);
t_file				*ft_label(t_file *file);
t_file				*ft_ocp(t_file *file);
t_file				*ft_instruction(t_file *file);
t_file				*ft_parametre(t_file *file);
char				*search_instruction(char *line, char *label, t_file *file);
char				*ft_conv_op_code(int op_code);
char				*cut_line(char *line, char *label);
char				*ft_hex(char *tmp, int j);
char				*ft_calc_ocp(char *line);
char				*conv_hex(char *binary);
char				*ft_two_octet(char *str, int bol, int l);
char				*ft_x_octet(t_file *file, char *str, int bol, int l);
char				*ft_calc_para(char *line, t_file *file);
char				*ft_binary(char *line);
void				ft_asm(t_file *file, char *name, char *comment);
int					ft_is_label(char *label);

#endif
