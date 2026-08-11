/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 11:43:32 by edurance          #+#    #+#             */
/*   Updated: 2026/08/11 11:54:20 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

static t_decal	*get_crosshair_decal(t_game *game)
{
	t_ray	*ray;
	t_decal	*d;
	float	u_world;
	float	z_center;
	float	z_plane;

	ray = &game->rays[game->screenSize[0] / 2];
	if (ray->wall_idx < 0 || ray->perp_dist <= 0.0f || ray->perp_dist >= FLT_MAX)
		return (NULL);
	u_world  = ray->u * game->map->walls[ray->wall_idx].length;
	z_center = game->ply->z + game->ply->pitch * ray->perp_dist * ray->inv_focal;
	for (int i = 0; i < game->map->num_decals; ++i)
	{
		d = &game->map->decals[i];
		if (dist_vect(game->ply->pos, d->pos) > 2.0f)
			continue ;
		if (d->sector_id >= 0)
			z_plane = get_plane_z(game->map->sectors[d->sector_id].floor_plane, d->pos.x, d->pos.y);
		else
			z_plane = 0.0f;
		if (d->wall_idx != ray->wall_idx)
			continue ;
		if (u_world < d->u_offset || u_world > d->u_offset + d->width)
			continue ;
		if (z_center < d->z_bottom + z_plane || z_center > d->z_bottom + d->height + z_plane)
			continue ;
		return (d);
	}
	return (NULL);
}

void	interactions(t_game *game)
{
	t_ply	*ply = game->ply;
	t_decal	*d;

	if (ply->crosshair_target && ply->crosshair_target->type == ENTITY_PNJ && ply->crosshair_target->notif)
		create_notif(&game->window->menus.notif.notif_buf, ply->crosshair_target->notif, 5, 40);
	else
	{
		d = get_crosshair_decal(game);
		if (!d || d->elev_sector == -1)
			return ;
		printf("decal = %d\n", d->need_key);

		if (d->need_key)
		{
			printf("need key\n");
			for (int i = 0; i < ply->inventory.tool_count; ++i)
			{
				if (ply->inventory.tools[i].type == TOOL_KEY)
				{
					printf("found key\n");
					toggle_elevator(&game->map->sectors[d->elev_sector]);
				}
			}
			return ;
		}

		toggle_elevator(&game->map->sectors[d->elev_sector]);
	}

	return ;
}
