/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 01:29:00 by cobecque          #+#    #+#             */
/*   Updated: 2018/01/06 03:53:27 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int		main(void)
{
	unsigned int	a;
//	unsigned int	b;
	unsigned int	res;

	a = 0x01;
//	b = 0x0203;
//	res = ((b >> 8) & 0xff) | ((b << 8) & 0xff00);
//	printf("l b = %x\nres = %x\n", b, res);
	//res = ((a >> 24) & 0xff) | ((a << 8) & 0xff0000) | ((a >> 8) & 0xff00) | ((a << 24) & 0xff000000);
	res = (a << 8) | 0x90;
	printf("l a = %x\nres = %x\n", a, res);
	res = (res << 8) | 0x70;
	printf("l a = %x\nres = %x\n", a, res);
	return (0);
}
