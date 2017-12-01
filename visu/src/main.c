/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 13:05:10 by cobecque          #+#    #+#             */
/*   Updated: 2017/12/01 17:07:01 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

int		main(void)
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Surface		*surf;
	SDL_Rect		position;
	SDL_Texture		*image;
	SDL_Texture		*texte2;
	SDL_Surface		*texte;
	SDL_Color		color = {255, 255, 255, 255};
	SDL_Event		event;
	TTF_Font		*police;
	int				bol;
	int				w;
	int				h;

	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		TTF_Init();
		bol = 0;
		window = NULL;
		renderer = NULL;
		surf = NULL;
		while (bol != 2)
		{
			if (bol != 1)
			{
		police = TTF_OpenFont("angelina.ttf", 65);
				SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);
				//			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				//			SDL_RenderDrawLine(renderer, 320, 200, 300, 240);
				//			SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
				surf = SDL_GetWindowSurface(window);
				texte = TTF_RenderText_Solid(police, "1 C", color);
				texte2 = SDL_CreateTextureFromSurface(renderer, texte);
				image = IMG_LoadTexture(renderer, "appel.jpg");
				SDL_QueryTexture(image, NULL, NULL, &w, &h);
				SDL_Rect texr;
				texr.x = 200;
				texr.y = 0;
				texr.w = w;
				texr.h = h;
				//		SDL_BlitSurface(image, NULL, surf, NULL);
				//		SDL_UpdateWindowSurface(window);
				//		SDL_Delay(2000);
				SDL_RenderClear(renderer);
			//	SDL_RenderCopy(renderer, image, NULL, &texr);
//				SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 255, 255, 255));
		//		SDL_BlitSurface((SDL_Surface *)image, NULL, surf, &position); /* Blit du fond */
				position.x = 60;
				position.y = 370;
				position.w = 500;
				position.h = 500;
		//		SDL_BlitSurface(texte, NULL, surf, &position); /* Blit du texte */
				SDL_RenderCopy(renderer, texte2, NULL, &position);
				SDL_RenderPresent(renderer);
				/*SDL_Delay(2000);
				  image = IMG_LoadTexture(renderer, "test.bmp");
				  SDL_QueryTexture(image, NULL, NULL, &w, &h);
				  texr.x = 0;
				  texr.y = 0;
				  texr.w = w*6;
				  texr.h = h*4;
				  SDL_RenderClear(renderer);
				  SDL_RenderCopy(renderer, image, NULL, &texr);
				  SDL_Delay(2000);*/
				//	SDL_RenderPresent(renderer);
				bol = 1;
			}
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
		SDL_FreeSurface(texte);
	}
	TTF_Quit();
	SDL_Quit();
	return (0);
}
