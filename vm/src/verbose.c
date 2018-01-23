/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:44:43 by rostroh           #+#    #+#             */
/*   Updated: 2018/01/21 17:51:15 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_ver			get_verbose(int nu)
{
	t_ver		ver;

	ver.li = 0;
	ver.cy = 0;
	ver.de = 0;
	ver.pc = 0;
	if (nu == 0)
		return (ver);
	if ((nu & 0x01) != 0)
		ver.li = 1;
	if ((nu & 0x02) != 0)
		ver.cy = 1;
	if ((nu & 0x04) != 0)
		ver.op = 1;
	if ((nu & 0x08) != 0)
		ver.de = 1;
	if ((nu & 0x010) != 0)
		ver.pc = 1;
	return (ver);
}
