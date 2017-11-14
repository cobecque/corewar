/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 17:16:04 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/13 12:46:29 by rostroh          ###   ########.fr       */
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

#define CYCLE_TO_DIE		1536
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
	int						reg[REG_NUMBER][REG_SIZE];
	void					*pc;
	int						carry;
	int						live;
	int						number;
	struct s_process		*next;
}							t_process;

typedef struct				s_inf
{
	int						nb;
	int						arg;
	int						*typ;
	int						*val;
	int						length;
	char					*name;
	struct s_inf			*next;
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
	void					*addr;
	int						error;
	int						nb_pros;
	t_champ					play[MAX_PLAYERS];
}							t_vm;

t_vm						fill_champ(int *fd);
void						vm_stuff(t_vm data);
int							get_line(int opc);
int							get_ocp(void *addr);
t_inf						*nb_oct(t_inf *srt, int line, int ocp);
t_inf						**list_info(t_vm data);
