/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:06:43 by cobecque          #+#    #+#             */
/*   Updated: 2017/12/13 23:52:20 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
#define VISU_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

SDL_Rect		*ft_rects(void);
char			*hexa(int i);
void			fill(int p, SDL_Rect *rects, SDL_Renderer *r, int i);
void			all(SDL_Renderer *r, SDL_Rect *rects, SDL_Texture **texte);
void			complete(SDL_Renderer *renderer);
void			champ(SDL_Renderer *renderer, TTF_Font *police);
void			ft_pause(SDL_Renderer *renderer, TTF_Font *police, int i);
void			ft_cycle(SDL_Renderer *renderer, TTF_Font *police, int cycle);
void			ft_process(SDL_Renderer *renderer, TTF_Font *police, int pros);
void			ft_die(SDL_Renderer *r, TTF_Font *police, int ctd);
void			ft_define(SDL_Renderer *r);
void			ft_load(SDL_Renderer *r, int ld, int bol);

#endif
