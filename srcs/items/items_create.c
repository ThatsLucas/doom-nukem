/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 12:58:20 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 12:58:20 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 00:00:00 by edurance          #+#    #+#             */
/*   Updated: 2026/09/22 00:00:00 by edurance         ###   ########.fr       */
/*                                                                            */

#include "Game.h"
#include "inventory/Items.h"

#define ITEM_PICKUP_RANGE 1.2f

/* Charge la texture de l’objet. */
static void	load_item_texture(t_game *game, t_ground_item *item, char *png_path)
{
	t_png	png;

	png.w = 0;
	png.h = 0;
	png.path = ft_strdup(png_path);
	if (!png.path)
		exit_game(game, "Failed to strdup item texture path");
	if (!process_png(&png))
		exit_game(game, "Failed to load item texture");
	item->texture = create_image(&png, game->window->renderPTR);
	if (!item->texture)
		exit_game(game, "Failed to create item image");
	item->texture_path = png_path;
	item->w = (int)png.w;
	item->h = (int)png.h;
	item->aspect_ratio = (float)item->w / (float)item->h;
}

/* Crée un objet au sol avec sa texture. */
void	create_ground_item(t_game *game, t_vect2 pos, char *png_path,
			float world_height, t_ground_item item)
{
	int		sector;

	sector = find_sector(game->map, pos);
	if (sector == -1)
		exit_game(game, "Failed to find sector for item");
	item.pos_x = pos.x;
	item.pos_y = pos.y;
	item.pos_z = get_plane_z(game->map->sectors[sector].floor_plane,
			pos.x, pos.y);
	item.pickup_range = ITEM_PICKUP_RANGE;
	item.picked_up = 0;
	item.world_height = world_height;
	load_item_texture(game, &item, png_path);
	add_item(game, item);
}
