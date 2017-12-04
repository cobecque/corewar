/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:40:28 by cobecque          #+#    #+#             */
/*   Updated: 2017/12/04 17:20:12 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

SDL_Rect		*ft_rects(void)
{
	SDL_Rect	*rect;
	int			*x;
	int			*y;
	int			i;
	int			j;
	int			h;

	if (!(rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * 4096)))
		;
	if (!(x = (int *)malloc(sizeof(int) * 64)))
		;
	if (!(y = (int *)malloc(sizeof(int) * 64)))
		;
	x[0] = 15;
	y[0] = 15;
	i = 1;
	while (i < 64)
	{
		x[i] = x[i - 1] + 30;
		y[i] = y[i - 1] + 20;
		i++;
	}
	j = 0;
	h = 0;
	while (j < 64)
	{
		i = 0;
		while (i < 64)
		{
			rect[h].y = y[j];
			rect[h].x = x[i];
			rect[h].w = 27;
			rect[h].h = 20;
			printf("rect[%d].y = %d et x = %d\n", h, rect[h].y, rect[h].x);
			i++;
			h++;
		}
		j++;
	}
	printf("i = %d et j = %d\n", i, j);
	return (rect);
}

void			fill(int player, SDL_Rect *rects, SDL_Renderer *renderer, int i)
{
	if (player == 1)
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	if (player == 2)
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	if (player == 3)
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
	if (player == 4)
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &rects[i]);
}
