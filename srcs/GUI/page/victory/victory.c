/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   victory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 14:00:00 by lle-duc           #+#    #+#             */
/*   Updated: 2026/10/29 14:00:00 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Window.h"
#include "menus/menus.h"

/* Initialise les textes de l'écran de fin. */
void    init_victory_texts(t_game *game)
{
    t_victory *menu = &game->window->menus.victory;

    menu->texts[0].size = 150;
    menu->texts[0].color = (SDL_Color){255, 215, 0, 255};
    menu->texts[1].size = 70;
    menu->texts[1].color = (SDL_Color){255, 255, 255, 255};
    create_text(&menu->texts[0], game->window->renderPTR, game->languages->the_end, DNFONT);
    create_text(&menu->texts[1], game->window->renderPTR, game->languages->beat_the_game, DNFONT);
}

/* Renvoie 1 si le boss du dernier niveau est mort. */
int is_final_boss_dead(t_game *game)
{
    t_entity *e;
    int bosses = 0;

    if (game->current_level != 3)
        return (0);
    for (int i = 0; i < game->entities.count; i++)
    {
        e = &game->entities.list[i];
        if (e->type != ENTITY_BOSS)
            continue ;
        if (e->status != E_STATUS_DEAD)
            return (0);
        bosses++;
    }
    return (bosses > 0);
}

/* Affiche l'écran de fin pendant VICTORY_DURATION secondes puis revient au menu. */
void    draw_victory_menu(t_game *game)
{
    t_WIN *win = game->window;
    t_victory *menu = &win->menus.victory;
    t_font *title = &menu->texts[0];
    t_font *subtitle = &menu->texts[1];

    if (!game->is_victory)
    {
        game->is_victory = 1;
        menu->begin_time = SDL_GetTicks64();
    }

    if (SDL_GetTicks64() - menu->begin_time > VICTORY_DURATION * 1000)
    {
        game->is_victory = 0;
        if (game->clientConnection.is_connected)
            close_connection(game);
        game->window->menus.current = 1;
    }

    SDL_Rect coords = {0, 0, 1920, 1080};
    to_responsive(win, &coords);

    t_RGB black = {0, 0, 0, 200};
    create_rectangle(win->renderPTR, coords, black);

    draw_texture(1920 / 2 - title->w / 2, 1080 / 2 - title->h, title->w, title->h, win, title->texture);
    draw_texture(1920 / 2 - subtitle->w / 2, 1080 / 2 + 20, subtitle->w, subtitle->h, win, subtitle->texture);
}
