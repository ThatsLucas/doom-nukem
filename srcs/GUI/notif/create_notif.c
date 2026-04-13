/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_notif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:46:10 by lucas             #+#    #+#             */
/*   Updated: 2026/04/14 00:16:57 by lucas            ###   ########.fr       */
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

static t_notif *allocate_new_notif(char *str, int duration_ms)
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
    notif->state = 0;
    return (notif);
}

static void destroy_notif_node(t_notif_buf **notif_buf)
{
    t_notif_buf *tmp = (*notif_buf)->next;
    if ((*notif_buf)->notif)
    {
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

void create_notif(t_notif_buf **notif_buf, char *str, int duration_ms)
{
    if (!*notif_buf)
    {
        *notif_buf = allocate_new_notif_buf();
        if (!*notif_buf)
            return;
        (*notif_buf)->notif = allocate_new_notif(str, duration_ms);
    }
    else
    {
        t_notif_buf *tmp = *notif_buf;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = allocate_new_notif_buf();
        tmp->next->notif = allocate_new_notif(str, duration_ms);
        return;
    }
}

void display_notif(t_WIN *win, t_notif_buf **notif_buf)
{
    if (!*notif_buf)
        return;
    if ((*notif_buf)->notif->state == NOTIF_NOT_SHOWED)
    {
        SDL_Rect new_pos = { win->w / 2 - win->Popup.w / 3 / 2, win->Popup.h / 3 - (win->Popup.h / 3 - 2), win->Popup.w / 3, win->Popup.h / 3};
        (*notif_buf)->notif->coords = new_pos;
        (*notif_buf)->notif->state = NOTIF_SPAWNING;
    }
    else if ((*notif_buf)->notif->state == NOTIF_SPAWNING)
    {
        if (((*notif_buf)->notif->coords.y * win->h) / 1080 < (win->h * 150 + (long)win->Popup.h / 3) / 1080)
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
        if ((((*notif_buf)->notif->coords.y + win->Popup.h / 3)) * win->h > 0)
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
    to_responsive(win, &(*notif_buf)->notif->coords);
	SDL_RenderCopy(win->renderPTR, win->Popup.texture, NULL, &(*notif_buf)->notif->coords);
}