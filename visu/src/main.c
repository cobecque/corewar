/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 13:05:10 by cobecque          #+#    #+#             */
/*   Updated: 2017/12/04 18:46:09 by cobecque         ###   ########.fr       */
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
//	SDL_Renderer	*ren;
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
	SDL_Rect		*rects;
	char			*str;

	rects = ft_rects();
	yolo = 0;
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		i = 0;
		TTF_Init();
		bol = 0;
		window = NULL;
		renderer = NULL;
		surf = NULL;
		while (bol != 2)
		{
			if (bol != 1)
			{
				police = TTF_OpenFont("police/Escapee.ttf", 15);
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
					//if (i % 15 >= 10)
					//	police = TTF_OpenFont("police/apple.ttf", 15);
					//else
					//	police = TTF_OpenFont("police/Escapee.ttf", 15);
					texte[i] = TTF_RenderText_Solid(police, str, color);
					texte2[i] = SDL_CreateTextureFromSurface(renderer, texte[i]);
					i++;
				}
				i = 0;
				image = IMG_LoadTexture(renderer, "fond/appel.jpg");
				SDL_QueryTexture(image, NULL, NULL, &w, &h);
				position.x = 0;
				position.y = 1295;
				position.w = 200;
				position.h = 200;
				while (i < 12)
				{
			//		SDL_RenderCopy(renderer, image, NULL, &position);
					position.x += 200;
					i++;
				}
				position.x = 2400;
			//	SDL_RenderCopy(renderer, image, NULL, &position);
				image = IMG_LoadTexture(renderer, "fond/spectrum.jpg");
				SDL_QueryTexture(image, NULL, NULL, &w, &h);
				position.x = 1935;
				position.y = 15;
				position.w = 2550 - 1935;
				position.h = 1295 - 15;
			//	SDL_RenderCopy(renderer, image, NULL, &position);
				//		SDL_Delay(2000);
				/*SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
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
					SDL_RenderCopy(renderer, texte2, NULL, &rects[i]);
					i++;
				}
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawLine(renderer, 1935, 1295, 2550, 1295);
				SDL_RenderDrawLine(renderer, 1935, 15, 2550, 15);
				SDL_RenderDrawLine(renderer, 2550, 15, 2550, 1295);
			*///	SDL_RenderPresent(renderer);
				//ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			//	SDL_SetRenderDrawColor(ren, 255, 0, 0, SDL_ALPHA_OPAQUE);
		//		SDL_RenderClear(ren);
		//		SDL_SetRenderDrawColor(ren, 255, 0, 0, SDL_ALPHA_OPAQUE);
		//		SDL_RenderDrawRect(ren, &rects[5]);
		///		SDL_RenderFillRect(ren, &rects[5]);
	//		SDL_RenderPresent(ren);
				bol = 1;
			}
			if (bol == 1)
			{
				all(renderer, rects, texte2);
				if (yolo % 2 == 0)
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
				else
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(renderer, &rects[5]);
				SDL_RenderCopy(renderer, texte2[5], NULL, &rects[5]);
				yolo++;
			}
			SDL_Delay(200);
			SDL_RenderPresent(renderer);
			while (SDL_PollEvent(&event))
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					bol = 2;
			}
		}
		if (renderer)
			SDL_DestroyRenderer(renderer);
		if (window)
			SDL_DestroyWindow(window);
		if (image)
			SDL_DestroyTexture(image);
		TTF_CloseFont(police);
		SDL_FreeSurface(*texte);
	}
	TTF_Quit();
	SDL_Quit();
	return (0);
}
