/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 10:40:59 by rostroh           #+#    #+#             */
/*   Updated: 2018/03/09 15:30:54 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "libft.h"
# include "ft_printf.h"
# include <ncurses.h>
# include <sys/types.h>
# include <signal.h>
# include <time.h>

# define SPEED				800
# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define MAX_ARGS_NUMBERS	4
# define MAX_PLAYERS		4
# define MEM_SIZE			(4 * 1024)
# define IDX_MOD			(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE		(MEM_SIZE / 6)

# define COMMENT_CHAR		'#'
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define SEPARATOR_CHAR		','

# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRIG	".comment"

# define REG_NUMBER			16

# define CYCLE_TO_DIE		1536

# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECK			10

# define T_REG				1
# define T_DIR				2
# define T_IND				4
# define T_LAB				8

# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define COREWAR_EXEC_MAGIC	0xea83f3

typedef struct				s_fd
{
	int						i;
	int						n;
	int						tmp;
	int						len;
}							t_fd;

typedef struct				s_cycle
{
	int						i;
	int						die;
	int						win;
	int						val;
	int						yolo;
	int						check;
	int						cycle_d;
}							t_cycle;

typedef struct				s_ver
{
	int						li;
	int						cy;
	int						op;
	int						de;
	int						pc;
}							t_ver;

typedef struct				s_inf
{
	int						nb;
	int						arg;
	int						*typ;
	int						*l;
	int						*val;
	int						length;
	char					*min_addr;
}							t_inf;

typedef struct				s_var
{
	int						nb;
	int						bol;
	int						adv;
	int						len;
}							t_var;

typedef struct				s_process
{
	int						start_cycle;
	int						val[REG_NUMBER];
	int						reg[REG_NUMBER][REG_SIZE];
	char					*pc;
	char					*ins;
	int						carry;
	int						line;
	int						ocp;
	int						live;
	int						last_live[2];
	int						seek;
	t_inf					inf;
	int						champ;
	int						live_champ[MAX_PLAYERS];
	int						number;
	struct s_process		*next;
	struct s_process		*pre;
}							t_process;

typedef struct				s_pam
{
	int						a;
	int						n[MAX_PLAYERS];
	int						nb;
	int						end;
	int						n_o;
	int						help;
	int						sdl;
	int						ver;
	int						dump;
	int						music;
	int						error;
	char					*patern;
	t_ver					ver_num;
}							t_pam;

typedef struct				s_champ
{
	int						nb;
	int						len;
	int						r1;
	char					name[PROG_NAME_LENGTH];
	char					code[CHAMP_MAX_SIZE];
	char					comment[COMMENT_LENGTH];
}							t_champ;

typedef struct				s_reg
{
	int						r1;
	int						r2;
	int						res;
}							t_reg;

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

typedef struct				s_inf_v
{
	int						last_live[4];
	int						nb_live[4];
	int						nb_pro_c[4];
}							t_inf_v;

typedef struct				s_vm
{
	char					*addr;
	char					color[MEM_SIZE];
	int						error;
	int						nb_pros;
	int						cycle;
	int						ctd;
	int						alive;
	int						number;
	t_pam					arg;
	t_process				*pros;
	t_process				*end_l;
	t_process				*start_l;
	t_champ					play[MAX_PLAYERS];
	t_inf_v					inf_v;
}							t_vm;

t_process					*calcul_val(t_process *c, int *y, unsigned int *a,
		int *p);
t_process					*kill_them_all(t_process *p, t_vm *v, int cy,
		int c);
t_process					*if_must_be_call(t_process *c, t_var *v, t_vm *vm);
t_process					*call_instru(t_process *cpy, t_var *var, t_vm *vm);
t_process					*gestion_process(t_process *pro, int cy, t_vm *vm);
t_process					*init_inf(t_process *c, t_vm vm, int *nb, int *b);
t_process					*calc_len(t_process *p, int *l, int *bol, int nb);
t_process					*check_ocp(t_process *p, int *n, int *b, t_vm vm);
t_process					*sound_and_reset(t_process *pro, t_vm *vm, int t);
t_process					*call_tree(t_inf truc, t_process *pros, t_vm vm);
t_process					*ocp_invalid(t_process *c, int *bol, int *len);
t_process					*dup_pros(t_process *src, t_inf inf, t_vm *vm);
t_process					*find_val(t_process *cpy, int *adv, int *len);
t_process					*start_gestion(t_process *c, t_vm vm, int cy);
t_process					*adv_printf(t_process *cpy, int len, int nb);
t_process					*calc_val(int *adv, int *nb, t_process *c);
t_process					*reverse_list(int cy, int cycle, t_vm *vm);
t_process					*add_new_process(t_process *src, int nb);
t_process					*re_init_live(t_process *pro, t_vm *vm);
t_process					*move_pc(t_process *cpy, int len);
t_process					*get_adr(t_process *cpy);

t_cycle						init_cycle(void);

t_inf						nb_oct(t_inf srt, int line, int ocp);
t_inf						nb_oct(t_inf srt, int line, int ocp);
t_inf						add_elem(int info, int opc);

t_ver						get_verbose(int nu);

t_pam						get_option(int argc, char **argv, int i);

t_vm						fill_champ(int *fd);
t_vm						ft_ncurses(t_process *pro, t_vm vm);

void						reg_write(t_process *pros, unsigned int val,
		int reg, int size);
void						ft_menu(WINDOW *m, t_vm *vm, int nb, t_process *p);
void						ft_catch_event(WINDOW *menu, WINDOW *game, int ch);
void						ft_init_game(t_process *p, WINDOW *game, t_vm vm);
void						print_dead(t_vm *vm, t_process *p, int c, int cy);
void						message_champ(int nb, int winner, t_champ champ);
void						get_col(t_process *pro, t_vm vm, int y, int *p);
void						ft_lfork(t_inf inf, t_process *pros, t_vm *vm);
void						ft_lldi(t_inf inf, t_process *pros, t_vm *vm);
void						ft_fork(t_inf inf, t_process *pros, t_vm *vm);
void						ft_live(t_inf info, t_process *pro, t_vm *vm);
void						ft_zjmp(t_inf inf, t_process *pros, t_vm *vm);
void						ft_add(t_inf inf, t_process *pros, t_vm *vm);
void						ft_aff(t_inf inf, t_process *pros, t_vm *vm);
void						ft_ldi(t_inf inf, t_process *pros, t_vm *vm);
void						ft_lld(t_inf inf, t_process *pros, t_vm *vm);
void						ft_sti(t_inf inf, t_process *pros, t_vm *vm);
void						ft_sub(t_inf inf, t_process *pros, t_vm *vm);
void						ft_xor(t_inf inf, t_process *pros, t_vm *vm);
void						ft_and(t_inf inf, t_process *pros, t_vm *vm);
void						ft_or(t_inf inf, t_process *pros, t_vm *vm);
void						ft_st(t_inf inf, t_process *pros, t_vm *vm);
void						ft_ld(t_inf inf, t_process *pros, t_vm *vm);
void						ft_init_ncurses(t_process *pro, t_vm vm);
void						ft_quit_ncurses(t_vm vm, int w);
void						play_music(t_vm vm, pid_t son);
void						cpy_reg(int *tab, int **res);
void						get_hexa(int val, int bol);
void						vm_stuff(t_vm data);
void						dump(char *ptr);
void						message(int nb);

char						*get_relative(char *adr, t_inf inf);
char						*get_afplay(t_vm vm);

int							cycle_gestion(t_vm vm, t_process *pro, t_cycle cy);
int							type_param(int ocp, int pos, int line, int *res);
int							catch_reg_val(int nb, t_inf inf, t_process *pros);
int							catch_ind_val(t_process *pro, int nb);
int							is_reg_good(t_inf inf, int line);
int							error_nb_champ(t_vm vm, int *fd);
int							ocp_valid(int line, int ocp);
int							adv_value(int line, int ocp);
int							string_is_digit(char *str);
int							count_live(t_process *pro);
int							winner(t_process *pro);
int							check_error(t_vm vm);
int							get_ocp(void *addr);
int							check_magic(int fd);
int							have_ocp(int line);
int							check_r(t_inf inf);
int							get_line(int opc);

static void				(*g_instructab[17])(t_inf i, t_process *p, t_vm *v) =
{
	&ft_live, &ft_ld, &ft_st, &ft_add, &ft_sub, &ft_and, &ft_or, &ft_xor,
	&ft_zjmp, &ft_ldi, &ft_sti, &ft_fork, &ft_lld, &ft_lldi, &ft_lfork,
	&ft_aff, NULL
};

#endif
