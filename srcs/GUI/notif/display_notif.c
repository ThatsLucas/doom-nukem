/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_notif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouyaz <aabouyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:16:08 by aabouyaz          #+#    #+#             */
/*   Updated: 2026/10/20 13:16:08 by aabouyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"

/* Dessine le texte de la notification. */
static void draw_notif_text(t_WIN *win, t_notif *notif, int notifX, int notifY, int notifW, int notifH)
{
    if (!notif->font.texture)
    {
        ft_dprintf(STDERR_FILENO, "Invalid Texture inside Notif\n");
        return;
    }
    int x = notifX + (notifW - notif->w) /2;
    int y = notifY + (notifH - notif->h) /2;
    int w = notif->w;
    int h = notif->h;
    SDL_Rect notifText = {x, y, w, h};
    to_responsive(win, &notifText);
    if (SDL_RenderCopy(win->renderPTR, notif->font.texture, NULL, &notifText)  < 0)
        ft_dprintf(STDERR_FILENO, "ERROR: %s\n", SDL_GetError());
}

/* Crée une notification et prépare son affichage. */
static void spawn_notif(t_WIN *win, t_notif_buf **notif_buf)
{
    t_notif *notif = (*notif_buf)->notif;
    SDL_Rect new_pos = { 1920 / 2 - (win->menus.notif.Popup.w / 3 / 2) , -win->menus.notif.Popup.h / 3 + 2, win->menus.notif.Popup.w / 3, win->menus.notif.Popup.h / 3};

    notif->coords = new_pos;
    notif->state = NOTIF_SPAWNING;

    SDL_Color color = {255, 255, 255, 255};
    notif->font.color = color;
    create_text_multiple_lines(&notif->font, win->renderPTR, notif->text, DNFONT, win->menus.notif.Popup.w / 3 - 120);
    if (!notif->font.texture)
    {
        destroy_notif_node(notif_buf);
        return;
    }
    notif->w = notif->font.w;
    notif->h = notif->font.h;
    notif->duration = SDL_GetTicks() + notif->duration * 1000;
}

/* Anime l’entrée de la notification à l’écran. */
static void slide_in_notif(t_WIN *win, t_notif *notif)
{
    if ((notif->coords.y * win->h) / 1080 < (win->h * 50 + (long)win->menus.notif.Popup.h / 3) / 1080)
    {
        SDL_Rect new_pos = notif->coords;
        new_pos.y += 1;
        notif->coords = new_pos;
    }
    else
        notif->state = NOTIF_DELETING;
}

/* Anime la sortie de la notification de l’écran. */
static int slide_out_notif(t_WIN *win, t_notif_buf **notif_buf)
{
    t_notif *notif = (*notif_buf)->notif;

    if (notif->duration >= SDL_GetTicks())
        return (0);
    SDL_Rect notifPos = notif->coords;
    to_responsive(win, &notifPos);
    if (((notifPos.y + win->menus.notif.Popup.h / 3)) * win->h > 0)
    {
        SDL_Rect new_pos = notif->coords;
        new_pos.y -= 1;
        notif->coords = new_pos;
        return (0);
    }
    destroy_notif_node(notif_buf);
    return (1);
}

/* Affiche et anime la notification courante. */
void display_notif(t_WIN *win, t_notif_buf **notif_buf)
{
    if (!*notif_buf)
        return;
    if ((*notif_buf)->notif->state == NOTIF_NOT_SHOWED)
    {
        spawn_notif(win, notif_buf);
        return;
    }
    else if ((*notif_buf)->notif->state == NOTIF_SPAWNING)
        slide_in_notif(win, (*notif_buf)->notif);
    else if ((*notif_buf)->notif->state == NOTIF_DELETING)
    {
        if (slide_out_notif(win, notif_buf))
            return;
    }
    SDL_Rect dest = (*notif_buf)->notif->coords;
    to_responsive(win, &dest);
    SDL_RenderCopy(win->renderPTR, win->menus.notif.Popup.texture, NULL, &dest);
    draw_notif_text(win, (*notif_buf)->notif,
    (*notif_buf)->notif->coords.x, (*notif_buf)->notif->coords.y,
    (*notif_buf)->notif->coords.w, (*notif_buf)->notif->coords.h);
}
