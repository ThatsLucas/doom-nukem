/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 10:50:07 by lle-duc           #+#    #+#             */
/*   Updated: 2026/10/27 10:54:19 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOUNDS_H

#define SOUNDS_H
#include <SDL_mixer.h>

# define AUDIO_FREQUENCY 44100
# define AUDIO_CHUNKSIZE 1024
# define AUDIO_CHANNELS 16

# define MENU_MUSIC_PATH "assets/sounds/menu_music.ogg"
# define INGAME_MUSIC_PATH "assets/sounds/ingame_music.ogg"
# define SHOT_SOUND_PATH "assets/sounds/shot.wav"

typedef struct s_SOUNDS
{
    Mix_Chunk *shot; // pour les effets
    Mix_Music *menu_music; // musique menu
    Mix_Music *ingame_music; // musique en jeu
    Mix_Music *current_music; // musique en cours de lecture
}	t_SOUNDS;

void	init_sounds(t_SOUNDS *sounds);
void	free_sounds(t_SOUNDS *sounds);
void	play_music(t_SOUNDS *sounds, Mix_Music *music);
int		play_sound(Mix_Chunk *chunk);

#endif