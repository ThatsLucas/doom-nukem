/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_menu_texts.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:07:30 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:07:30 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.h"
#include "Window.h"
#include "GUI/GUI.h"

/*
	Labels of a classic menu button:
		texts[0] -> red text (normal)
		texts[1] -> white outlined text (hover)
*/
void	create_menu_button_texts(t_font *texts, SDL_Renderer *renderer, char *str)
{
	texts[0].color = (SDL_Color){221, 21, 0, 255};
	texts[0].size = 60;
	texts[0].textHOffset = -10;
	create_text(&texts[0], renderer, str, DNFONT);

	texts[1].color = (SDL_Color){255, 255, 255, 255};
	texts[1].size = 60;
	texts[1].textHOffset = -10;
	create_text(&texts[1], renderer, str, DNFONTOUTLINED);
}

/* White DNFONT text of the given size */
void	create_white_text(t_font *font, SDL_Renderer *renderer, char *str, int size)
{
	font->color = (SDL_Color){255, 255, 255, 255};
	font->size = size;
	create_text(font, renderer, str, DNFONT);
}
