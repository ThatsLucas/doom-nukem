/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root- <root-@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:51:11 by root-             #+#    #+#             */
/*   Updated: 2026/04/09 15:45:08 by root-            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#ifndef FILTER_H
#define FILTER_H

/*filter types*/
#define FILTER_NONE 0    // pas de filtre
#define FILTER_SUB 0     // val - byte de gauche
#define FILTER_UP 0      // val - byte du dessus
#define FILTER_AVERAGE 0 // val - moyenne gauche et dessus
#define FILTER_PAETH 0   // val - fonction parth pour trouver le pixel

typedef struct s_filterType {
  __uint8_t top;
  __uint8_t left;
  __uint8_t topleft;
} t_filterType;

#endif