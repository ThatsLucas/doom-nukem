/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_music.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 10:46:20 by lle-duc           #+#    #+#             */
/*   Updated: 2026/10/27 11:04:35 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "sounds/sounds.h"

void	play_music(t_SOUNDS *sounds, Mix_Music *music)
{
	if (!music)
		return ;
	if (sounds->current_music == music && Mix_PlayingMusic())
		return ;
	if (Mix_PlayMusic(music, -1) == -1)
	{
		SDL_Log("Mix_PlayMusic: %s", Mix_GetError());
		return ;
	}
	sounds->current_music = music;
}
