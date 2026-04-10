/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:38:29 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/10 11:47:51 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting.h"
#include "Game.h"

static void	draw_ray(t_game *game, t_RGB rgb, t_vect2 intersection, t_ray *ray)
{
	SDL_SetRenderDrawColor(game->window->renderPTR, rgb.r, rgb.g, rgb.b, rgb.alphaValue);
	// SDL_RenderDrawLineF(game->window->renderPTR, to_pixelX(game->ply->pos.x,game),
	// 					to_pixelY(game->ply->pos.y, game), to_pixelX(intersection.x, game),
	// 					to_pixelY(intersection.y, game));

	ray->draw_start	= (game->screenSize[1] / 2) - (ray->height / 2);
	ray->draw_end	= (game->screenSize[1] / 2) + (ray->height / 2);
	SDL_RenderDrawLineF(game->window->renderPTR, ray->screen_x, ray->draw_start,
						ray->screen_x, ray->draw_end);
	(void)intersection;

	return ;
}

void	send_rays(t_game *game, t_RGB rgb)
{
	t_vect2	intersection;
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

		intersection = get_smaller_ray(game, game->bspTree, &ray, &t);
		ray.height = game->screenSize[1] / t;
		ray.screen_x = i;

		if (intersection.x != -1 && intersection.y != -1)
			draw_ray(game, rgb, intersection, &ray);
	}

	return ;
}

