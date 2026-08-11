/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:14:41 by edurance          #+#    #+#             */
/*   Updated: 2026/08/11 13:44:15 by edurance         ###   ########.fr       */
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
	ENTITY_BOSS
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
	void			*texture_dead;
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
	float		sprite_w;
	float		sprite_h;	long long	last_shot_time;
	char		*notif;

	float	attack_timer;
	float	special_timer;
	float	dash_timer;
	float	state_timer;

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

void	create_enemy1(t_game *game, t_vect2 pos);
void	create_enemy2(t_game *game, t_vect2 pos);
void	create_enemy3(t_game *game, t_vect2 pos);
void	create_pnj1(t_game *game, t_vect2 pos, t_vect2 dir);
void	create_pnj2(t_game *game, t_vect2 pos, t_vect2 dir);
void	create_pnj3(t_game *game, t_vect2 pos, t_vect2 dir);
void	create_boss1(t_game *game, t_vect2 pos);
void	create_boss2(t_game *game, t_vect2 pos);
void	create_boss3(t_game *game, t_vect2 pos);

#endif
