/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:52:06 by edurance          #+#    #+#             */
/*   Updated: 2026/04/14 15:54:22 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"

void	update_projectiles(t_game *game)
{
	t_projectile	**cur = &game->projectiles;

	while (*cur)
	{
		t_projectile	*p = *cur;
		
		if (p->state == PROJ_FLYING)
		{
			float	dx = p->target_x - p->x;
			float	dy = p->target_y - p->y;
			float	dist = sqrtf(dx * dx + dy * dy); // calculer la distance (hypothenuse)
			float	ratio = dist / p->start_dist;
			float	speed = p->speed * (0.2f + 0.8f * ratio);
			p->size_x = (int)(p->fly_dest.w * (0.3f + 0.7f * ratio));
			p->size_y = (int)(p->fly_dest.h * (0.3f + 0.7f * ratio));

			if (dist <= p->speed)
			{
				p->x = p->target_x;
				p->y = p->target_y;
				p->state = PROJ_EXPLODING;
			}
			else
			{
				/* normaliser le vecteur pour avoir la position en fonction de la distance et de la vitesse */
				p->x += (dx / dist) * speed;
				p->y += (dy / dist) * speed;
			}
			cur = &p->next;
		}
		else if (p->state == PROJ_EXPLODING)
		{
			p->expl_tick++;
			if (p->expl_tick >= p->expl_rate)
			{
				p->expl_tick = 0;
				p->expl_frame++;
				if (p->expl_frame >= 3)
					p->state = PROJ_DEAD;
			}
			cur = &p->next;
		}
		else if (p->state == PROJ_DEAD)
		{
			p->expl_tick++;
			if (p->expl_tick > 2)
			{
				*cur = p->next;
				free(p);
				continue;
			}
			cur = &p->next;
		}
	}
}

void	render_projectiles(t_game *game)
{
	t_projectile	**cur = &game->projectiles;

	while (*cur)
	{
		t_projectile	*p = *cur;

		if (p->state == PROJ_FLYING)
		{
			SDL_Rect dest = {(int)p->x, (int)p->y, p->size_x, p->size_y};
			to_responsive(game->window, &dest);
			SDL_RenderCopy(game->window->renderPTR, p->fly_texture, NULL, &dest);
		}
		else if (p->state == PROJ_EXPLODING || p->state == PROJ_DEAD)
		{
			int frame = p->expl_frame;
			if (frame >= 3)
				frame = 2;

			SDL_Rect dest = {(int)p->x - 160, (int)p->y - 130, 300, 259};
			to_responsive(game->window, &dest);
			SDL_RenderCopy(game->window->renderPTR, p->expl_frames[frame], NULL, &dest);
		}
		cur = &(*cur)->next;
	}
}
