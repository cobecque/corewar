/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:34:49 by rostroh           #+#    #+#             */
/*   Updated: 2017/11/26 04:39:35 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_process	*dup_pros(t_process *src)
{
	t_process	*new;
	t_process	*tmp;
	int			i;
	int			j;

	i = 0;
	tmp = src;
	if (!(new = (t_process *)malloc(sizeof(t_process))))
		return (NULL);
	while (i < REG_NUMBER)
	{ 
		j = 0;
		while (j < REG_SIZE)
		{
			new->reg[i][j] = src->reg[i][j];
			j++;
		}
		ft_printf("new reg = %d src reg = %d\n", new->reg[i][3], src->reg[i][3]);
		i++;
	}
	new->pc = NULL;
	new->carry = src->carry;
	new->live = src->live;
	new->start_cycle = -1;
	new->number = src->number + 1;//
	new->ins = src->ins;
	new->pc = new->ins;
	new->next = NULL;
	if (!(tmp))
		return (new);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (src);
}
/*
void		cpy_reg(int *tab, int *res[4])
{
	int		i;
//	int		*res;

	i = -1;
//	if (!(res = (int *)malloc(sizeof(int) * REG_SIZE)))
//		return (NULL);
	while (++i < REG_SIZE)
		*(res[i]) = tab[i];
}
*/
void	ft_fork(t_inf inf, t_process *pros)
{
	/*t_process	*cpy;
*/
	ft_printf(C_GRN"fork je t'envois au combat, val = %d ins = %d\n"FC_ALL, inf.val[0], pros->ins);
	pros = dup_pros(pros);
/*	cpy->ins = (pros->ins + (inf.val[0] % IDX_MOD));
	cpy->pc = cpy->ins;
	ft_printf("ins dans fork = %d\n", cpy->ins);
*/	//return (cpy);
}
