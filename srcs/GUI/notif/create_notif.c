/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_notif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:46:10 by lucas             #+#    #+#             */
/*   Updated: 2026/05/01 16:04:19 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.h"
#include "Game.h"

static t_notif_buf *allocate_new_notif_buf(void)
{
    t_notif_buf *new_notif_buf = malloc(sizeof(t_notif_buf));
    if (!new_notif_buf)
        return (NULL);
    new_notif_buf->next = NULL;
    new_notif_buf->notif = NULL;
    return (new_notif_buf);
}

static t_notif *allocate_new_notif(char *str, int duration_ms, int fontSize)
{
    t_notif *notif = malloc(sizeof(t_notif));
    if (!notif)
        return NULL;
    
    if (duration_ms < 1)
        duration_ms = 1;
    notif->duration = duration_ms;
    notif->text = ft_strdup(str);
    SDL_Rect new_pos = {-500, -500, 0, 0};
    notif->coords = new_pos;
    notif->time_left = -1;
    notif->state = NOTIF_NOT_SHOWED;
    notif->font.size = fontSize;
    notif->font.texture = NULL;
    return (notif);
}

void destroy_notif_node(t_notif_buf **notif_buf)
{
    if (!notif_buf || !*notif_buf)
        return;
    t_notif_buf *tmp = (*notif_buf)->next;
    if ((*notif_buf)->notif)
    {
        SDL_DestroyTexture((*notif_buf)->notif->font.texture);
        free((*notif_buf)->notif->text);
        free((*notif_buf)->notif);
    }
    free(*notif_buf);
    *notif_buf = tmp;
}

int init_notif(t_png *notifImg, SDL_Renderer *renderer)
{
    notifImg->path = ft_strdup("assets/png/notif/notif_bg.png");
    if(!process_png(notifImg))
		return (0);
    notifImg->texture = create_image(notifImg, renderer);
    return (1);
}

void create_notif(t_notif_buf **notif_buf, char *str, int duration_ms, int fontSize)
{
    if (!*notif_buf)
    {
        *notif_buf = allocate_new_notif_buf();
        if (!*notif_buf)
            return;
        (*notif_buf)->notif = allocate_new_notif(str, duration_ms, fontSize);
    }
    else
    {
        t_notif_buf *tmp = *notif_buf;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = allocate_new_notif_buf();
        tmp->next->notif = allocate_new_notif(str, duration_ms, fontSize);
        return;
    }
}

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

void display_notif(t_WIN *win, t_notif_buf **notif_buf)
{
    if (!*notif_buf)
        return;
    if ((*notif_buf)->notif->state == NOTIF_NOT_SHOWED)
    {
        SDL_Rect new_pos = { 1920 / 2 - (win->menus.notif.Popup.w / 3 / 2) , -win->menus.notif.Popup.h / 3 + 2, win->menus.notif.Popup.w / 3, win->menus.notif.Popup.h / 3};
        (*notif_buf)->notif->coords = new_pos;
        (*notif_buf)->notif->state = NOTIF_SPAWNING;

        SDL_Color color = {255, 255, 255, 255};
        (*notif_buf)->notif->font.color = color;
        create_text_multiple_lines(&(*notif_buf)->notif->font, win->renderPTR, (*notif_buf)->notif->text, DNFONT, win->menus.notif.Popup.w / 3 - 120);
        if (!(*notif_buf)->notif->font.texture)
        {
            destroy_notif_node(notif_buf);
            return;
        }
        (*notif_buf)->notif->w = (*notif_buf)->notif->font.w;
        (*notif_buf)->notif->h = (*notif_buf)->notif->font.h;
        (*notif_buf)->notif->duration = SDL_GetTicks() + (*notif_buf)->notif->duration * 1000;
        return;
    }
    else if ((*notif_buf)->notif->state == NOTIF_SPAWNING)
    {
        if (((*notif_buf)->notif->coords.y * win->h) / 1080 < (win->h * 50 + (long)win->menus.notif.Popup.h / 3) / 1080)
        {
            SDL_Rect new_pos = (*notif_buf)->notif->coords;
            new_pos.y += 1;
            (*notif_buf)->notif->coords = new_pos;
        }
        else
            (*notif_buf)->notif->state = NOTIF_DELETING;
    }
    else if ((*notif_buf)->notif->state == NOTIF_DELETING)
    {
        if ((*notif_buf)->notif->duration < SDL_GetTicks())
        {   
            SDL_Rect notifPos = (*notif_buf)->notif->coords;
            to_responsive(win, &notifPos);
            if (((notifPos.y + win->menus.notif.Popup.h / 3)) * win->h > 0)
            {
                SDL_Rect new_pos = (*notif_buf)->notif->coords;
                new_pos.y -= 1;
                (*notif_buf)->notif->coords = new_pos;
            }
            else
            {
                destroy_notif_node(notif_buf);
                return;
            }
        }
    }
    SDL_Rect dest = (*notif_buf)->notif->coords;
    to_responsive(win, &dest);
    SDL_RenderCopy(win->renderPTR, win->menus.notif.Popup.texture, NULL, &dest);
    draw_notif_text(win, (*notif_buf)->notif,
    (*notif_buf)->notif->coords.x, (*notif_buf)->notif->coords.y,
    (*notif_buf)->notif->coords.w, (*notif_buf)->notif->coords.h);
}
