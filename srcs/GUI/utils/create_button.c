/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_button.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 17:49:10 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/12 20:21:47 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI.h"
#include "Window.h"

static  void insert_new_button(t_buttons **button_list, void (*callback)(t_WIN *), SDL_Rect coords, t_RGB color, t_RGB hoverColor, t_font *text, t_font *textHover, int pageID)
{
    t_buttons *new;

    new = malloc(sizeof(t_buttons));
    if (!new)
        return;
    new->callback_func = callback;
    new->next = NULL;
    new->buttonCoords = coords;
    new->color = color;
    new->hoverColor = hoverColor;
    new->text = text;
    new->textHover = textHover;
    new->page_id = pageID;
    if (*button_list)
    {
        t_buttons *tmp = *button_list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
    else
        *button_list = new;
    return;
}

static int is_mouse_pos_inside_button(SDL_Rect mouseCoords, SDL_Rect buttonCoords)
{
    if (mouseCoords.x < buttonCoords.x || mouseCoords.x > buttonCoords.x  + buttonCoords.w)
        return 0;
    if (mouseCoords.y < buttonCoords.y || mouseCoords.y > buttonCoords.y  + buttonCoords.h)
        return 0;
    return 1;
}

void create_button(t_buttons **button_list, void (*callback)(t_WIN *), SDL_Rect coords, t_RGB color, t_RGB hoverColor, t_font *text, t_font *textHover, int pageID)
{
    insert_new_button(button_list, callback, coords, color, hoverColor, text, textHover, pageID);
}

void display_buttons(t_buttons *button_list, t_WIN *win, int pageID)
{
    SDL_Rect mouseCoords;
    SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);
    while(button_list)
    {
        if (button_list->page_id  != pageID)
        {
            button_list = button_list->next;
            continue;
        }
        t_RGB color = button_list->color;
        t_font *textFont = button_list->text;
        int HOffset = button_list->text->textHOffset;
        SDL_Rect buttonCoords = button_list->buttonCoords;
        to_responsive(win, &buttonCoords);
        if (is_mouse_pos_inside_button(mouseCoords, buttonCoords))
        {
            color = button_list->hoverColor;
            textFont = button_list->textHover;
            HOffset = button_list->textHover->textHOffset;
        }
        create_rectangle(win->renderPTR, button_list->buttonCoords, color);
        if (textFont->texture)
        {
            int x = button_list->buttonCoords.x + (button_list->buttonCoords.w / 2 - textFont->w / 2);
            int y = button_list->buttonCoords.y + (button_list->buttonCoords.h / 2 - textFont->h / 2) - HOffset;
            int w = textFont->w;
            int h = textFont->h; 
            SDL_Rect btn_text_dest = {x, y, w, h};
            to_responsive(win, &btn_text_dest);
            SDL_RenderCopy(win->renderPTR, textFont->texture, NULL, &btn_text_dest);
        }
        button_list = button_list->next;
    }
}

int check_button_pressed(t_WIN *win, t_buttons *button_list)
{
    SDL_Rect mouseCoords;
    SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);

    while(button_list)
    {
        if (is_mouse_pos_inside_button(mouseCoords, button_list->buttonCoords))
        {
            printf("Button has been pressed!\n");
            if (button_list->callback_func)
                button_list->callback_func(win);
            return 1;
        }
        button_list = button_list->next;
    }
    return 0;
}

void free_buttons(t_buttons *buttonlist)
{
    if (!buttonlist)
        return;
    while(buttonlist)
    {
        t_buttons *tmp = buttonlist;
        buttonlist = buttonlist->next;
        free(tmp);
    }
}