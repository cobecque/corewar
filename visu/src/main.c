/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 13:05:10 by cobecque          #+#    #+#             */
/*   Updated: 2017/12/17 09:27:40 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
*/
#include "visu.h"
#include <unistd.h>

int		main(void)
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Surface		*surf;
	SDL_Rect		position;
	SDL_Rect		rpos;
	SDL_Texture		*image;
	SDL_Texture		*renderer3;
	SDL_Texture		*r;
	SDL_Texture		*r2;
	SDL_Texture		**texte2;
	SDL_Surface		**texte;
	SDL_Color		color = {0, 0, 0, 255};
	SDL_Event		event;
	TTF_Font		*police;
	TTF_Font		*police2;
	int				bol;
	int				w;
	int				dat;
	int				h;
	int				i;
	int				yolo;
	int				si;
	SDL_Rect		*rects;
	SDL_Rect		sans;
	char			*str;
	int				d;
	int				cy;
	int				ctd;
	int				pros;
	int				ld;
	int				salut;

	cy = 0;
	salut = 1;
	pros = 1;
	ctd = 1536;
	rects = ft_rects();
	yolo = 0;
	ld = 0;
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		si = 0;
		i = 0;
		TTF_Init();
		bol = 0;
		window = NULL;
		renderer = NULL;
		surf = NULL;
		police = TTF_OpenFont("police/stocky.ttf", 25);
		police2 = TTF_OpenFont("police/code2000.ttf", 15);
		//	SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
		window = SDL_CreateWindow("hello", 0, 0, 2500, 1400, SDL_WINDOW_FULLSCREEN_DESKTOP);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		renderer3 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, 2250, 1295);
		r = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, 2550, 1295);
		r2 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, 2550, 1400);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		surf = SDL_GetWindowSurface(window);
		image = IMG_LoadTexture(renderer, "fond/Sans.jpg");
		SDL_QueryTexture(image, NULL, NULL, &w, &h);
		if (!(texte = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 225)))
			return (0);
		if (!(texte2 = (SDL_Texture **)malloc(sizeof(SDL_Texture *) * 225)))
			return (0);
		while (i < 225)
		{
			str = hexa(i);
			texte[i] = TTF_RenderText_Solid(police, str, color);
			texte2[i] = SDL_CreateTextureFromSurface(renderer, texte[i]);
			i++;
			free(str);
		}
		d = 0;
		si = 0;
		sans.x = 2253;
		sans.y = 1035;
		sans.w = 2550 - 2253;
		sans.h = 1295 - 1035;
		position.x = 0;
		position.y = 0;
		position.w = 2250;
		position.h = 1295;
		SDL_SetRenderTarget(renderer, renderer3);
		all(renderer, rects, texte2);
	//	champ(renderer, police2);
		SDL_SetRenderTarget(renderer, NULL);
		SDL_SetRenderTarget(renderer, r);
		SDL_RenderCopy(renderer, renderer3, NULL, &position);
		champ(renderer, police2);
		SDL_SetRenderTarget(renderer, NULL);
		dat = 0;
		while (bol != 2)
		{
			i = 0;
			SDL_SetRenderTarget(renderer, r);
			SDL_RenderCopy(renderer, image, NULL, &sans);
			//	if (yolo == 0)
			//	all(renderer, rects, texte2);
			//	all(renderer, rects, texte2);
			ft_pause(renderer, police2, si);
			ft_process(renderer, police2, cy);
			ft_define(renderer);
		//	complete(renderer);
			ft_cycle(renderer, police2, cy);
			//	champ(renderer, police2);
			//	ft_process(renderer, police2, cy);
			//	ft_define(renderer);
			if ((cy % 100 == 0 && cy != 0 ) || cy == 8 || cy == d + 1536 - 20 || (salut == 0 && cy == d && cy != 0))
				ld += 150;
			SDL_SetRenderTarget(renderer, NULL);
			SDL_SetRenderTarget(renderer, r2);
			rpos.x = 0;
			rpos.y = 0;
			rpos.w = 2550;
			rpos.h = 1295;
			SDL_RenderCopy(renderer, r, NULL, &rpos);
			if (yolo % 10 == 0)
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			else
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRect(renderer, &rects[10]);
			SDL_RenderCopy(renderer, texte2[10], NULL, &rects[10]);
			ft_load(renderer, ld, salut);
			SDL_SetRenderTarget(renderer, NULL);
			SDL_SetRenderTarget(renderer, r);
//			complete(renderer);
			yolo++;
			cy += 1;
			if (cy % 800 == 0)
				pros *= 2;
			if (cy == d + 1536)
			{
				ctd -= 50;
				ld = 0;
				if (salut == 1)
					salut = 0;
				else if (salut == 0)
					salut = 1;
				d = cy;
			}
			ft_die(renderer, police2, ctd);
			position.x = 0;
			position.y = 0;
			position.w = 2250;
			position.h = 1295;
			SDL_SetRenderTarget(renderer, NULL);
			SDL_RenderCopy(renderer, renderer3, NULL, &position);
			SDL_RenderCopy(renderer, r, NULL, &rpos);
			rpos.x = 0;
			rpos.y = 0;
			rpos.w = 2550;
			rpos.h = 1400;
			SDL_RenderCopy(renderer, r2, NULL, &rpos);
			SDL_RenderPresent(renderer);
			if (bol == 3)
			{
				if (event.key.keysym.sym == SDLK_SPACE && si == 0)
				{
					ft_pause(renderer, police2, 1);
					SDL_RenderPresent(renderer);
					SDL_WaitEvent(&event);
					cy--;
					si++;
				}
				else if (si == 1 && event.key.keysym.sym == SDLK_SPACE)
					si++;
				else
					si = 0;
				bol = 1;
			}
			while (SDL_PollEvent(&event))
			{
				if (event.key.keysym.sym == SDLK_SPACE)
					bol = 3;
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					bol = 2;
					TTF_CloseFont(police);
					TTF_CloseFont(police2);
					TTF_Quit();
					SDL_Quit();
				}
			}
			while (SDL_PollEvent(&event) && si != 2)
			{
				if (event.key.keysym.sym == SDLK_SPACE)// && si != 1)
					si++;
			}
			if (si == 2)
				si = 0;
			/*	else if (event.key.keysym.sym == SDLK_SPACE && si == 1)
				si++;
				else if (si == 2)
				{
				si = 0;
				}
				while (SDL_PollEvent(&event))
				SDL_FlushEvent(event.key.keysym.sym);
				*/}
			if (rects)
				free(rects);
			if (renderer)
				SDL_DestroyRenderer(renderer);
			if (window)
				SDL_DestroyWindow(window);
			if (image)
				SDL_DestroyTexture(image);
			if (surf)
				SDL_FreeSurface(surf);
			if (renderer3)
				SDL_DestroyTexture(renderer3);
			i = 0;
			while (i < 225)
			{
				SDL_FreeSurface(texte[i]);
				SDL_DestroyTexture(texte2[i]);
				i++;
			}
	}
	//TTF_Quit();
	//	SDL_Quit();
	return (0);
}

