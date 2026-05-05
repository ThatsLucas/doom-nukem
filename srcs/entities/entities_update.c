/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:17:15 by edurance          #+#    #+#             */
/*   Updated: 2026/05/05 18:09:12 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities/Entities.h"
#include "Game.h"
#include "Raycasting/Raycasting.h"
#include "GUI/HUD.h"

float	angle_diff(float a, float b)
{
	float diff = fmod(b - a + M_PI, 2 * M_PI) - M_PI;

	return (diff);
}

/* Verifie si un mur bloque la ligne de mire entre l'entite et le joueur */
int	check_wall_blocking(t_game *game, float ex, float ey, int entity_sector, float px, float py)
{
	t_sector	*sector;
	t_wall		*wall;
	t_vect2		e_pos = {ex, ey};
	t_vect2		p_pos = {px, py};
	t_vect2		ray_dir = {px - ex, py - ey};
	t_vect2		hit_point;
	float		ray_length;
	float		distance_to_player;
	
	ray_length = sqrt(ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y);
	if (ray_length < 0.001f)
		return (1);
	
	/* mur du secteur de l'entite*/
	if (entity_sector >= 0 && entity_sector < game->map->num_sectors)
	{
		sector = &game->map->sectors[entity_sector];
		for (int i = 0; i < sector->num_walls; i++)
		{
			wall = &game->map->walls[sector->walls[i]];
			
			/* saute les murs transparents ou portals */
			if (wall->next_sector != -1)
				continue ;
			
			t_vect2 wall_v1 = game->map->vertices[wall->v1];
			t_vect2 wall_v2 = game->map->vertices[wall->v2];
			t_vect2 wall_edge = edge(wall_v1, wall_v2);
			
			/* intersection avec le rayon et le mur */
			float t = inter_point(e_pos, ray_dir, wall_v1, wall_edge, &hit_point);
			
			if (t > 0.001f && t < 1.0f)
			{
				distance_to_player = sqrt((p_pos.x - e_pos.x) * (p_pos.x - e_pos.x) + (p_pos.y - e_pos.y) * (p_pos.y - e_pos.y));
				float distance_to_hit = sqrt((hit_point.x - e_pos.x) * (hit_point.x - e_pos.x) + (hit_point.y - e_pos.y) * (hit_point.y - e_pos.y));
				
				/* si le mur est plus proche que le joueur */
				if (distance_to_hit < distance_to_player - 0.01f)
					return (0);
			}
		}
	}
	
	/* murs du secteur du joueur */
	sector = &game->map->sectors[game->ply->sector];
	for (int i = 0; i < sector->num_walls; i++)
	{
		wall = &game->map->walls[sector->walls[i]];
		
		if (wall->next_sector != -1)
			continue ;
		
		t_vect2 wall_v1 = game->map->vertices[wall->v1];
		t_vect2 wall_v2 = game->map->vertices[wall->v2];
		t_vect2 wall_edge = edge(wall_v1, wall_v2);
		
		float t = inter_point(e_pos, ray_dir, wall_v1, wall_edge, &hit_point);
		
		if (t > 0.001f && t < 1.0f)
		{
			distance_to_player = sqrt((p_pos.x - e_pos.x) * (p_pos.x - e_pos.x) + (p_pos.y - e_pos.y) * (p_pos.y - e_pos.y));
			float distance_to_hit = sqrt((hit_point.x - e_pos.x) * (hit_point.x - e_pos.x) + (hit_point.y - e_pos.y) * (hit_point.y - e_pos.y));
			
			if (distance_to_hit < distance_to_player - 0.01f)
				return (0);
		}
	}
	return (1);
}

int	check_vision(t_game *game, t_entity *e, t_ply *p)
{
	float	dx = p->pos.x - e->x;
	float	dy = p->pos.y - e->y;

	float	distance = sqrt(dx * dx + dy * dy);
	if (distance > e->vision_range)
		return (0);

	dx /= distance;
	dy /= distance;

	float	dot = dx * e->dir_x + dy * e->dir_y;
	float	limit = cos((e->vision_angle * M_PI / 180.0f) * 0.5f);

	if (dot < limit)
		return (0);

	if (!check_wall_blocking(game, e->x, e->y, e->sector, p->pos.x, p->pos.y))
		return (0);

	return (1);
}

void	move_to_ply(t_entity *e, t_ply *p, float dt)
{
	t_vect2	dir;

	dir.x = p->pos.x - e->x;
	dir.y = p->pos.y - e->y;

	float	dist = sqrt(dir.x * dir.x - dir.y * dir.y);

	if (dist < e->attack_range * 0.7f)
		return ;

	dir.x /= dist;
	dir.y /= dist;

	e->x += dir.x * e->speed * dt;
	e->y += dir.y * e->speed * dt;

	//e->dir_x = dir.x;
	//e->dir_y = dir.y;
}

void	attack_ply(t_ply *p, t_entity *e)
{
	long long current = get_time_ms();

	if (e->last_shot_time == 0)
		e->last_shot_time = current;

	if ((current - e->last_shot_time) / 10 < e->fire_rate)
		return ;

	e->last_shot_time = current;

	srand((int)get_time_ms());
	int	damage = rand() % (e->damage - 4 + 1) + 4;
	if (rand() % 10 == 0)
		damage = 0;
	p->hp -= damage;
}

void	actions_base_on_state(t_entity *e, t_game *game, float dt)
{
	if (e->status == E_STATUS_CHASE)
	{
		move_to_ply(e, game->ply, dt);
	}
	if (e->status == E_STATUS_ATTACK)
	{
		attack_ply(game->ply, e);
	}
}

void	update_enemy(t_entity *e, t_game *game, float dt)
{
	t_ply	*p = game->ply;
	float	dx = p->pos.x - e->x;
	float	dy = p->pos.y - e->y;
	float	distance = sqrt(dx * dx + dy * dy);

	int	see_player = check_vision(game, e, game->ply);

	switch (e->status)
	{
		case E_STATUS_IDLE:
			if (see_player)
			{
				printf("il nous voit\n");
				e->status = E_STATUS_CHASE;
			}
			break ;

		case E_STATUS_CHASE:
			if (distance < e->attack_range && see_player)
				e->status = E_STATUS_ATTACK;
			else if (!see_player)
				e->status = E_STATUS_IDLE;
			break ;

		case E_STATUS_ATTACK:
			if (distance > e->attack_range)
				e->status = E_STATUS_CHASE;
			break ;

		case E_STATUS_DEAD:
			break ;
	}

	actions_base_on_state(e, game, dt);
}

void	update_entities(t_game *game, t_entities *e)
{
	static long long	last_time = 0;
	long long			current = get_time_ms();

	if (last_time == 0)
		last_time = current;

	float dt = (current - last_time) / 1000.0f;
	if (dt > 0.1f)
		dt = 0.1f;

	last_time = current;

	for (int i = 0; i < e->count; i++)
	{
		if (e->list[i].type == ENTITY_ENEMY)
			update_enemy(&e->list[i], game, dt);
	}
}
