/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:40:28 by cobecque          #+#    #+#             */
/*   Updated: 2017/12/17 09:27:41 by cobecque         ###   ########.fr       */
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
			i++;
			h++;
		}
		j++;
	}
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

//	police = TTF_OpenFont("police/code2000.ttf", 15);
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
	SDL_DestroyTexture(texte2);
	SDL_FreeSurface(texte);
//	TTF_CloseFont(police);
}

void			ft_cycle(SDL_Renderer *renderer, TTF_Font *police, int cycle)
{
	char		*str;
	SDL_Rect	rect;
	SDL_Surface	*texte;
	SDL_Texture	*texte2;
	SDL_Color	color = {255, 255, 255, 255};


//	police = TTF_OpenFont("police/code2000.ttf", 15);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	rect.x = 2253;
	rect.y = 705;
	rect.w = 2550 - 2253;
	rect.h = 60;
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &rect);
	rect.y = rect.y + 20;
	rect.w = 185;
	rect.h = 30;
	str = ft_strjoin("  Cycle : ", ft_itoa(cycle));
	texte = TTF_RenderText_Solid(police, str, color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	SDL_DestroyTexture(texte2);
	SDL_FreeSurface(texte);
//	TTF_CloseFont(police);
}

void			ft_process(SDL_Renderer *renderer, TTF_Font *police, int pros)
{
	char		*str;
	SDL_Rect	rect;
	SDL_Surface	*texte;
	SDL_Texture	*texte2;
	SDL_Color	color = {255, 255, 255, 255};

	printf("fonction processi cycle %d\n", pros);
	//police = TTF_OpenFont("police/code2000.ttf", 15);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	rect.x = 2253;
	rect.y = 765;
	rect.w = 2550 - 2253;
	rect.h = 60;
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &rect);
	rect.y = rect.y + 15;
	rect.w = 185;
	rect.h = 30;
	str = ft_strjoin("  Process : ", ft_itoa(pros));
	texte = TTF_RenderText_Solid(police, str, color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	SDL_FreeSurface(texte);
	SDL_DestroyTexture(texte2);
	//TTF_CloseFont(police);
}

void			ft_die(SDL_Renderer *r, TTF_Font *police, int ctd)
{
	char		*str;
	SDL_Rect	rect;
	SDL_Surface	*texte;
	SDL_Texture	*texte2;
	SDL_Color	color= {255, 255, 255, 255};

//	police = TTF_OpenFont("police/code2000.ttf", 15);
	SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
	rect.x = 2253;
	rect.y = 825;
	rect.w = 2550 - 2253;
	rect.h = 50;
	SDL_RenderFillRect(r, &rect);
	SDL_SetRenderDrawColor(r, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(r, &rect);
	rect.y = rect.y + 15;
	rect.w = 250;
	rect.h = 20;
	str = ft_strjoin("  Cycle to die : ", ft_itoa(ctd));
	texte = TTF_RenderText_Solid(police, str, color);
	texte2 = SDL_CreateTextureFromSurface(r, texte);
	SDL_RenderCopy(r, texte2, NULL, &rect);
	SDL_FreeSurface(texte);
	SDL_DestroyTexture(texte2);
}

void			ft_load(SDL_Renderer *renderer, int ld, int bol)
{
	SDL_Rect	rect;

	rect.x = 15;
	rect.y = 1305;
	rect.w = 2550 - 15;
	rect.h = 100;
	if (bol == 1)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		//SDL_RenderDrawRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
		rect.x = 15;
		rect.y = 1305;
		rect.w = ld;
		if (rect.w > 2550 - 15)
			rect.w = 2550 - 15;
		rect.h = 100;
		SDL_RenderFillRect(renderer, &rect);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	//	SDL_RenderDrawRect(renderer, &rect);
		rect.x = 2550;
		rect.y = 1305;
		rect.w = -ld;
		if (rect.w < -2550 + 15)
			rect.w = -2550 + 15;
		rect.h = 100;
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &rect);
	}
}

void			ft_define(SDL_Renderer *r)
{
	SDL_Rect	rect;
	SDL_Surface	*texte;
	SDL_Texture	*texte2;
	SDL_Color	color = {255, 255, 255, 255};
	TTF_Font	*police;

	police = TTF_OpenFont("police/code2000.ttf", 15);
	SDL_SetRenderDrawColor(r, 0, 0 ,0, SDL_ALPHA_OPAQUE);
	rect.x = 2253;
	rect.y = 875;
	rect.w = 2550 - 2253;
	rect.h = 160;
	SDL_RenderFillRect(r, &rect);
	SDL_SetRenderDrawColor(r, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(r, &rect);
	rect.y = rect.y + 25;
	rect.w = 250;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, "  Cycle delta : 50 ", color);
	texte2 = SDL_CreateTextureFromSurface(r, texte);
	SDL_RenderCopy(r, texte2, NULL, &rect);
	rect.y = rect.y + 45;
	rect.w = 250;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, "  Number live :  21 ", color);
	texte2 = SDL_CreateTextureFromSurface(r, texte);
	SDL_RenderCopy(r, texte2, NULL, &rect);
	rect.y = rect.y + 45;
	rect.w = 250;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, "  Max Checks   :  21 ", color);
	texte2 = SDL_CreateTextureFromSurface(r, texte);
	SDL_RenderCopy(r, texte2, NULL, &rect);
	TTF_CloseFont(police);
}

void			champ(SDL_Renderer *renderer, TTF_Font *police)
{
	SDL_Rect	rect;
	SDL_Surface	*texte;
	SDL_Texture	*texte2;
	SDL_Color	color = {255, 0, 0, 255};

//	police = TTF_OpenFont("police/code2000.ttf", 15);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	rect.x = 2253;
	rect.y = 65;
	rect.w = 2550 - 2253;
	rect.h = 180;
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
	rect.w = 250;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, "  dat fucking comment ye ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	rect.y = rect.y + 25;
	rect.w = 250;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, "  is really long you cant ", color);
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
	rect.h = 180;
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
	rect.w = 250;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, " dat fucking comment ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	rect.y = rect.y + 25;
	rect.w = 250;
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
	rect.h = 180;
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
	rect.w = 250;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, " dat fucking comment ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	rect.y = rect.y + 25;
	rect.w = 250;
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
	rect.h = 180;
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
	rect.w = 250;
	rect.h = 20;
	texte = TTF_RenderText_Solid(police, " dat fucking comment ", color);
	texte2 = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_RenderCopy(renderer, texte2, NULL, &rect);
	rect.y = rect.y + 25;
	rect.w = 250;
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
	SDL_FreeSurface(texte);
	SDL_DestroyTexture(texte2);
	//TTF_CloseFont(police);
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
	/*SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, 2253, 1295, 2550, 1295);
	SDL_RenderDrawLine(renderer, 2253, 15, 2550, 15);
	SDL_RenderDrawLine(renderer, 2550, 15, 2550, 1295);
*/}

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
