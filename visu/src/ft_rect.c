/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:40:28 by cobecque          #+#    #+#             */
/*   Updated: 2017/12/04 18:45:45 by cobecque         ###   ########.fr       */
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

void			all(SDL_Renderer *renderer, SDL_Rect *rects, SDL_Texture **texte2)
{
	int			i;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRects(renderer, rects, 4096);
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	i = 0;
	while (i < 4096)
	{
		if (i < 16 * 64)
			fill(1, rects, renderer, i);
		if (i < 32 * 64 && i >= 16 * 64)
			fill(2, rects, renderer, i);
		if (i < 48 * 64 && i >= 32 * 64)
			fill(3, rects, renderer, i);
		if (i < 64 * 64 && i >= 48 * 64)
			fill(4, rects, renderer, i);
		//SDL_RenderFillRect(renderer, &rects[i]);
		SDL_RenderCopy(renderer, texte2[i % 225], NULL, &rects[i]);
		i++;
	}
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, 1935, 1295, 2550, 1295);
	SDL_RenderDrawLine(renderer, 1935, 15, 2550, 15);
	SDL_RenderDrawLine(renderer, 2550, 15, 2550, 1295);
}

char			*hexa(int i)
{
	char	*str;
	int		res;

	if (!(str = (char *)malloc(sizeof(char) * 5)))
		return (NULL);
	str[0] = ' ';
	str[3] = ' ';
	if (i <= 15)
	{
		str[1] = '0';
		if (i < 10)
			str[2] = i + '0';
		if (i > 9)
			str[2] = i + 'A' - 10;
		str[4] = '\0';
	}
	else
	{
		res = i % 15;
		i /= 15;
		if (res > 10)
			str[2] = res + 'A' - 10;
		else
			str[2] = res + '0';
		if (i > 10)
			str[1] = i + 'A' - 10;
		else
			str[1] = i + '0';
		str[4] = '\0';
	}
	return (str);
}
