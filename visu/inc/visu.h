/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobecque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:06:43 by cobecque          #+#    #+#             */
/*   Updated: 2017/12/05 19:01:54 by cobecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
#define VISU_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <stdio.h>
#include <stdlib.h>

SDL_Rect		*ft_rects(void);
char			*hexa(int i);
void			fill(int p, SDL_Rect *rects, SDL_Renderer *r, int i);
void			all(SDL_Renderer *r, SDL_Rect *rects, SDL_Texture **texte);
void			complete(SDL_Renderer *renderer);

#endif
