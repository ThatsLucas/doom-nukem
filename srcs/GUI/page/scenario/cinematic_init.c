/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cinematic_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:14:19 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:14:19 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"
#include "menus/menus.h"

/* Initialise les textes des cinématiques. */
static void *init_texts(void *gameStruct)
{
    t_game *game = (t_game *)gameStruct;
    t_languages *lang = game->languages;
    SDL_Renderer *renderer = game->window->renderPTR;
    t_cinematic *menu = &game->window->menus.cinematic;
    char *lines[16] = {
        lang->cinematic_text_one, lang->cinematic_text_two,
        lang->cinematic_text_three, lang->cinematic_text_four,
        lang->cinematic_text_five, lang->cinematic_text_six,
        lang->cinematic_text_seven, lang->cinematic_text_eight,
        lang->cinematic_text_nine, lang->cinematic_text_ten,
        lang->cinematic_text_eleven, lang->cinematic_text_twelve,
        lang->cinematic_text_thirteen, lang->cinematic_text_fourteen,
        lang->cinematic_text_fifteen, lang->cinematic_text_sixteen};

    for (int i = 0; i < 16; i++)
        create_white_text(&menu->texts[i], renderer, lines[i], 60);
    return ((void *)1);
}

/* Initialise les positions des éléments de la cinématique. */
static void init_cinematic_positions(t_cinematic *cinematic)
{
    cinematic->scientificsXPos[0] = 1700.0f;
    cinematic->scientificsXPos[1] = 1200.0f;
    cinematic->scientificsXPos[2] = 800.0f;
    cinematic->scientificsXPos[3] = 400.0f;
    cinematic->scientificsXPos[4] = 200.0f;
    cinematic->scientifics[0].y = 500;
    cinematic->scientifics[1].y = 500;
    cinematic->scientifics[2].y = 500;
    cinematic->scientifics[3].y = 500;
    cinematic->scientifics[4].y = 500;
    cinematic->smoke.x = 0;
    cinematic->smokeYPos = 600.0f;
    cinematic->blue_light_ratio = 5.0f;
    cinematic->grow_order = -1;
}

/* Définit les images de la cinématique. */
static void set_cinematic_images(t_cinematic *cinematic, t_png **images)
{
    t_png *list[13] = {
        &cinematic->bg_one,
        &cinematic->scientifics[0],
        &cinematic->scientifics[1],
        &cinematic->scientifics[2],
        &cinematic->scientifics[3],
        &cinematic->scientifics[4],
        &cinematic->smoke,
        &cinematic->bg_two,
        &cinematic->blue_light,
        &cinematic->bg_three,
        &cinematic->boss,
        &cinematic->eyes,
        &cinematic->lightning,
    };

    const char *paths[13] = {
        "assets/png/cinematics/one/bg_one.png",
        "assets/png/cinematics/one/scientific_one.png",
        "assets/png/cinematics/one/scientific_two.png",
        "assets/png/cinematics/one/scientific_three.png",
        "assets/png/cinematics/one/scientific_four.png",
        "assets/png/cinematics/one/scientific_five.png",
        "assets/png/cinematics/one/smoke.png",
        "assets/png/cinematics/two/underground_bg.png",
        "assets/png/cinematics/two/blue_glow.png",
        "assets/png/cinematics/three/bg.png",
        "assets/png/cinematics/three/boss.png",
        "assets/png/cinematics/three/eyes.png",
        "assets/png/cinematics/three/lightning.png"};

    for (int i = 0; i < 13; i++)
    {
        images[i] = list[i];
        images[i]->path = ft_strdup(paths[i]);
    }
}

/* Initialise les cinématiques. */
int init_cinematics_menus(t_game *game, SDL_Renderer *renderer,
                          t_cinematic *cinematic)
{
    pthread_t threads[14];
    t_png *images[13];
    void *ret = NULL;
    int finalRet;

    ft_bzero(cinematic, sizeof(t_cinematic));
    init_cinematic_positions(cinematic);
    set_cinematic_images(cinematic, images);

    for (int i = 0; i < 13; i++)
        pthread_create(&threads[i], NULL, process_png, images[i]);

    pthread_create(&threads[13], NULL, init_texts, game);

    finalRet = join_png_threads(threads, images, 13, renderer);
    pthread_join(threads[13], &ret);

    if (!ret)
        finalRet = 0;
    return finalRet;
}
