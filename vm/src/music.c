/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 01:47:08 by cobecque          #+#    #+#             */
/*   Updated: 2018/03/06 07:44:32 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

char		*get_afplay(t_vm vm)
{
	int			i;

	i = 0;
	while (i < vm.nb_pros)
	{
		if (ft_strcmp(vm.play[i].name, "Yandere-chan") == 0)
			return ("afplay ./sound_bank/yuki9min.mp3");
		i++;
	}
	if (vm.nb_pros == 1)
		return ("afplay ./sound_bank/arcade.mp3");
	if (vm.nb_pros == 2)
		return ("afplay ./sound_bank/red_theme.mp3");
	if (vm.nb_pros == 3)
		return ("afplay ./sound_bank/necrodancer.mp3");
	if (vm.nb_pros == 4)
		return ("afplay ./sound_bank/megalovania.mp3");
	return ("afplay ./sound_bank/ascenseur.mp3");
}

void		play_music(t_vm vm, pid_t son)
{
	char	*to_play;

	to_play = get_afplay(vm);
	while (42)
		system(to_play);
	kill(son, SIGKILL);
}
