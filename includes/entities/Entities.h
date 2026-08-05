/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:14:41 by edurance          #+#    #+#             */
/*   Updated: 2026/07/25 13:49:52 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_H
# define ENTITIES_H

# include <stddef.h>
# include <stdlib.h>

#define MAX_ENTITY_DIST_RENDER_SQ 625.0f

typedef struct	s_game t_game;
typedef struct	s_vect2 t_vect2;

typedef enum	e_entity_type
{
	ENTITY_PNJ,
	ENTITY_ENEMY,
	ENTITY_PROP,
	ENTITY_NONE
}				t_entity_type;

typedef enum	e_entity_status
{
	E_STATUS_IDLE,
	E_STATUS_CHASE,
	E_STATUS_ATTACK,
	E_STATUS_DEAD
}				t_entity_status;

typedef struct	s_entity
{
	double			x;
	double			y;
	double			z;
	float			dir_x;
	float			dir_y;

	int				sector;
	t_entity_type	type;
	void			**textures;
	void			*texture;
	void			*texture_shoot;
	int				num_frames;

	int	hp;
	float	speed;
	float	vision_range;
	float	vision_angle;
	int		attack_range;
	int		fire_rate;
	int		damage;

	t_entity_status	status;

	double	hitbox;

	int			can_shoot;
	long long	last_shot_time;
	char		*notif;

}				t_entity;

typedef struct	s_entities
{
	t_entity	*list;
	int			count;
	int			capacity;
}				t_entities;

void	free_entities(t_entities *e);
void	init_entities(t_entities *e);
void	add_entity(t_game *game, t_entities *e, t_entity entity);
int		entities_collision(t_game *game, float next_x, float next_y);
void	update_entities(t_game *game, t_entities *e);

int		default_enemy(t_game *game, t_vect2 pos, char *idle_tex, char *shoot_tex, int w, int h);
void	default_pnj(t_game *game, t_vect2 pos, char *paths[], int size, int w, int h, float dir_x, float dir_y, char *notif);
int		spawn_props(t_game *game, t_vect2 pos, char *png_path);

#endif
