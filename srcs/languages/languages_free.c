/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   languages_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:20:14 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:20:14 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "languages/language.h"
#include "Game.h"

void free_languages(t_game *game)
{
    char **tab[LANGUAGE_FIELDS];

    if (!game->languages)
        return;
    get_language_fields(game->languages, tab);
    for (int i = 0; i < LANGUAGE_FIELDS; i++)
    {
        free(*tab[i]);
        *tab[i] = NULL;
    }

    free(game->languages);
    game->languages = NULL;
}
