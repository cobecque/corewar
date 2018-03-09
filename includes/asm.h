/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 00:51:56 by cobecque          #+#    #+#             */
/*   Updated: 2018/03/08 06:36:06 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "ft_printf.h"
# include "op.h"

typedef struct		s_op
{
	char			*name;
	int				nb_arg;
	int				tab[3];
	int				op_code;
	int				cycle;
	char			*des;
	int				d_size;
	int				strange;
}					t_op;

typedef struct		s_inst
{
	int				nb_ins;
	int				bol;
	char			*label;
	char			*label1;
	char			*label2;
	char			*label3;
	int				line;
	int				ocp;
	int				len;
	int				typ[3];
	unsigned int	val[3];
	struct s_inst	*next;
}					t_inst;

typedef struct		s_file
{
	char			*name;
	char			*comment;
	t_inst			*ins;
}					t_file;

extern t_op			g_op_tab[];

unsigned int		find_val(char *par);

t_file				instruction(t_file file, char *line);
t_file				fill_file(t_file file, char *line);
t_file				init_file(void);

t_inst				*add_inst(t_inst *ins, int i, char *line);
t_inst				*label_param(char **par, t_inst *ins);
t_inst				*find_param(char *line, int i, t_inst *ins);
t_inst				*find_label(t_inst *ins);

char				**ft_cut(char *line, int i, int j, int count);
char				*cut_label(char *line, int size);
char				*cut_middle(char *line);
char				*cut_start(char *line);
char				*have_label(char *par);

void				ft_putchar_fd_size(char c, char c1, char c2, int fd);
void				cpy_name(char *res, char *line, int *i, int *j);
void				fill_champ(int fd, t_file file, t_header h);
void				create_file(char *argv, t_file file);
void				write_binary(t_file file, int fd);
void				write_spec(t_inst *ins, int fd);
void				fill_magic(int fd, t_header h);
void				clear_file(t_file file);
void				spec_typ(int *typ);

int					check_label(t_inst *ins, char *label, int line);
int					ft_letter(char *str, int *i, int *j, int *let);
int					label_range(t_inst *ins, char *label, int pos);
int					ocp_calc(t_inst *ins, int i, int neg);
int					ft_sep(char *line, int i, int *count);
int					bad_typ(int typ, int line, int j);
int					line_size(char *line, int i);
int					find_ocp(char *line, int i);
int					spec_ocp(int i, char *line);
int					find_typ(char *par, int i);
int					ft_size_label(char *line);
int					check_error(t_file file);
int					size_champ(t_file file);
int					error_val(t_file file);
int					error_typ(t_file file);
int					error_len(t_file file);
int					error_open(int fd);
int					have_ocp(int i);

#endif
