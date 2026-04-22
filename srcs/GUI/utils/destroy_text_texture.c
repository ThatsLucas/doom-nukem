/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_text_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 18:02:04 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/22 18:04:12 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI.h"

void destroy_text_texture(t_font *text)
{
    if (text && text->texture)
    {
        SDL_DestroyTexture(text->texture);
        text->texture = NULL;
    }
}