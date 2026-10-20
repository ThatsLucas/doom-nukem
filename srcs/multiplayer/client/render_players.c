/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 00:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/09/23 12:19:14 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <math.h>

#include "Game.h"
#include "multiplayer/client.h"

#define REMOTE_PLAYER_HEIGHT 1.8f // hauteur en unites monde, comme les entities
#define WALK_LINGER_MS 300        // garde l'anim de marche entre deux paquets reseau
#define WALK_EPSILON 0.001

/* index des textures dans lobby.playerImgs */
#define TEX_FRONT_IDLE 0
#define TEX_FRONT_WALK 1
#define TEX_BACK_IDLE 3
#define TEX_BACK_WALK 4

/*infos de camera communes a tous les joueurs pour une frame*/
typedef struct s_player_cam
{
    t_vect2 pos;
    t_vect2 dir;
    t_vect2 plane;
    float inv_det;
    float focal;
    float z;
    float pitch;
    float half_sw;
    float half_sh;
} t_player_cam;

/*etat d'animation de chaque joueur distant, garde entre les frames*/
typedef struct s_walk_state
{
    double last_pos[2];
    Uint64 last_moved;
} t_walk_state;

static t_player_cam init_player_cam(t_game *game)
{
    t_player_cam cam;
    float camera_scale;

    camera_scale = tanf(game->settings.FOV * 0.5f);
    cam.pos = game->ply->pos;
    cam.dir = game->ply->dir;
    cam.plane = get_cam_plane(camera_scale, cam.dir);
    cam.inv_det = 1.0f / (cam.plane.x * cam.dir.y - cam.dir.x * cam.plane.y);
    cam.half_sw = game->screenSize[0] * 0.5f;
    cam.half_sh = game->screenSize[1] * 0.5f;
    cam.focal = cam.half_sw / camera_scale;
    cam.z = game->ply->z;
    cam.pitch = (float)game->ply->pitch;
    return (cam);
}

static int update_walk_state(t_walk_state *state, double x, double y)
{
    Uint64 now;

    now = SDL_GetTicks64();
    if (fabs(x - state->last_pos[0]) > WALK_EPSILON || fabs(y - state->last_pos[1]) > WALK_EPSILON)
        state->last_moved = now;
    state->last_pos[0] = x;
    state->last_pos[1] = y;
    return (now - state->last_moved <= WALK_LINGER_MS);
}

static int is_facing_camera(t_player_cam *cam, float x, float y, double angle)
{
    double to_cam;
    double diff;

    to_cam = atan2(cam->pos.y - y, cam->pos.x - x);
    diff = to_cam - angle;
    while (diff > M_PI)
        diff -= 2.0 * M_PI;
    while (diff < -M_PI)
        diff += 2.0 * M_PI;
    return (fabs(diff) < M_PI / 2.0);
}

static void pick_player_texture(t_game *game, t_player_sprite *sprite, int facing, int walking)
{
    int idx;

    if (facing)
        idx = walking ? TEX_FRONT_WALK : TEX_FRONT_IDLE;
    else
        idx = walking ? TEX_BACK_WALK : TEX_BACK_IDLE;
    sprite->tex = game->window->menus.lobby.playerImgs[idx].texture;
    sprite->src = game->window->menus.lobby.playerBounds[idx];
}

static int project_player(t_player_cam *cam, t_player_sprite *sprite, float x, float y, float floor_z)
{
    float dx;
    float dy;
    float tx;
    float inv_ty;

    dx = x - cam->pos.x;
    dy = y - cam->pos.y;
    tx = cam->inv_det * (cam->dir.y * dx - cam->dir.x * dy);
    sprite->depth = cam->inv_det * (-cam->plane.y * dx + cam->plane.x * dy);
    if (sprite->depth <= 0.1f || !sprite->tex || sprite->src.w <= 0 || sprite->src.h <= 0)
        return (0);
    inv_ty = 1.0f / sprite->depth;
    int y_bot = (int)(cam->half_sh - (floor_z - cam->z) * cam->focal * inv_ty + cam->pitch);
    int y_top = (int)(cam->half_sh - (floor_z + REMOTE_PLAYER_HEIGHT - cam->z) * cam->focal * inv_ty + cam->pitch);
    sprite->dest.h = y_bot - y_top;
    sprite->dest.w = sprite->dest.h * sprite->src.w / sprite->src.h;
    sprite->dest.x = (int)(cam->half_sw + cam->half_sw * tx * inv_ty) - sprite->dest.w / 2;
    sprite->dest.y = y_top;
    return (sprite->dest.w > 0 && sprite->dest.h > 0);
}

static int collect_player_sprites(t_game *game, t_player_cam *cam, t_player_sprite *sprites)
{
    static t_walk_state walk[4];
    t_udp_connections *con;
    int count;
    int walking;
    float x;
    float y;
    float feet_z;

    con = &game->clientConnection;
    count = 0;
    for (int i = 0; i < con->player_count && i < 4; i++)
    {
        if (i == con->selfIndex)
            continue;
        x = (float)con->players[i][0];
        y = (float)con->players[i][1];
        feet_z = (float)con->players[i][2]; // envoye par le joueur : suit le jetpack/saut
        walking = update_walk_state(&walk[i], x, y);
        pick_player_texture(game, &sprites[count], is_facing_camera(cam, x, y, con->player_angles[i]), walking);
        if (project_player(cam, &sprites[count], x, y, feet_z))
            count++;
    }
    return (count);
}

static void sort_sprites_by_depth(t_player_sprite *sprites, int count)
{
    t_player_sprite tmp;

    for (int i = 1; i < count; i++)
    {
        for (int j = i; j > 0 && sprites[j - 1].depth < sprites[j].depth; j--)
        {
            tmp = sprites[j];
            sprites[j] = sprites[j - 1];
            sprites[j - 1] = tmp;
        }
    }
}

void render_multiplayer_players(t_game *game)
{
    t_player_cam cam;
    t_player_sprite sprites[4];
    int count;

    if (!game->clientConnection.is_connected || game->clientConnection.player_count <= 0 || !game->map)
        return;
    cam = init_player_cam(game);
    if (fabsf(cam.plane.x * cam.dir.y - cam.dir.x * cam.plane.y) < 0.00001f)
        return;
    count = collect_player_sprites(game, &cam, sprites);
    sort_sprites_by_depth(sprites, count);
    for (int i = 0; i < count; i++)
        draw_player_sprite(game, &sprites[i]);
}
