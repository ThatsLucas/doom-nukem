/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 00:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/05/29 17:57:21 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <math.h>

#include "Game.h"
#include "multiplayer/client.h"

static SDL_Texture *get_player_texture(t_game *game, int tex_index)
{
    t_lobby *menu;

    menu = &game->window->menus.lobby;
    return (menu->playerImgs[tex_index % 5].texture);
}

static void draw_player_sprite(t_game *game, float depth, int center_x, int size, int index)
{
    SDL_Rect dest;
    int screen_h;
    int sprite_h;
    int tex_w;
    int tex_h;
    SDL_Texture *texture;

    if (size <= 0 || depth <= 0.05f)
        return;
    screen_h = game->screenSize[1];
    texture = get_player_texture(game, index);
    if (!texture)
        return;
    if (SDL_QueryTexture(texture, NULL, NULL, &tex_w, &tex_h) < 0 || tex_w <= 0 || tex_h <= 0)
        return;
    float camera_scale = tanf(game->settings.FOV * 0.5f);
    float focal = (float)game->screenSize[0] / (2.0f * camera_scale);
    float player_world_h = 1.8f;
    float base_h = (player_world_h * focal) / depth;
    const float NEAR_BOOST_DIST = 1.2f;
    const float BOOST_MAX = 2.2f;
    float boost = 1.0f;
    if (depth < NEAR_BOOST_DIST)
    {
        float t = (NEAR_BOOST_DIST - depth) / NEAR_BOOST_DIST;
        t = t * t * (3.0f - 2.0f * t);
        boost = 1.0f + t * (BOOST_MAX - 1.0f);
    }
    sprite_h = (int)(base_h * boost);

    int min_sprite_h = 24;
    int max_sprite_h = (int)((float)screen_h * 0.95f);
    if (sprite_h < min_sprite_h)
        sprite_h = min_sprite_h;
    if (sprite_h > max_sprite_h)
        sprite_h = max_sprite_h;
    dest.w = (int)((float)sprite_h * ((float)tex_w / (float)tex_h));

    int max_sprite_w = (int)((float)game->screenSize[0] * 0.75f);
    if (dest.w > max_sprite_w)
        dest.w = max_sprite_w;
    dest.h = sprite_h;
    dest.x = center_x - dest.w / 2;

    int floor_y = screen_h - 190; // valeir a modif pour baisser le joueur
    if (center_x >= 0 && center_x < game->screenSize[0])
    {
        int ry = game->rays[center_x].y_wall_bot;
        if (ry > 0 && ry < screen_h)
            floor_y = ry;
    }

    int extra_offset = (int)((float)dest.h * 0.45f) + 24;
    if (extra_offset > screen_h / 3)
        extra_offset = screen_h / 3;
    dest.y = floor_y - dest.h + extra_offset;
    if (dest.x + dest.w <= 0 || dest.x >= game->screenSize[0])
        return;
    if (dest.y + dest.h <= 0 || dest.y >= screen_h)
        return;

    int start_x = dest.x < 0 ? 0 : dest.x;
    int end_x = dest.x + dest.w;
    if (end_x > game->screenSize[0])
        end_x = game->screenSize[0];

    int x = start_x;
    while (x < end_x)
    {
        int occluded = (game->rays[x].wall_idx >= 0 && game->rays[x].perp_dist > 0.0f && game->rays[x].perp_dist < FLT_MAX && depth >= game->rays[x].perp_dist);
        if (occluded)
        {
            x++;
            continue;
        }
        int span_start = x;
        while (x < end_x)
        {
            int oc = (game->rays[x].wall_idx >= 0 && game->rays[x].perp_dist > 0.0f && game->rays[x].perp_dist < FLT_MAX && depth >= game->rays[x].perp_dist);
            if (oc)
                break;
            x++;
        }
        int span_end = x;
        int span_w = span_end - span_start;
        if (span_w <= 0)
            continue;

        SDL_Rect src;
        src.y = 0;
        src.h = tex_h;
        float rel_x = (float)(span_start - dest.x) / (float)dest.w;
        float rel_w = (float)span_w / (float)dest.w;
        src.x = (int)floorf(rel_x * (float)tex_w);
        src.w = (int)ceilf(rel_w * (float)tex_w);
        if (src.x < 0)
            src.x = 0;
        if (src.x + src.w > tex_w)
            src.w = tex_w - src.x;
        if (src.w <= 0)
            continue;

        SDL_Rect dest_span = {span_start, dest.y, span_w, dest.h};
        SDL_RenderCopyEx(game->window->renderPTR, texture, &src, &dest_span, 0.0, NULL, SDL_FLIP_NONE);
    }
}

void render_multiplayer_players(t_game *game)
{
    float camera_scale;
    t_vect2 dir;
    t_vect2 plane;
    float det;
    float inv_det;

    if (!game->clientConnection.is_connected || game->clientConnection.player_count <= 0)
        return;
    dir = game->ply->dir;
    camera_scale = tanf(game->settings.FOV * 0.5f);
    plane = get_cam_plane(camera_scale, dir);
    det = plane.x * dir.y - dir.x * plane.y;
    if (fabsf(det) < 0.00001f)
        return;
    inv_det = 1.0f / det;
    static double prev_pos[4][2] = {{0}};
    static double smoothed_speed[4] = {0.0, 0.0, 0.0, 0.0};
    static Uint64 last_moved_tick[4] = {0, 0, 0, 0};
    const double EMA_ALPHA = 0.15;
    const double WALK_THRESHOLD = 0.005;
    const Uint64 WALK_LINGER_MS = 300;
    for (int i = 0; i < game->clientConnection.player_count && i < 4; i++)
    {
        if (i == game->clientConnection.selfIndex) // pour pas se drw soit meme
            continue;
        float player_x = (float)game->clientConnection.players[i][0];
        float player_y = (float)game->clientConnection.players[i][1];
        float sprite_x = player_x - game->ply->pos.x;
        float sprite_y = player_y - game->ply->pos.y;
        float transform_x;
        float transform_y;
        int sprite_h;
        int sprite_w;
        int sprite_screen_x;

        if (fabsf(sprite_x) < 0.001f && fabsf(sprite_y) < 0.001f)
            continue;
        transform_x = inv_det * (dir.y * sprite_x - dir.x * sprite_y);
        transform_y = inv_det * (-plane.y * sprite_x + plane.x * sprite_y);
        if (transform_y <= 0.05f)
            continue;
        sprite_h = (int)fabsf(game->screenSize[1] / transform_y);
        sprite_w = sprite_h / 2;
        if (sprite_w < 4)
            sprite_w = 4;
        sprite_screen_x = (int)((game->screenSize[0] / 2.0f) * (1.0f + transform_x / transform_y));
        int tex_idx = 0;
        double prevx = prev_pos[i][0];
        double prevy = prev_pos[i][1];
        double dx = player_x - prevx;
        double dy = player_y - prevy;
        double measured = sqrt(dx * dx + dy * dy);
        smoothed_speed[i] = smoothed_speed[i] * (1.0 - EMA_ALPHA) + measured * EMA_ALPHA;
        if (smoothed_speed[i] > WALK_THRESHOLD)
            last_moved_tick[i] = SDL_GetTicks64();
        Uint64 now = SDL_GetTicks64();
        int is_walking = (smoothed_speed[i] > WALK_THRESHOLD) || (now - last_moved_tick[i] <= WALK_LINGER_MS);
        double to_cx = (double)game->ply->pos.x - player_x;
        double to_cy = (double)game->ply->pos.y - player_y;
        double ang = game->clientConnection.player_angles[i];
        double to_cam_ang = atan2(to_cy, to_cx);
        double diff = to_cam_ang - ang;
        while (diff > M_PI)
            diff -= 2.0 * M_PI;
        while (diff < -M_PI)
            diff += 2.0 * M_PI;
        int facing_towards_camera = (fabs(diff) < (M_PI / 2.0));
        if (is_walking)
            tex_idx = facing_towards_camera ? 1 : 4; /* front_walk : back_walk */
        else
            tex_idx = facing_towards_camera ? 0 : 3; /* front_idle : back_idle */
        SDL_Texture *tex = get_player_texture(game, tex_idx);
        if (tex)
            draw_player_sprite(game, transform_y, sprite_screen_x, sprite_w, tex_idx);
        else
            draw_player_sprite(game, transform_y, sprite_screen_x, sprite_w, i);
        prev_pos[i][0] = player_x;
        prev_pos[i][1] = player_y;
    }
}