/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 17:16:04 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/06 06:21:29 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

#define IND_SIZE			2
#define REG_SIZE			4
#define DIR_SIZE			REG_SIZE

#define REG_CODE			1
#define DIR_CODE			2
#define IND_CODE			3

#define MAX_ARGS_NUMBERS	4
#define MAX_PLAYERS			4
#define MEM_SIZE			(4 * 1024)
#define IDX_MOD				(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE		(MEM_SIZE / 6)

#define COMMENT_CHAR		'#'
#define LABEL_CHAR			':'
#define DIRECT_CHAR			'%'
#define SEPARATOR_CHAR		','

#define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING		".name"
#define COMMENT_CMD_STRIG	".comment"

#define REG_NUMBER			16

#define CYCLE_TO_DIE		27438

#define CYCLE_DELTA			50
#define NBR_LIVE			21
#define MAX_CHECK			10

#define T_REG				1
#define T_DIR				2
#define T_IND				4
#define T_LAB				8

#define PROG_NAME_LENGTH	(128)
#define COMMENT_LENGTH		(2048)
#define COREWAR_EXEC_MAGIC	0xea83f3

typedef struct				s_process
{
	int						start_cycle;
	int						val[REG_NUMBER];
	int						reg[REG_NUMBER][REG_SIZE];
	char					*pc;						//
	char					*ins;						//
	int						carry;
	int						live;
	int						champ;
	int						number;
	struct s_process		*next;
	struct s_process		*pre;
}							t_process;

typedef struct				s_inf
{
	int						nb;
	int						arg;
	int						*typ;
	int						*l;
	int						*val;
	int						length;
	char					*name;
	char					*min_addr;
}							t_inf;

typedef struct				s_champ
{
	int						nb;
	int						len;
	char					name[PROG_NAME_LENGTH];
	char					code[CHAMP_MAX_SIZE];
	char					comment[COMMENT_LENGTH];
}							t_champ;

typedef struct				s_op
{
	char					*name;
	int						nb_arg;
	int						tab[3];
	int						op_code;
	int						cycle;
	char					*desc;
	int						direct_size;
	int						strange;
}							t_op;

extern t_op					g_op_tab[];

typedef struct				s_vm
{
	char					*addr;
	int						error;
	int						nb_pros;
	t_process				*pros; //*
	t_champ					play[MAX_PLAYERS];
}							t_vm;


void						ft_fork(t_inf inf, t_process *pros);
void						ft_lfork(t_inf inf, t_process *pros);
t_process					*dup_pros(t_process *src, t_inf inf);
t_inf						nb_oct(t_inf srt, int line, int ocp);
//t_inf						**list_info(t_vm data);
t_vm						fill_champ(int *fd);
void						reg_write(t_process *pros, unsigned int val, int reg, int size);
void						vm_stuff(t_vm data);
void						ft_add(t_inf inf, t_process *pros);
void						ft_aff(t_inf inf, t_process *pros);
void						ft_and(t_inf, t_process *pros);
void						ft_ld(t_inf inf, t_process *pros);
void						ft_ldi(t_inf inf, t_process *pros);
void						ft_lld(t_inf inf, t_process *pros);
void						ft_lldi(t_inf inf, t_process *pros);
void						ft_or(t_inf inf, t_process *pros);
void						ft_st(t_inf inf, t_process *pros);
void						ft_sti(t_inf inf, t_process *pros);
void						ft_sub(t_inf inf, t_process *pros);
void						ft_xor(t_inf inf, t_process *pros);
void						ft_zjmp(t_inf, t_process *pros);
int							have_ocp(int line);
int							get_line(int opc);
int							get_ocp(void *addr);
void						cpy_reg(int *tab, int **res);
t_inf						add_elem(int info, int opc);
t_process					*gestion_process(t_process *pro, int cycle, t_vm vm, int *val);
t_process					*call_tree(t_inf truc, t_process *pros, t_vm vm);
int							cycle_gestion(t_vm vm, t_process *pro, int ctd);
void						ft_live(t_inf info, t_process *pro);

static void					(*g_instructab[17])(t_inf, t_process *pros)=
{
	&ft_live, &ft_ld, &ft_st, &ft_add, &ft_sub, &ft_and, &ft_or, &ft_xor, 
	&ft_zjmp, &ft_ldi, &ft_sti, &ft_fork, &ft_lld, &ft_lldi, &ft_lfork, 
	&ft_aff, NULL
};
