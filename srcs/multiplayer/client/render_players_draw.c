/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_players_draw.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:26:24 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:26:24 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>

#include "Game.h"
#include "multiplayer/client.h"

/* Vérifie si la colonne du sprite est masquée. */
static int is_column_occluded(t_game *game, int x, float depth)
{
    t_ray *ray;

    ray = &game->rays[x];
    return (ray->wall_idx >= 0 && ray->perp_dist > 0.0f && ray->perp_dist < FLT_MAX && depth >= ray->perp_dist);
}

/* Dessine une portion verticale du sprite. */
static void draw_sprite_span(t_game *game, t_player_sprite *sprite, int start, int end)
{
    SDL_Rect src;
    SDL_Rect dst;

    src = sprite->src;
    src.x = sprite->src.x + (start - sprite->dest.x) * sprite->src.w / sprite->dest.w;
    src.w = sprite->src.x + (end - sprite->dest.x) * sprite->src.w / sprite->dest.w - src.x;
    if (src.w <= 0)
        return;
    dst = (SDL_Rect){start, sprite->dest.y, end - start, sprite->dest.h};
    SDL_RenderCopy(game->window->renderPTR, sprite->tex, &src, &dst);
}

/* Dessine le sprite d’un joueur distant. */
void draw_player_sprite(t_game *game, t_player_sprite *sprite)
{
    int x;
    int end;
    int span_start;

    x = sprite->dest.x < 0 ? 0 : sprite->dest.x;
    end = sprite->dest.x + sprite->dest.w;
    if (end > game->screenSize[0])
        end = game->screenSize[0];
    while (x < end)
    {
        while (x < end && is_column_occluded(game, x, sprite->depth))
            x++;
        span_start = x;
        while (x < end && !is_column_occluded(game, x, sprite->depth))
            x++;
        if (x > span_start)
            draw_sprite_span(game, sprite, span_start, x);
    }
}
