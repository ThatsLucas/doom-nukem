/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:51:11 by root-             #+#    #+#             */
/*   Updated: 2026/04/10 20:00:24 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#ifndef FILTER_H
#define FILTER_H

/*filter types*/
#define FILTER_NONE    0
#define FILTER_SUB     1
#define FILTER_UP      2
#define FILTER_AVERAGE 3
#define FILTER_PAETH   4

typedef struct s_filterType {
  __uint8_t top;
  __uint8_t left;
  __uint8_t topleft;
} t_filterType;

#endif