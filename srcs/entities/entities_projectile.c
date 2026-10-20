/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_projectile.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 08:34:03 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/05 08:45:25 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	1. entité projectile créée au moment du clic
	2. va dans la direction du joueur
	3. s'arrête si croise un mur ou une entité en collision
	4. Garde fou: distance max & collision radius min
	5. animation à la fin d'explosion et application des dégats

	modif le sprintf
	!!! murs transparents
*/


