/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:40:28 by cobecque          #+#    #+#             */
/*   Updated: 2017/12/13 21:27:23 by cobecque         ###   ########.fr       */
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
		x[i] = x[i - 1] + 35;
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
			rect[h].w = 32;
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

void			ft_pause(SDL_Renderer *renderer, TTF_Font *police, int i)
{
	SDL_Rect	rect;
	SDL_Surface	*texte;
	SDL_Texture	*texte2;
	SDL_Color	color = {255, 255, 255, 255};

	police = TTF_OpenFont("police/code2000.ttf", 15);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	rect.x = 2253;
	rect.y = 15;
	rect.w = 2550 - 2253;
	rect.h = 50;
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &rect);
	rect.y = rect.y + 5;
	rect.w = 250;
	rect.h = 30;
	if (i == 1)
		texte = TTF_RenderText_Solid(police, "    --PAUSE--  ", color);
	else
		texte = TTF_RenderText_Solid(police, "    --START--  ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
}

void			ft_cycle(SDL_Renderer *renderer, TTF_Font *police, int cycle)
{
	char		*str;
	SDL_Rect	rect;
	SDL_Surface	*texte;
	SDL_Texture	*texte2;
	SDL_Color	color = {255, 255, 255, 255};


	police = TTF_OpenFont("police/code2000.ttf", 15);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	rect.x = 2253;
	rect.y = 585;
	rect.w = 2550 - 2253;
	rect.h = 40;
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &rect);
	rect.y = rect.y + 10;
	rect.w = 185;
	rect.h = 20;
	str = ft_strjoin("  Cycle : ", ft_itoa(cycle));
	texte = TTF_RenderText_Solid(police, str, color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
}



void			champ(SDL_Renderer *renderer, TTF_Font *police)
{
	SDL_Rect	rect;
	SDL_Surface	*texte;
	SDL_Texture	*texte2;
	SDL_Color	color = {255, 0, 0, 255};

	police = TTF_OpenFont("police/code2000.ttf", 15);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	rect.x = 2253;
	rect.y = 65;
	rect.w = 2550 - 2253;
	rect.h = 150;
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &rect);
	rect.y = rect.y + 5;
	rect.w = 250;
	rect.h = 30;
	texte = TTF_RenderText_Solid(police, " 1 - Fluttershy ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	rect.y = rect.y + 35;
	rect.w = 200;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, " dat fucking comment ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	rect.y = rect.y + 25;
	rect.w = 200;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, " -nombre live         0 ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	rect.y = rect.y + 25;
	rect.w = 200;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, " -nombre process      0 ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	rect.y = rect.y + 25;
	rect.w = 200;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, " -last live              0 ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);

	color.r = 0;
	color.g = 0;
	color.b = 255;
	color.a = 255;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	rect.x = 2253;
	rect.y = rect.y + 20;
	rect.w = 2550 - 2253;
	rect.h = 150;
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &rect);
	rect.y = rect.y + 5;
	rect.w = 250;
	rect.h = 30;
	texte = TTF_RenderText_Solid(police, " 2 - Fluttershy ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	rect.y = rect.y + 35;
	rect.w = 200;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, " dat fucking comment ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	rect.y = rect.y + 25;
	rect.w = 200;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, " -nombre live         0 ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	rect.y = rect.y + 25;
	rect.w = 200;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, " -nombre process      0 ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	rect.y = rect.y + 25;
	rect.w = 200;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, " -last live              0 ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);


	color.r = 0;
	color.g = 255;
	color.b = 0;
	color.a = 255;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	rect.x = 2253;
	rect.y = rect.y + 20;
	rect.w = 2550 - 2253;
	rect.h = 150;
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &rect);
	rect.y = rect.y + 5;
	rect.w = 250;
	rect.h = 30;
	texte = TTF_RenderText_Solid(police, " 3 - Fluttershy ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	rect.y = rect.y + 35;
	rect.w = 200;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, " dat fucking comment ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	rect.y = rect.y + 25;
	rect.w = 200;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, " -nombre live         0 ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	rect.y = rect.y + 25;
	rect.w = 200;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, " -nombre process      0 ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	rect.y = rect.y + 25;
	rect.w = 200;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, " -last live              0 ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);


	color.r = 255;
	color.g = 0;
	color.b = 255;
	color.a = 255;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	rect.x = 2253;
	rect.y = rect.y + 20;
	rect.w = 2550 - 2253;
	rect.h = 150;
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &rect);
	rect.y = rect.y + 5;
	rect.w = 250;
	rect.h = 30;
	texte = TTF_RenderText_Solid(police, " 4 - Fluttershy ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	rect.y = rect.y + 35;
	rect.w = 200;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, " dat fucking comment ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	rect.y = rect.y + 25;
	rect.w = 200;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, " -nombre live         0 ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	rect.y = rect.y + 25;
	rect.w = 200;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, " -nombre process      0 ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	rect.y = rect.y + 25;
	rect.w = 200;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, " -last live              0 ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
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
			fill(2, rects, renderer, i);
		if (i < 32 * 64 && i >= 16 * 64)
			fill(1, rects, renderer, i);
		if (i < 48 * 64 && i >= 32 * 64)
			fill(4, rects, renderer, i);
		if (i < 64 * 64 && i >= 48 * 64)
			fill(3, rects, renderer, i);
		SDL_RenderCopy(renderer, texte2[i % 225], NULL, &rects[i]);
		i++;
	}
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, 2253, 1295, 2550, 1295);
	SDL_RenderDrawLine(renderer, 2253, 15, 2550, 15);
	SDL_RenderDrawLine(renderer, 2550, 15, 2550, 1295);
}

char			*hexa(int i)
{
	char	*str;
	int		res;

	if (!(str = (char *)malloc(sizeof(char) * 6)))
		return (NULL);
	str[0] = ' ';
	str[4] = ' ';
	if (i <= 15)
	{
		str[1] = '0';
		if (i < 10)
			str[3] = i + '0';
		if (i > 9)
			str[3] = i + 'A' - 10;
		str[2] = ' ';
		str[5] = '\0';
	}
	else
	{
		res = i % 16;
		i /= 16;
		if (res > 9)
			str[3] = res + 'A' - 10;
		else
			str[3] = res + '0';
		if (i > 9)
			str[1] = i + 'A' - 10;
		else
			str[1] = i + '0';
		str[2] = ' ';
		str[5] = '\0';
	}
	return (str);
}

void			complete(SDL_Renderer *renderer)
{
	int		i;
	int		y;

	i = 15;
	y = 15;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	while (i < 1295)
	{
		y += 20;
		SDL_RenderDrawLine(renderer, 15, y, 2250, y);
		i += 20;
	}
}
