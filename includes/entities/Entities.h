/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:14:41 by edurance          #+#    #+#             */
/*   Updated: 2026/10/28 22:46:05 by aabouyaz         ###   ########.fr       */
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

# define PROJ_SPEED 8.0f
# define PROJ_ENTITY_RADIUS 0.5f
# define PROJ_HIT_HEIGHT 2.0f
# define PROJ_MAX_DIST 50.0f
# define PROJ_SPAWN_DROP 0.2f
# define PROJ_HIDE_DIST 0.5f
# define PROJ_SPLASH_RADIUS 2.5f

typedef struct s_game	t_game;
typedef struct s_vect2	t_vect2;
typedef struct s_tex	t_tex;
typedef struct s_ply	t_ply;
typedef struct s_map	t_map;

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

/* joueur que les ennemis peuvent viser (local ou distant en multi) */
typedef struct s_target
{
	float				x;
	float				y;
	float				z;			// hauteur des yeux
	int					sector;
	int					net_index;	// -1 : joueur local, sinon index du joueur distant
}						t_target;

typedef struct s_cached_sprite
{
	char				*path;
	int					w;
	int					h;
	t_tex				*tex;
}						t_cached_sprite;

/* Textures déjà décodées, partagées entre les entités. */
typedef struct s_sprite_cache
{
	t_cached_sprite		*list;
	int					count;
	int					capacity;
}						t_sprite_cache;

typedef struct s_entities
{
	t_entity			*list;
	int					count;
	int					capacity;
	t_sprite_cache		sprites;
}						t_entities;

typedef enum e_proj_state
{
	PROJ_FLYING,
	PROJ_EXPLODING
}						t_proj_state;

typedef struct s_projectile
{
	t_proj_state		state;
	float				x;
	float				y;
	float				z;
	float				dx;
	float				dy;
	float				dz;
	int					sector;
	float				traveled;
	float				expl_timer;
	int					expl_frame;
	struct s_projectile	*next;
}						t_projectile;

typedef struct s_proj_assets
{
	t_tex				*fly;
	t_tex				*expl[3];
	int					loaded;
}						t_proj_assets;

/* Segment suivi de secteur en secteur : depart (x, y, z) + deplacement (rx, ry, rz). */
typedef struct s_trace
{
	float				x;
	float				y;
	float				z;
	float				rx;
	float				ry;
	float				rz;
	int					sector;
	int					glass_blocks;
	float				t;
}						t_trace;

void					free_entities(t_entities *e);
void					init_entities(t_entities *e);
t_tex					*get_cached_sprite(t_game *game, char *path, int w, int h);
void					free_sprite_cache(t_sprite_cache *cache);
void					add_entity(t_game *game, t_entities *e, t_entity entity);
int						entities_collision(t_game *game, float next_x, float next_y);
void					update_entities(t_game *game, t_entities *e);
int						get_directional_frame(t_entity *e, float px, float py);

/* entities_ai.c */
float					angle_diff(float a, float b);
int						check_vision(t_game *game, t_entity *e, t_target *t);
void					move_to_ply(t_game *game, t_entity *e, t_target *t, float dt);
int						entity_attack_damage(t_entity *e);
void					attack_ply(t_ply *p, t_entity *e);
int						check_wall_blocking(t_game *game, t_entity *e, t_target *t);
int						trace_segment(t_map *map, t_trace *tr);
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

/* entities_projectile.c */
void					spawn_rocket(t_game *game);
void					update_projectiles(t_game *game);

/* entities_projectile_render.c */
void					load_proj_assets(t_game *game);
void					render_projectiles(t_game *game);
void					clear_projectiles(t_game *game);
void					free_projectiles(t_game *game);

#endif
