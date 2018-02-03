/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 05:40:33 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/30 05:23:39 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int		ocp_valid(int line, int ocp)
{
	if ((line == 1 || line == 12) && (ocp == 144 || ocp == 208 || ocp == -112))
		return (1);
	if (line == 2 && (ocp == 80 || ocp == 112))
		return (1);
	if ((line == 3 || line == 4) && ocp == 84)
		return (1);
	if ((line == 5 || line == 6 || line == 7) && (ocp == 84 || ocp == 148 ||
				ocp == 212 || ocp == 100 || ocp == 116 || ocp == 164 ||
				ocp == 228 || ocp == 244 || ocp == 180))
		return (1);
	if ((line == 9 || line == 13) && (ocp == 84 || ocp == 100 || ocp == 148 ||
				ocp == 212 || ocp == 228 || ocp == 164 || ocp == -108))
		return (1);
	if (line == 10 && (ocp == 84 || ocp == 100 || ocp == 116 || ocp == 120 ||
				ocp == 104 || ocp == 88 ))
		return (1);
	return (0);
}

int		get_line(int opc)
{
	int		i;

	i = 0;
	if (opc > 17 || opc < 1)
		return (-1);
	//ft_printf("opc = %d\n", opc);
	while (i < 17)
	{
		if (g_op_tab[i].op_code == opc)
		{
	//		ft_printf("name = %s\n", g_op_tab[i].name);
			return (i);
		}
		i++;
	}
	//ft_putchar('\n');
	return (-1);
}

int		type_param(int ocp, int pos, int line, int *res)
{
	ocp  = (ocp >> (6 - (2 * pos)));
	if ((ocp & 3) == 3) //3 = indirecte
	{
		*res = 3;
		return (2);
	}
	if ((ocp & 2) == 2) //2 = directe
	{
		if (g_op_tab[line].strange == 0)
		{
			*res = 4;
			return (4);
		}
		else
		{
			*res = 2;
			return (2);
		}
	}
	if ((ocp & 1) == 1)		//1 = registre
	{
		*res = 1;
		return (1);
	}
	return (0);
}

int		adv_value(int line, int ocp)
{
	int		i;
	int		res;
	int		val;

	i = 0;
	res = 0;
	val = 0;
	while (i < g_op_tab[line].nb_arg)
	{
		val += type_param(ocp, i, line, &res);
		i++;
	}
	return (val);
}

t_inf	nb_oct(t_inf srt, int line, int ocp)
{
	int		i;
	int		*tab;

	i = 0;
	if (!(tab = (int *)malloc(sizeof(int) * 3)))
		return(srt);
	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	srt.l[0] = 0;
	srt.l[1] = 0;
	srt.l[2] = 0;
	srt.length = 0;
	srt.arg = g_op_tab[line].nb_arg;
	srt.name = ft_strdup(g_op_tab[line].name);
	if (ft_strcmp(g_op_tab[line].name, "live") == 0)
	{
		tab[0] = 3;
		srt.l[i] = 4;
	}
	else if (ft_strcmp(g_op_tab[line].name, "zjmp") == 0)
	{
		tab[0] = 2;
		srt.l[i] = 2;
	}
	else if (ft_strcmp(g_op_tab[line].name, "lfork") == 0 || ft_strcmp(g_op_tab[line].name, "fork") == 0)
	{
		tab[0] = 2;
		srt.l[i] = 2;
	}
	else
	{
		while (i < g_op_tab[line].nb_arg)
		{
			srt.l[i] = type_param(ocp, i, line, &tab[i]);
			i++;
		}
	}
	srt.typ = tab;
//	ft_printf(C_RED"%d\n"FC_ALL, srt->length);
	return (srt);
}

/*t_inf	*last_elem(t_inf *srt)
{
	while (srt->next != NULL)
		srt = srt->next;
	return (srt);
}*/

int		have_ocp(int line)
{
	if (line == 0 || line == 8 || line == 11 || line == 14)
		return (-1);
	return (0);
}

t_inf	add_elem(int info, int opc)//,/* t_inf *srt,*/ int nb)
{
	t_inf	new;
/*	t_inf	*cpy;
	t_inf	*new;

	*/new.length = 0;
	/*
	cpy = srt;*/
//	if (!(new = (t_inf *)malloc(sizeof(t_inf) * 1)))
//		return (NULL);
//	new.nb = nb;
	new.l = (int *)malloc(sizeof(int) * 3);
	new = nb_oct(new, info, opc);
	//ft_printf("length = %d\n", new->length);
	//ft_printf("->%d\n->%d\n->%d\n", new->typ[0], new->typ[1], new->typ[2]);
/*	if (!srt)
		return (new);
	while (cpy->next != NULL)
		cpy = cpy->next;
	cpy->next = new;*/
	return (new);
}

int		fun(int type)
{
	if (type == 3)
		return (2);
	return (type);
}

int		*list_val(t_inf elem, char *str)
{
	int		i;
	int		nb;
	int		j;
	unsigned char zj;
	int		*tab;

	i = 0;
	if (!(tab = (int *)malloc(sizeof(int) * 3)))
		return (NULL);
	if (ft_strcmp(elem.name, "zjmp") == 0 || ft_strcmp(elem.name, "fork") == 0 || ft_strcmp(elem.name, "lfork") == 0)
	{
		zj = *str;
		if (zj == 255)
		{
			str++;
			zj = *str;
			zj = ~(zj - 1);
			i = -zj;
		}
		else
		{
			ft_putstr("yolo\n");
			str++;
			i = *str;
		}
		tab[0] = i;
//		ft_printf("VAL = %d zj = %d\n", tab[0], i);
		return (tab);
	}
	if (ft_strcmp(elem.name, "live") == 0)
		str += 2;
	while (i < elem.arg)
	{
		j = 0;
		while (j < fun(elem.typ[i]) - 1)
			j++;
		str += j;
		zj = *str;
		if (zj == 255)
		{
			str++;
			zj = *str;
			zj = ~(zj - 1);
			nb = -zj;
			tab[i] = nb;
		}
		else
		{
			str++;
			tab[i] = *str;
		}
//		ft_printf("VAL[%d] = %d pour j = %d\n", i, tab[i], j);
	//	str++;
		i++;
	//	if (*str == '\0')
	//		break;
	}
	return (tab);
}

int		is_ocp(int line)
{
	if (ft_strcmp(g_op_tab[line].name, "ld") == 0)
		return (2);
	if (ft_strcmp(g_op_tab[line].name, "zjmp") == 0)
		return (1);
	if (ft_strcmp(g_op_tab[line].name, "sti") == 0)
		return (2);
	if (g_op_tab[line].strange == 0 && ft_strcmp(g_op_tab[line].name, "live") != 0)
		return (2);
	return (1);
}

/*t_inf	**list_info(t_vm data)
{
	int		i;
	int		j;
	int		nb;
	int		info;
	t_inf	**srt;

	if (!(srt = (t_inf **)malloc(sizeof(t_inf *) * data.nb_pros)))
		return (NULL);
	i = 0;
	while (i < data.nb_pros)
	{
		j = 0;
		nb = 1;
		srt[i] = NULL;
		while (data.play[i].code[j] != '\0')
		{
			info = get_line(data.play[i].code[j]);
			srt[i] = add_elem(info, data.play[i].code[j + 1], srt[i], nb);
			srt[i]->val = list_val(last_elem(srt[i]), &data.play[i].code[j + 1]);
			j += last_elem(srt[i])->length + is_ocp(info);//get_line(data.play[i].code[j]));
			nb++;
		}*/
/*		j = 0;
		while (data.play[i].code[j] != '\0')
		{
			j += 2;
		}*/
/*		i++;
	}
	return (srt);
}*/
