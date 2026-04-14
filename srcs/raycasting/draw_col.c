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

	for (int i = step_top; i < step_ny_top; i++)
		game->frame_buffer[i * sW + x] = (47 << 16) | (79 << 8) | 79;

	for (int i = step_ny_bot; i < step_bot; i++)
		game->frame_buffer[i * sW + x] = (47 << 16) | (79 << 8) | 79;

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
		draw_ceil(game, ray, x);
		draw_wall(game, ray, x);
		draw_floor(game, ray, x);
		return ;
	}

	sector = &game->map->sectors[game->map->walls[ray->wall_idx].next_sector];
	draw_ceil(game, ray, x);
	draw_floor(game, ray, x);

	nz_floor	= get_plane_z(sector->floor_plane, ray->hit.x, ray->hit.y);
	nz_ceil		= get_plane_z(sector->ceil_plane,  ray->hit.x, ray->hit.y);
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
