/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:08:50 by cobecque          #+#    #+#             */
/*   Updated: 2017/11/15 18:51:17 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "ft_printf.h"
# include "op.h"

typedef struct		s_label
{
	char			*label;
	struct s_label	*next;
}					t_label;
typedef struct		s_file
{
	char			*line;
	char			*code;
	char			*label;
	char			**param;
	char			*inst;
	unsigned char	*binair;
	int				nb;
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

unsigned char		*dec_to_bi(char *code);
unsigned char		hex_dec(char *code);
header_t			init_header(char *name, char *comment);
t_file				*init_file(t_file *file, char *line);
t_file				*go_label(t_file *file, char *label);
t_file				*ft_encodage(t_file *file, int fd, header_t header);
t_file				*ft_label(t_file *file);
t_file				*ft_ocp(t_file *file);
t_file				*ft_instruction(t_file *file);
t_file				*ft_parametre(t_file *file);
t_file				*fill_binair(t_file *file, int fd, header_t header);
t_file				*parsing(t_file *file, char *argv, header_t *header);
t_file				*file_param(t_file *file);
t_file				*ft_spec_param(t_file *file);
char				*search_instruction(char *line, char *label, t_file *file);
char				*ft_conv_op_code(int op_code);
char				*cut_line(char *line, char *label);
char				*ft_hex(char *tmp, int j);
char				*ft_calc_ocp(char *line);
char				*conv_hex(char *binary);
char				*get_name(char *str);
char				*ft_two_octet(char *str, int bol, int l, char pa);
char				*ft_x_octet(t_file *file, char *str, int bol, int l);
char				*ft_calc_para(char *line, t_file *file, int i);
char				*ft_binary(char *line);
char				*search_spec(char *code, t_file *file, int nb);
char				*reverse_hex(int j);
char				*good_hex(char *tmp);
void				ft_fill_ocp(char **bin, int *j, int *i, char *n);
void				ft_putchar_fd_size(char c, char c2, char c3, int fd);
void				put_magic(header_t header, int fd);
void				put_all(header_t header, int fd);
void				ft_get_par(char *tmp, int *i, int *j, int *p);
int					ft_is_label(char *label);
int					ft_is_spec(char *code);
int					ft_label_signed(t_file *file, char *line, char *label);
int					label_pos(t_file *file, char *label, char *code);
int					label_neg(t_file *file, char *label, char *code);
int					ft_nb_octet(char *inst);
int					octet_on_line(char *code);
int					all_octet(t_file *file);
int					write_in(int size, int all, int nb, unsigned char *);
int					is_end_label(t_file *tmp, char *label, int *size);

#endif
