/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:14:41 by edurance          #+#    #+#             */
/*   Updated: 2026/05/04 10:56:23 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_H
# define ENTITIES_H

# include <stddef.h>
# include <stdlib.h>

#define MAX_ENTITY_DIST_RENDER_SQ 625.0f

typedef struct	s_game t_game;

typedef enum	e_entity_type
{
	ENTITY_PNJ,
	ENTITY_ENEMY,
}				t_entity_type;

typedef struct	s_entity
{
	double			x;
	double			y;
	double			z;
	int				sector;
	t_entity_type	type;
	void*			texture;

	int	hp;
	int	max_hp;
	int	is_alive;

	double	hitbox;

	int			can_shoot;
	long long	last_shot_time;

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

#endif
