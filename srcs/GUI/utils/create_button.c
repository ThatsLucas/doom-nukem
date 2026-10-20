/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_button.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edurance <edurance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 17:49:10 by lle-duc           #+#    #+#             */
/*   Updated: 2026/08/12 15:59:44 by edurance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GUI/GUI.h"
#include "Window.h"
#include "Game.h"

static  void insert_new_button(t_buttons **button_list, void (*callback)(t_game *), SDL_Rect coords, t_RGB color, t_RGB hoverColor, t_font *text, t_font *textHover, int pageID)
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

int is_mouse_pos_inside_button(SDL_Rect mouseCoords, SDL_Rect buttonCoords)
{
    if (mouseCoords.x < buttonCoords.x || mouseCoords.x > buttonCoords.x  + buttonCoords.w)
        return 0;
    if (mouseCoords.y < buttonCoords.y || mouseCoords.y > buttonCoords.y  + buttonCoords.h)
        return 0;
    return 1;
}

void create_button(t_buttons **button_list, void (*callback)(t_game *), SDL_Rect coords, t_RGB color, t_RGB hoverColor, t_font *text, t_font *textHover, int pageID)
{
    insert_new_button(button_list, callback, coords, color, hoverColor, text, textHover, pageID);
}

/* Label of the button, centered (minus its vertical offset) */
static void draw_button_text(t_game *game, t_buttons *button, t_font *textFont, int HOffset)
{
    int x = button->buttonCoords.x + (button->buttonCoords.w / 2 - textFont->w / 2);
    int y = button->buttonCoords.y + (button->buttonCoords.h / 2 - textFont->h / 2) - HOffset;
    int w = textFont->w;
    int h = textFont->h;
    SDL_Rect btn_text_dest = {x, y, w, h};

    to_responsive(game->window, &btn_text_dest);
    SDL_RenderCopy(game->window->renderPTR, textFont->texture, NULL, &btn_text_dest);
}

/* Draws one button, using its hover color / text when the mouse is on it */
static void display_button(t_buttons *button, t_game *game, SDL_Rect mouseCoords)
{
    t_RGB color = button->color;
    t_font *textFont = button->text;
    int HOffset = 0;

    if (textFont)
        HOffset = textFont->textHOffset;
    SDL_Rect buttonCoords = button->buttonCoords;
    to_responsive(game->window, &buttonCoords);
    if (is_mouse_pos_inside_button(mouseCoords, buttonCoords))
    {
        color = button->hoverColor;
        if (button->textHover)
        {
            textFont = button->textHover;
            HOffset = button->textHover->textHOffset;
        }
    }
    if (color.alphaValue > 0)
        create_rectangle(game->window->renderPTR, button->buttonCoords, color);
    if (textFont && textFont->texture)
        draw_button_text(game, button, textFont, HOffset);
}

void display_buttons(t_buttons *button_list, t_game *game, int pageID)
{
    SDL_Rect mouseCoords;

    SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);
    while(button_list)
    {
        if (button_list->page_id == pageID)
            display_button(button_list, game, mouseCoords);
        button_list = button_list->next;
    }
}

int check_button_pressed(t_game *game, t_buttons *button_list)
{
    SDL_Rect mouseCoords;
    SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);

    while(button_list)
    {
        if (game->window->menus.current != button_list->page_id)
        {
            button_list = button_list->next;
            continue;
        }
        SDL_Rect buttonCoords = button_list->buttonCoords;
        to_responsive(game->window, &buttonCoords);
        if (is_mouse_pos_inside_button(mouseCoords, buttonCoords))
        {
            if (button_list->callback_func)
                button_list->callback_func(game);
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