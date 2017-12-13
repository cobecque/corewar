/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 13:05:10 by cobecque          #+#    #+#             */
/*   Updated: 2017/12/13 21:24:49 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
*/
#include "visu.h"

int		main(void)
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Surface		*surf;
	SDL_Rect		position;
	SDL_Texture		*image;
	SDL_Texture		**texte2;
	SDL_Surface		**texte;
	SDL_Color		color = {0, 0, 0, 255};
	SDL_Event		event;
	TTF_Font		*police;
	int				bol;
	int				w;
	int				h;
	int				i;
	int				yolo;
	int				si;
	SDL_Rect		*rects;
	char			*str;
	int				d;
	int				cy;

	cy = 0;
	rects = ft_rects();
	yolo = 0;
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
		SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		surf = SDL_GetWindowSurface(window);
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
		while (bol != 2)
		{
			i = 0;
			h = 0;
			w = 0;
			position.x = 0;
			image = NULL;
			/*image = IMG_LoadTexture(renderer, "fond/appel.jpg");
			  SDL_QueryTexture(image, NULL, NULL, &w, &h);
			  position.x = 0;
			  position.y = 1295;
			  position.w = 200;
			  position.h = 200;
			  i = 0;
			  while (i < 12)
			  {
			  SDL_RenderCopy(renderer, image, NULL, &position);
			  position.x += 200;
			  i++;
			  }
			  position.x = 2400;
		*/	/*  SDL_RenderCopy(renderer, image, NULL, &position);
					image = IMG_LoadTexture(renderer, "fond/spectrum.jpg");
					SDL_QueryTexture(image, NULL, NULL, &w, &h);
					position.x = 2220;
					position.y = 15;
				position.w = 2550 - 2220;
					position.h = 1295 - 15;
					SDL_RenderCopy(renderer, image, NULL, &position);*/
				all(renderer, rects, texte2);
				ft_pause(renderer, police, si);
				champ(renderer, police);
				ft_cycle(renderer, police, cy);
				if (yolo % 2 == 0)
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
				else
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(renderer, &rects[10]);
				SDL_RenderCopy(renderer, texte2[10], NULL, &rects[10]);
				complete(renderer);
				yolo++;
				SDL_RenderPresent(renderer);
				cy++;
			if (bol == 3)
			{
				if (event.key.keysym.sym == SDLK_SPACE && si == 0)
				{
					ft_pause(renderer, police, 1);
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

