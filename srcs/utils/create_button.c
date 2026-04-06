/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_button.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 17:49:10 by lle-duc           #+#    #+#             */
/*   Updated: 2026/04/06 17:53:02 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI.h"
#include "Window.h"

static  void insert_new_button(t_buttons **button_list, void (*callback)(t_WIN *), t_coordinates coords, t_RGB color, t_RGB hoverColor)
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

static int is_mouse_pos_inside_button(t_coordinates mouseCoords, t_coordinates buttonCoords)
{
    if (mouseCoords.x < buttonCoords.x || mouseCoords.x > buttonCoords.x  + buttonCoords.w)
        return 0;
    if (mouseCoords.y < buttonCoords.y || mouseCoords.y > buttonCoords.y  + buttonCoords.h)
        return 0;
    return 1;
}

void create_button(t_buttons **button_list, void (*callback)(t_WIN *), t_coordinates coords, t_RGB color, t_RGB hoverColor)
{
    insert_new_button(button_list, callback, coords, color, hoverColor);
}

void display_buttons(t_buttons *button_list, SDL_Renderer *renderer)
{
    t_coordinates mouseCoords;
    SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);
    while(button_list)
    {
        t_RGB color = button_list->color;
        if (is_mouse_pos_inside_button(mouseCoords, button_list->buttonCoords))
            color = button_list->hoverColor;
            
        create_rectangle(renderer, button_list->buttonCoords, color);
        button_list = button_list->next;
    }
}

int check_button_pressed(t_WIN *win, t_buttons *button_list)
{
    t_coordinates mouseCoords;
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