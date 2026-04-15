/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_col.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:17:59 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/15 13:48:09 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"

void	blend_pixels(t_game *game, t_wall *w, t_ray *ray, int x, t_sector *sector)
{
	int		draw_top = (ray->y_wall_top > ray->y_top) ? ray->y_wall_top : ray->y_top;
	int		draw_bot = (ray->y_wall_bot < ray->y_bot) ? ray->y_wall_bot : ray->y_bot;
	float	u_world, wall_len, v;
	int		tex_x, tex_y;

	wall_len	= dist_vect(game->map->vertices[w->v1], game->map->vertices[w->v2]);
	u_world		= ray->u * wall_len;
	tex_x		= (int)(u_world * game->map->surface[w->tex_mid]->w) % game->map->surface[w->tex_mid]->w;
	t_RGB	behind;
	t_RGB	color;
	for (int y = draw_top; y < draw_bot; ++y)
	{
		v		= (float)(y - ray->y_wall_top) / (float)(ray->y_wall_bot - ray->y_wall_top);
		tex_y	= (int)(v * game->map->surface[w->tex_mid]->h) % game->map->surface[w->tex_mid]->h;
		behind.r	= (game->frame_buffer[game->screenSize[0] * y + x] >> 16) & 0xFF; // & 0xFF pour garger que les derniers 8 bits
		behind.g	= (game->frame_buffer[game->screenSize[0] * y + x] >> 8) & 0xFF;
		behind.b	= (game->frame_buffer[game->screenSize[0] * y + x]) & 0xFF;
		color		= game->map->text_colors[w->tex_mid][tex_y * game->map->surface[w->tex_mid]->w + tex_x];

		color.r		= color.r * w->alpha + behind.r * (1 - w->alpha);
		color.g		= color.g * w->alpha + behind.g * (1 - w->alpha);
		color.b		= color.b * w->alpha + behind.b * (1 - w->alpha);

		game->frame_buffer[game->screenSize[0] * y + x] = write_color(color.r, color.g, color.b, sector->light_level);
	}
}

/* Affiche les mur/toit/sol en fonction du cas */
static void	simple_draw(t_game *game, t_ray *ray, int x, t_sector *sector, int cas)
{
	switch (cas)
	{
		case 1:
			draw_ceil(game, ray, x, sector);
			ray->y_wall_bot = ray->y_wall_top;
			draw_floor(game, ray, x, sector);
			break;

		case 2:
			draw_ceil(game, ray, x, sector);
			draw_wall(game, ray, x, sector);
			draw_floor(game, ray, x, sector);
			break;

		default:
			draw_ceil(game, ray, x, sector);
			draw_floor(game, ray, x, sector);
			break;
	}

	return ;
}

static void get_next_sect(int *next_id, int *mirror, t_game *game, t_ray *ray, int x, t_sector *sector)
{
	float		nz_floor, nz_ceil;
	int			ny_top, ny_bot;
	int			sH = game->screenSize[1];

	t_sector *next_sec	= &game->map->sectors[game->map->walls[ray->wall_idx].next_sector];
	nz_floor			= get_plane_z(next_sec->floor_plane, ray->hit.x, ray->hit.y);
	nz_ceil				= get_plane_z(next_sec->ceil_plane,  ray->hit.x, ray->hit.y);
	ny_bot				= sH / 2 - ((nz_floor - game->ply->z) / ray->perp_dist) * ray->focal + game->ply->pitch;
	ny_top				= sH / 2 - ((nz_ceil  - game->ply->z) / ray->perp_dist) * ray->focal + game->ply->pitch;

	ny_top				= SDL_clamp(ny_top, ray->y_wall_top, ray->y_wall_bot);
	ny_bot				= SDL_clamp(ny_bot, ray->y_wall_top, ray->y_wall_bot);
	draw_offsets(ray, game, ny_top, ny_bot, x, sector);

	*next_id			= game->map->walls[ray->wall_idx].next_sector;
	*mirror				= find_mirror_wall(game->map, ray->wall_idx, *next_id);

	return ;
}

/* dessine la colonne x du rayon ray, de facon recursive */
void	draw_col(t_game *game, t_ray *ray, int x, int sector_id, int skip_wall)
{
	t_sector	*sector;
	int			sH = game->screenSize[1];
	t_ray		temp;
	int			is_transparent = 0;
	int			next_id, mirror;

	ray->t			= FLT_MAX;
	sector			= &game->map->sectors[sector_id];
	find_smaller_ray(game, sector, ray, skip_wall);
	if (ray->t >= FLT_MAX - 1)
		return ;
	ray->perp_dist	= ray->t * (ray->dir.x * game->ply->dir.x + ray->dir.y * game->ply->dir.y);
	ray->z_floor	= get_plane_z(sector->floor_plane, ray->hit.x, ray->hit.y);
	ray->z_ceil		= get_plane_z(sector->ceil_plane,  ray->hit.x, ray->hit.y);
	ray->y_wall_bot	= sH / 2 - ((ray->z_floor - game->ply->z) / ray->perp_dist) * ray->focal + game->ply->pitch;
	ray->y_wall_top	= sH / 2 - ((ray->z_ceil - game->ply->z) / ray->perp_dist) * ray->focal + game->ply->pitch;

	if (ray->y_wall_top >= ray->y_wall_bot)					/* Si le haut du mur passe en bas du bas du mur */
		return simple_draw(game, ray, x, sector, 1);
	if (game->map->walls[ray->wall_idx].next_sector == -1)	/* Si c'est pas un portail	 */
		return simple_draw(game, ray, x, sector, 2);
	if (game->map->walls[ray->wall_idx].alpha < 1.0f && game->map->walls[ray->wall_idx].tex_mid >= 0)	/* gerer la transparance */
	{
		if (game->map->walls[ray->wall_idx].alpha > 0.0f)
			is_transparent = 1;
		temp = *ray;
	}

	simple_draw(game, ray, x, sector, -1);
	if (ray->y_top > ray->y_bot)
		return ;
	get_next_sect(&next_id, &mirror, game, ray, x, sector);
	draw_col(game, ray, x, next_id, mirror);

	if (is_transparent)
		blend_pixels(game, &game->map->walls[temp.wall_idx], &temp, x, sector);

	return ;
}
