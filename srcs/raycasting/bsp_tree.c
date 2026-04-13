/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:09:57 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/04/13 22:22:15 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycasting/Raycasting.h"
#include "Game.h"

// static t_list	*copy_wall(t_game *game, t_list *wall)
// {
// 	t_list	*new;
// 	t_wall	*new_wall, *this_wall;

// 	new_wall = calloc(1, sizeof(t_wall));
// 	if (!new_wall)
// 		exit_game(game, "COPY_WALL calloc");
// 	this_wall = (t_wall *)wall->content;
// 	new_wall->end.x = this_wall->end.x;
// 	new_wall->end.y = this_wall->end.y;
// 	new_wall->start.x = this_wall->start.x;
// 	new_wall->start.y = this_wall->start.y;
// 	new_wall->textureID = this_wall ->textureID;
// 	new_wall->transparency = this_wall->textureID;

// 	new = ft_lstnew(new_wall);
// 	if (!new)
// 		exit_game(game, "COPY_WALL new");
// 	return (new);
// }

// static void	split_wall(t_game *game, t_wall *splitter, t_wall *wall, t_list **front, t_list **back)
// {
// 	t_vect2	intersection;
// 	t_wall	*part1;
// 	t_wall	*part2;

// 	inter_point(wall->start, edge(wall->start, wall->end), splitter->start, edge(splitter->start, splitter->end), &intersection);
// 	part1 = calloc(1, sizeof(t_wall));
// 	part2 = calloc(1, sizeof(t_wall));
// 	if (!part1 || !part2)
// 		exit_game(game, "split_wall part1 || part2");
// 	part1->start.x = wall->start.x;
// 	part1->start.y = wall->start.y;
// 	part1->end.x = intersection.x;
// 	part1->end.y = intersection.y;

// 	part2->start.x = intersection.x;
// 	part2->start.y = intersection.y;
// 	part2->end.x = wall->end.x;
// 	part2->end.y = wall->end.y;

// 	part1->textureID = wall->textureID;
// 	part2->textureID = wall->textureID;
// 	part1->transparency = wall->transparency;
// 	part2->transparency = wall->transparency;

// 	if (wall_side(splitter, part1) == 1)
// 	{
// 		ft_lstadd_back(front, ft_lstnew(part1));
// 		ft_lstadd_back(back, ft_lstnew(part2));
// 	}
// 	else
// 	{
// 		ft_lstadd_back(front, ft_lstnew(part2));
// 		ft_lstadd_back(back, ft_lstnew(part1));
// 	}

// 	return ;
// }

// t_bsp	*bsp(t_game *game, t_list *walls)
// {
// 	t_list	*splitter;
// 	int		side;
// 	t_bsp	*node;
// 	t_list	*front = NULL, *back = NULL;

// 	if (ft_lstsize(walls) == 0)
// 		return (NULL);

// 	node = calloc(1, sizeof(t_bsp));
// 	if (!node)
// 		exit_game(game, "BSP_CALLOC");
// 	splitter = best_splitter(&walls);
// 	node->splitter = *(t_wall *)splitter->content;
// 	for (t_list *current = walls; current; current = current ->next)
// 	{
// 		if (current == splitter)
// 			continue ;
// 		side = wall_side(splitter->content, current->content);
// 		if (side == 1)
// 			ft_lstadd_back(&front, copy_wall(game, current));
// 		else if (side == 2)
// 			ft_lstadd_back(&back, copy_wall(game, current));
// 		else if (side == 3)
// 			split_wall(game, splitter->content, current->content, &front, &back);
// 	}

// 	node->front = bsp(game, front);
// 	node->back = bsp(game, back);

// 	ft_lstclear(&front, &free);
// 	ft_lstclear(&back, &free);

// 	return (node);
// }
