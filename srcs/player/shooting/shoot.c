/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:38:16 by edurance          #+#    #+#             */
/*   Updated: 2026/08/12 16:00:19 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

/* Calcule les dégâts infligés par l’arme à l’entité. */
static int	weapon_damage(t_game *game, t_weapon_type type, t_entity *e)
{
	int	damage = 0;

	switch (type)
	{
		case WEAP_PISTOL:
			damage = PISTOL_DAMAGE;
			break ;
		case WEAP_SHOTGUN:
			damage = SHOTGUN_DAMAGE;
			break ;
		case WEAP_ROCKET_LAUNCHER:
			damage = ROCKET_DAMAGE;
			break ;
		case WEAP_FISTS:
			float	dx = e->x - game->ply->pos.x;
			float	dy = e->y - game->ply->pos.y;
			float	dist = sqrt(dx * dx + dy * dy);
			if (dist > 2.0f)
				damage = 0;
			else
				damage = FISTS_DAMAGE;
			break ;
	}
	return (damage);
}

/* Fait tirer le joueur sur l’entité visée. */
void	player_shoot(t_game *game)
{
	int				idx = game->ply->current_weap_index;
	t_weapon_type	type = game->ply->inventory.weapons[idx].type;
	t_weapon_3D		*w = &game->hud_cache.weapons_3D[type];
	t_entity		*e = game->ply->crosshair_target;

	if (w->is_firing)
		return ;

	if (game->ply->crosshair_target && game->ply->crosshair_target->type == ENTITY_PNJ)
		return ;

	if (game->ply->inventory.weapons[idx].ammo <= 0 && game->ply->inventory.weapons[idx].ammo != -1)
		return ;

	// client multi : c'est l'hote qui applique les degats et renvoie l'etat
	if (e && game->settings.multiplayer_enabled && !game->settings.is_host)
		report_entity_hit(game, e - game->entities.list,
			weapon_damage(game, game->ply->inventory.weapons[idx].type, e));
	else if (e)
	{
		e->hp -= weapon_damage(game, game->ply->inventory.weapons[idx].type, e);
		if (e->hp <= 0)
		{
			e->status = E_STATUS_DEAD;
			e->hitbox = 0;
		}
	}
	if (game->ply->inventory.weapons[idx].type != WEAP_FISTS)
	{
		game->ply->inventory.weapons[idx].ammo -= 1;
		play_sound(game->sounds.shot);
	}

	w->current_frame = 0;
	w->is_firing = 1;
}
