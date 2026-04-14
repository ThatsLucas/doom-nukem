#include "Raycasting/Raycasting.h"
#include "Game.h"

/* dessine le decalage entre le portail et le plafond + le portail et le sol */
static void	draw_offset(t_ray *ray, t_game *game, int ny_top, int ny_bot, int x)
{
	int sW			= game->screenSize[0], sH = game->screenSize[1];
	int step_top	= SDL_clamp(ray->y_top, 0, sH - 1);
	int step_ny_top	= SDL_clamp(ny_top, 0, sH - 1);
	int step_ny_bot	= SDL_clamp(ny_bot, 0, sH - 1);
	int step_bot	= SDL_clamp(ray->y_bot, 0, sH - 1);
	t_wall	*w;
	float	u_world, wall_len, v;
	int		tex_x, tex_y;
	t_RGB	c;

	w			= &game->map->walls[ray->wall_idx];
	wall_len	= dist_vect(game->map->vertices[w->v1], game->map->vertices[w->v2]);
	u_world		= ray->u * wall_len;

	if (w->tex_upper >= 0)
	{
		tex_x		= (int)(u_world * game->map->surface[w->tex_upper]->w) % game->map->surface[w->tex_upper]->w;
		for (int y = step_top; y < step_ny_top; y++)
		{
			v		= (float)(y - ny_top) / (float)(ny_bot - ny_top);
			tex_y	= (int)(v * game->map->surface[w->tex_upper]->h) % game->map->surface[w->tex_upper]->h;
			c		= game->map->text_colors[w->tex_upper][tex_y * game->map->surface[w->tex_upper]->w + tex_x];
			game->frame_buffer[y * sW + x] = (c.r << 16) | (c.g << 8) | c.b;
		}
	}

	if (w->tex_lower >= 0)
	{
		tex_x		= (int)(u_world * game->map->surface[w->tex_lower]->w) % game->map->surface[w->tex_lower]->w;
		for (int y = step_ny_bot; y < step_bot; y++)
		{
			v		= (float)(y - ny_top) / (float)(ny_bot - ny_top);
			tex_y	= (int)(v * game->map->surface[w->tex_lower]->h) % game->map->surface[w->tex_lower]->h;
			c		= game->map->text_colors[w->tex_lower][tex_y * game->map->surface[w->tex_lower]->w + tex_x];
			game->frame_buffer[y * sW + x] = (c.r << 16) | (c.g << 8) | c.b;
		}
	}

	ny_top		= SDL_clamp(ny_top, ray->y_top, ray->y_bot);
	ny_bot		= SDL_clamp(ny_bot, ray->y_top, ray->y_bot);
	ray->y_top	= ny_top;
	ray->y_bot	= ny_bot;

	return ;
}

/* dessine la colonne x du rayon ray, de facon recursive */
void	draw_col(t_game *game, t_ray *ray, int x, int sector_id, int skip_wall)
{
	t_sector	*sector;
	float		nz_floor, nz_ceil;
	int			ny_top, ny_bot;
	int			sH = game->screenSize[1];

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

	if (game->map->walls[ray->wall_idx].next_sector == -1)
	{
		draw_ceil(game, ray, x, sector);
		draw_wall(game, ray, x);
		draw_floor(game, ray, x, sector);
		return ;
	}

	draw_ceil(game, ray, x, sector);
	draw_floor(game, ray, x, sector);

	t_sector *next_sec = &game->map->sectors[game->map->walls[ray->wall_idx].next_sector];
	nz_floor	= get_plane_z(next_sec->floor_plane, ray->hit.x, ray->hit.y);
	nz_ceil		= get_plane_z(next_sec->ceil_plane,  ray->hit.x, ray->hit.y);
	ny_bot		= sH / 2 - ((nz_floor - game->ply->z) / ray->perp_dist) * ray->focal + game->ply->pitch;
	ny_top		= sH / 2 - ((nz_ceil  - game->ply->z) / ray->perp_dist) * ray->focal + game->ply->pitch;

	draw_offset(ray, game, ny_top, ny_bot, x);
	if (ray->y_top > ray->y_bot)
		return ;

	int	next_id	= game->map->walls[ray->wall_idx].next_sector;
	int	mirror	= find_mirror_wall(game->map, ray->wall_idx, next_id);
	draw_col(game, ray, x, next_id, mirror);
	return ;
}
