/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Inventory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:17:03 by edurance          #+#    #+#             */
/*   Updated: 2026/06/10 16:31:14 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX_WEAPONS 4
#define MAX_TOOLS 3

#include "Items.h"
#include <math.h>
#include <stdio.h>

typedef struct s_inventory
{
	t_weapon weapons[MAX_WEAPONS];
	int weap_count;

	t_tool tools[MAX_TOOLS];
	int tool_count;

	t_tool *jetpack;
} t_inventory;

#endif
