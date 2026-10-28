/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:14:41 by edurance          #+#    #+#             */
/*   Updated: 2026/10/20 13:48:57 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_H
# define ENTITIES_H

# include <stddef.h>
# include <stdlib.h>

# define MAX_ENTITY_DIST_RENDER_SQ 625.0f
# define ENTITY_EYE_HEIGHT 1.5f
# define ENTITY_WALL_MARGIN 0.3f
# define MAX_SIGHT_STEPS 64

typedef struct s_game	t_game;
typedef struct s_vect2	t_vect2;
typedef struct s_tex	t_tex;
typedef struct s_ply	t_ply;

typedef enum e_entity_type
{
	ENTITY_PNJ,
	ENTITY_ENEMY,
	ENTITY_BOSS,
	ENTITY_PROP,
	ENTITY_PROJ,
	ENTITY_NONE
}						t_entity_type;

typedef enum e_entity_status
{
	E_STATUS_IDLE,
	E_STATUS_CHASE,
	E_STATUS_ATTACK,
	E_STATUS_DEAD
}						t_entity_status;

typedef struct s_entity
{
	double				x;
	double				y;
	double				z;
	float				dir_x;
	float				dir_y;

	int					sector;
	t_entity_type		type;
	t_tex				**textures;
	t_tex				*texture;
	t_tex				*texture_shoot;
	t_tex				*texture_dead;
	int					num_frames;

	int					hp;
	float				speed;
	float				vision_range;
	float				vision_angle;
	int					attack_range;
	int					fire_rate;
	int					damage;

	t_entity_status		status;

	double				hitbox;
	float				sprite_w;
	float				sprite_h;
	long long			last_shot_time;
	char				*notif;

	float				attack_timer;
	float				special_timer;
	float				dash_timer;
	float				state_timer;

}						t_entity;

typedef struct s_entities
{
	t_entity			*list;
	int					count;
	int					capacity;
}						t_entities;

void					free_entities(t_entities *e);
void					init_entities(t_entities *e);
void					add_entity(t_game *game, t_entities *e, t_entity entity);
int						entities_collision(t_game *game, float next_x, float next_y);
void					update_entities(t_game *game, t_entities *e);
int						get_directional_frame(t_entity *e, float px, float py);

/* entities_ai.c */
float					angle_diff(float a, float b);
int						check_vision(t_game *game, t_entity *e, t_ply *p);
void					move_to_ply(t_game *game, t_entity *e, t_ply *p, float dt);
void					attack_ply(t_ply *p, t_entity *e);
int						check_wall_blocking(t_game *game, t_entity *e, t_ply *p);
int						entity_can_move(t_game *game, t_entity *e, float nx, float ny);

/* entities_create_utils.c */
void					init_pnj_base(t_game *game, t_entity *e, t_vect2 pos, t_vect2 dir);
void					load_entity_frames(t_game *game, t_entity *e, char *prefix, int w, int h);
void					init_fighter_base(t_game *game, t_entity *e, t_entity_type type, t_vect2 pos);
void					load_fighter_textures(t_game *game, t_entity *e, char *dir, int size[4]);

void					create_enemy1(t_game *game, t_vect2 pos);
void					create_enemy2(t_game *game, t_vect2 pos);
void					create_enemy3(t_game *game, t_vect2 pos);
void					create_pnj1(t_game *game, t_vect2 pos, t_vect2 dir);
void					create_pnj2(t_game *game, t_vect2 pos, t_vect2 dir);
void					create_pnj3(t_game *game, t_vect2 pos, t_vect2 dir);
void					create_boss1(t_game *game, t_vect2 pos);
void					create_boss2(t_game *game, t_vect2 pos);
void					create_boss3(t_game *game, t_vect2 pos);

#endif
