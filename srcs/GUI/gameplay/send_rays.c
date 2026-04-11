/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:38:29 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/11 11:43:15 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"

static void	draw_ray(t_game *game, t_RGB rgb, t_ray *ray)
{
	SDL_SetRenderDrawColor(game->window->renderPTR, rgb.r, rgb.g, rgb.b, rgb.alphaValue);
	// SDL_RenderDrawLineF(game->window->renderPTR, to_pixelX(game->ply->pos.x,game),
	//                  to_pixelY(game->ply->pos.y, game), to_pixelX(intersection.x, game),
	//                  to_pixelY(intersection.y, game));

	if (ray->intersection.x < 0 || ray->intersection.y < 0 || ray->height <= 0)
		return ;

	texture_wall(game, ray);

	return ;
}

void	send_rays(t_game *game, t_RGB rgb)
{
	t_ray	ray;
	int		elements = ft_lstsize(game->walls);
	float	t;

	if (elements <= 1)
		return ;

	ray.plane.x = game->ply->dir.y * -1 * 0.57;
	ray.plane.y = game->ply->dir.x * 0.57;
	for (int i = 0; i < game->screenSize[0]; i++)
	{

		ray.camera_x = 2 * i / (float)game->screenSize[0] - 1.0f;
		ray.ray_dir.x = game->ply->dir.x + ray.plane.x * ray.camera_x;
		ray.ray_dir.y = game->ply->dir.y + ray.plane.y * ray.camera_x;

		get_smaller_ray(game, game->bspTree, &ray, &t);
		ray.height = game->screenSize[1] / t;
		ray.screen_x = i;

		draw_ray(game, rgb, &ray);
	}

	return ;
}

