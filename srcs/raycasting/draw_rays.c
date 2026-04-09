/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:38:29 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/09 14:10:08 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting.h"
#include "Game.h"

static void	get_smaller_ray(t_vect2 *inter, t_game *game, t_ray *ray)
{
	float	min_t;
	t_list	*current;
	t_wall	*wall, *next_wall;

	min_t = INT_MAX;
	current = game->walls;

	while (current)
	{
		wall = (t_wall *)current->content;
		if (current->next)
			next_wall = (t_wall *)current->next->content;
		else
			next_wall = (t_wall *)game->walls->content;
		inter_point(game->ply->pos, ray->ray_dir, wall->start, edge(wall->start, next_wall->start), inter, &min_t);
		current = current->next;
	}

	return ;
}

void	draw_rays(t_game *game, t_RGB rgb)
{
	t_vect2	intersection;
	t_ray	ray;
	int		elements = ft_lstsize(game->walls);

	if (elements <= 1)
		return ;

	SDL_SetRenderDrawColor(game->window->renderPTR, rgb.r, rgb.g, rgb.b, rgb.alphaValue);
	ray.plane.x = game->ply->dir.y * -1 * 0.57;
	ray.plane.y = game->ply->dir.x * 0.57;
	for (int i = 0; i < game->screenSize[0]; i++)
	{

		ray.camera_x = 2 * i / (float)game->screenSize[0] - 1.0f;
		ray.ray_dir.x = game->ply->dir.x + ray.plane.x * ray.camera_x;
		ray.ray_dir.y = game->ply->dir.y + ray.plane.y * ray.camera_x;

		intersection.x = -1;
		intersection.y = -1;
		get_smaller_ray(&intersection, game, &ray);

		if (intersection.x != -1 && intersection.y != -1)
			SDL_RenderDrawLineF(game->window->renderPTR, to_pixelX(game->ply->pos.x,game), to_pixelY(game->ply->pos.y, game), to_pixelX(intersection.x, game), to_pixelY(intersection.y, game));
	}

	return ;
}
