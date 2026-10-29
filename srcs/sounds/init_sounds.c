/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sounds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 10:49:13 by lle-duc           #+#    #+#             */
/*   Updated: 2026/10/27 11:08:10 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "sounds/sounds.h"

static Mix_Chunk	*load_chunk(const char *path)
{
	Mix_Chunk	*chunk;

	chunk = Mix_LoadWAV(path);
	if (!chunk)
		SDL_Log("Mix_LoadWAV %s: %s", path, Mix_GetError());
	return (chunk);
}

static Mix_Music	*load_music(const char *path)
{
	Mix_Music	*music;

	music = Mix_LoadMUS(path);
	if (!music)
		SDL_Log("Mix_LoadMUS %s: %s", path, Mix_GetError());
	return (music);
}

void	init_sounds(t_SOUNDS *sounds)
{
	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		SDL_Log("SDL audio init: %s", SDL_GetError());
		return ;
	}
	if (Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, 2,
			AUDIO_CHUNKSIZE) < 0)
	{
		SDL_Log("Mix_OpenAudio: %s", Mix_GetError());
		return ;
	}
	Mix_AllocateChannels(AUDIO_CHANNELS);
	sounds->shot = load_chunk(SHOT_SOUND_PATH);
	sounds->rocket = load_chunk(ROCKET_SOUND_PATH);
	sounds->item_get = load_chunk(ITEM_GET_SOUND_PATH);
	sounds->menu_music = load_music(MENU_MUSIC_PATH);
	sounds->ingame_music = load_music(INGAME_MUSIC_PATH);
}

void	free_sounds(t_SOUNDS *sounds)
{
	Mix_HaltMusic();
	Mix_FreeChunk(sounds->shot);
	Mix_FreeChunk(sounds->rocket);
	Mix_FreeChunk(sounds->item_get);
	Mix_FreeMusic(sounds->menu_music);
	Mix_FreeMusic(sounds->ingame_music);
	sounds->shot = NULL;
	sounds->rocket = NULL;
	sounds->item_get = NULL;
	sounds->menu_music = NULL;
	sounds->ingame_music = NULL;
	sounds->current_music = NULL;
	Mix_CloseAudio();
}
